#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  double sample;  // <-- redeclaring the sample variable outisde of the loop

  // now do the same thing for initializing the instances of the structs outside of the loop
  struct cs1300bmp *input = new struct cs1300bmp;
  struct cs1300bmp *output = new struct cs1300bmp;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    // struct cs1300bmp *input = new struct cs1300bmp;                              // we  don't want to waste cycles re-initializing these unneccessarily.
    // struct cs1300bmp *output = new struct cs1300bmp;
    //int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);   if we just directly make the function call, we again don't need to unneccessarily initialize the 'ok' variable

    if ( cs1300bmp_readfile( (char *) inputFilename.c_str(), input) ) {
      sample = applyFilter(filter, input, output);     // want to declare this outside of the loop so we are not recreating the same variable
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    //delete input;    might potentially cause memory error since we initialize the objects outside of the loop
    //delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  // output -> width = input -> width;         instead of having dereferenced memory, create local variables since they have faster access times
  // output -> height = input -> height;
  int varWidth = output->width = input->width;
  int varHeight = output->height = input->height;

  int varHeightn = varHeight - 1;           //  make these calculations outside of the loop so we don't have to waste cycles re-calculating it everytime.
  int varWidthn = varWidth - 1;

  int filterSize = filter -> getSize();   // move this call outside fo the loop so we don't have to keep calling another function
  int step = 0;
  int i = 0;
  for (i = 9; i > 1; i--)
  {
    if (!filterSize%i && !step)
    {
      step = i;
    }
  }

  // Array to hold filter x and y values, so we don't have to keep looking for the values in the main loop , we need to fill it next with a seperate loop
  int filterxy[filterSize][filterSize];
  i = 0;
  int j = 0;
  for ( i = 0 ; i < filterSize; i++ )
  {
    for ( j = 0; j < filterSize; j++)
    {
      filterxy[i][j] = filter->get(i,j);
    }
  }

  int divisor = filter->getDivisor();  // make this a variable so we don't have to keep calling the function

  int plane1Value, plane2Value, plane3Value;  // variables that will hold values for the planes in the image.

  int row = 1;
  int colomn = 1;
  int k = 0;
  for ( row = 1; row < varHeightn; row = row + step)
  {
    for ( colomn = 1; colomn <= varWidthn; colomn = colomn + step){
      plane1Value = 0; // make these all back to zero for the next execution of the inner loop
      plane2Value = 0;
      plane3Value = 0;
    }
    for ( k = 0; k < step; k++)
    {
      for ( i = 0; i < filterSize; i++)
      {
        int temp1 = 0;
        int temp2 = 0;
        int temp3 = 0;


        int varRow = row + i - 1 + k;  // creating a row variable for current row that we will use for the column loop
        for (j = 0; j < filterSize; j++){
          int matrixXY = filterxy[i][j];    // again intitializing these variables will maek it so we don't have to waste cycles calculating the values
          int varCol = colomn + j - 1 + k;

          // instead of creating more loops we can just do inline programming and process each plane individually

          temp1 = temp1 + input -> color[0][varRow][varCol] * matrixXY;
          temp2 = temp2 + input -> color[1][varRow][varCol] * matrixXY;
          temp3 = temp3 + input -> color[2][varRow][varCol] * matrixXY;
        }
        // now take the temp values and add them to the plane values
        plane1Value = plane1Value + temp1;
        plane2Value = plane2Value + temp2;
        plane3Value = plane3Value + temp3;
      }
        // we save calculation time if avoid all instance for when divisor is equal to one, remember we created a seperate variable for divisor to avoid unneccessary function calls
      if (divisor != 1 ){
        plane1Value = plane1Value / divisor;
        plane2Value = plane2Value / divisor;
        plane3Value = plane3Value / divisor;
      }

      // now we can address improving the conditional statements by making them nested conditionals. By making them nested conditionals we can save cycles since
      // we will avoid checking other conditionals that are uneeded.
      plane1Value = plane1Value < 0 ? 0 : plane1Value > 255 ? 255 : plane1Value;
      plane2Value = plane2Value < 0 ? 0 : plane2Value > 255 ? 255 : plane2Value;
      plane3Value = plane3Value < 0 ? 0 : plane3Value > 255 ? 255 : plane3Value;

      output->color[0][row][colomn] = plane1Value;
      output->color[1][row][colomn] = plane2Value;
      output->color[2][row][colomn] = plane3Value;
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
