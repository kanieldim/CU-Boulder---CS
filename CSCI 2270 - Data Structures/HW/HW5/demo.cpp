void MovieTree :: printMovieInventory()
{
    MovieNode *temp;
    MovieNode *temp2;
    temp = root;
    while(temp != nullptrptr)
    {
        if(temp -> leftChild == nullptr)
        {
            cout << "Movie: " << temp -> title << " " << temp -> rating << endl;
            temp = temp -> rightChild;
        }
        else
        {
            temp2 = temp -> leftChild;
            while (temp2 -> rightChild != nullptr && temp2 -> rightChild != temp)
            {
                temp2 = temp2->rightChild;
            }
            if (temp2 -> rightChild == nullptr)
            {
                temp2 -> rightChild = temp;
                temp = temp -> leftChild;
            }
            else
            {
                temp2 -> rightChild = nullptr;
                cout << "Movie: " << temp -> title << " " << temp -> rating << endl;
                temp = temp -> rightChild;
            }
        }
    }

}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating)
{
   MovieNode *temp;
   MovieNode *parent;
   MovieNode *tempNew = new MovieNode(ranking, title, year, rating);
    temp = root;
   parent = temp;

   if (parent == nullptr)
   {
       root = tempNew;
   }
   else
   {
       while (temp != nullptr)
       {
           parent = temp;
           if(temp -> title > tempNew -> title)
           {
               temp = temp -> leftChild;
           }
           else
           {
               temp = temp -> rightChild;
           }
       }
       if (parent -> title > tempNew -> title)
       {
           parent-> leftChild = tempNew;
           tempNew -> parent = parent;
       }
       else
       {
           parent -> rightChild = tempNew;
           tempNew -> parent = parent;
       }
   }
}

void MovieTree :: findMovie(string title)
{
  MovieNode *movieFound;
  movieFound = root;
  bool trueOrFalse = false;
  while( movieFound != nullptr)
  {
      if (movieFound -> title > title)
      {
          movieFound = movieFound ->leftChild;
      }
      else if (movieFound -> title < title)
      {
          movieFound = movieFound -> rightChild;
      }
      else if (movieFound -> title == title)
      {
          trueOrFalse = true;
          break;
      }
  }

  if (trueOrFalse)
  {
  	cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << movieFound->ranking << endl;
    cout << "Title :" << movieFound->title << endl;
    cout << "Year :" << movieFound->year << endl;
    cout << "rating :" << movieFound->rating << endl;
  	return;
  }
  else
  {
    cout<<"Movie not found."<<endl;
    return;
  }
}


void MovieTree::queryMovies(float rating, int year)
{
	cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;

	MovieNode *temp;
  MovieNode *temp2;
  temp = root;
  while(temp)
  {
    if(temp -> leftChild == nullptr)
    {
			if((temp ->year) > year && (temp->rating) >= rating)
      {
        cout << temp -> title << "(" << temp -> year << ") " << temp -> rating << endl;
      }
      temp = temp -> rightChild;
    }
    else
    {
      temp2 = temp -> leftChild;
      while(temp2 -> rightChild != temp && temp2 -> rightChild != nullptr)
      {
        temp2=temp2 -> rightChild;
      }
      if(temp2 -> rightChild == temp)
      {
        temp2 -> rightChild = nullptr;
        temp=temp -> rightChild;
      }
      else
      {
        temp2 -> rightChild = temp;
			  if((temp ->year) > year && (temp->rating) >= rating)
        {
      		cout << temp -> title << "(" << temp -> year << ") " << temp -> rating << endl;
        }
        temp = temp -> leftChild;
      }
    }
  }
}



void MovieTree::averageRating()
{
  float average = 0.0;
  float sum = 0.0;
  int totalNode = 0;
  MovieNode *temp;
  MovieNode *temp2;
  temp = root;

  if (temp == nullptr)
  {
      cout << "Average rating:" << average << endl;
      return;
  }
  while(temp)
  {
    sum += temp -> rating;
    totalNode++;
    if(temp -> leftChild == nullptr)
    {
      sum += temp -> rating;
      totalNode++;
      temp = temp -> rightChild;
    }
    else
    {
      temp2 = temp -> leftChild;
      while(temp2 -> rightChild != temp && temp2 -> rightChild != nullptr)
      {
        temp2 = temp2 -> rightChild;
      }
      if(temp2 -> rightChild == temp)
      {
        temp2 -> rightChild= nullptr;
        temp = temp -> rightChild;
      }
      else
      {
        temp2 -> rightChild = temp;
        temp = temp -> leftChild;
      }
    }
  }
  average = (float) sum/totalNode;
  cout << "Average rating:" << average << endl;
}
