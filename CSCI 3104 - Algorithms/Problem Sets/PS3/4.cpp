#include <iostream>
using namespace std;

int mergeSort(int array[], int temp[], int left, int right);
int merge(int array[], int temp[], int left, int mid, int right);

/* This functions copies to temp array with input array and return the number of inversions happens in the array */
int sortMerged(int array[], int arraySize)
{
    int temp[arraySize];
    return mergeSort(array, temp, 0, arraySize - 1);
}

/* Needs two helper functions to make sortMerged happen. Recursive function that sorts the sub arrays and keeps returning number of inversions*/
int mergeSort(int array[], int temp[], int left, int right)
{
    int mid, flipCount = 0;
    /*  If right index is bigger than left index, divide the array into two parts. */
    if (right > left) {
        /* To find the mid */
        mid = (right + left) / 2;
        /* Use recursive function mergeSort till right is less than left, and the flip count will keep adding  */
        flipCount += mergeSort(array, temp, left, mid);
        flipCount += mergeSort(array, temp, mid + 1, right);

        /*Call helper function merge to merge back two parts*/
        flipCount += merge(array, temp, left, mid + 1, right);
    }
    return flipCount;
}

/* Helper function to make two sub array merge back and return flipCount again*/
int merge(int array[], int temp[], int left,int mid, int right)
{
    int i, j, k;
    int flipCount = 0;

    i = left; /* index for left subarray*/
    j = mid; /* index for right subarray*/
    k = left; /* index for resultant merged subarray*/
    while ((i <= mid - 1) && (j <= right)) { /* This is where flipping happens */
        if (array[i] <= array[j]) { /* Compare two elements*/
            temp[k++] = array[i++]; /* Switch element*/
        }
        else {
            temp[k++] = array[j++];
            flipCount = flipCount + (mid - i);
        }
    }

    /* Copy the remaining elements of left subarray to temp array */
    while (i <= mid - 1)
        temp[k++] = array[i++];

    /* Copy the remaining elements of right subarray to temp array*/
    while (j <= right)
        temp[k++] = array[j++];

    /*Copy the merged elements from temp to original array*/
    for (i = left; i <= right; i++)
        array[i] = temp[i];

    return flipCount;
}

// Main function
int main()
{
   int size = 100;
   int array[size];
   srand(time(0));
   for(int i = 0; i < size; i++){ /* set random number in array */
       array[i] = rand() % 200 + 1;
   }
    cout<<"Array is\n";
   for(int j = 0; j < size; j++){ /* print array before sorting */
       cout<<array[j]<<' ';
   }
   cout << endl;
   cout << endl;
   int number = sortMerged(array, size); /* call sortMerged */
   cout << "Number of reverse are " << number << '\n';
   cout << endl;
   for(int j = 0; j < size; j++){ /* print array after sorting */
       cout<<array[j]<<' ';
   }
   return 0;
}
