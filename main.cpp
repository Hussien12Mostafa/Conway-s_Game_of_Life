#include <iostream>
#include <unistd.h>

using namespace std;
const float prob=.03;
const int gridSize = 100;
void printGrid(bool gridOne[gridSize + 1][gridSize + 1]);
void deterministic(bool gridOne[gridSize + 1][gridSize + 1]);
void god1(bool gridOne[gridSize + 1][gridSize + 1]);
void god2(bool gridOne[gridSize + 1][gridSize + 1]);
int main()
{

  bool gridOne[gridSize + 1][gridSize + 1] = {};

  for (int row = 1; row < gridSize; row++)
  {
    for (int col = 1; col < gridSize; col++)
    {  
      if(row%4==0 )
        gridOne[row][col] = true;
    }
  }

  printGrid(gridOne);
  for (int i =0;i<100;i++)
  {
    printGrid(gridOne);
    deterministic(gridOne);
    god1(gridOne);
    usleep(2000000);
  }
}

void printGrid(bool gridOne[gridSize + 1][gridSize + 1])
{
  for (int row = 1; row < gridSize; row++)
  {
    for (int col = 1; col < gridSize; col++)
    {
      if (gridOne[row][col] == true)
        cout << " O ";
      else
        cout << " . ";
      
        
    }
    cout << endl;
  }
  cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void deterministic(bool gridOne[gridSize + 1][gridSize + 1])
{
  bool gridTwo[gridSize + 1][gridSize + 1] = {};

  std::copy(&gridOne[0][0], &gridOne[0][0]+(gridSize+1)*(gridSize+1),&gridTwo[0][0]);

  for (int row = 1; row < gridSize; row++)
  {
    for (int col = 1; col < gridSize; col++)
    {
      int alive = 0;
      for (int r = -1; r < 2; r++)
      {
        for (int c = -1; c < 2; c++)
        {
          if (!(r == 0 && c == 0))
          {
            if (gridTwo[row + r][col + c])
            {
              ++alive;
            }
          }
        }
      }
      if (alive < 2)
      {
        gridOne[row][col] = false;
      }
      else if (alive == 3)
      {
        gridOne[row][col] = true;
      }
      else if (alive > 3)
      {
        gridOne[row][col] = false;
      }
    }
  }
}


void god1(bool gridOne[gridSize + 1][gridSize + 1]){

 for (int row = 1; row < gridSize; row++)
  {
    for (int col = 1; col < gridSize; col++)
    {
      if((float) rand()/RAND_MAX<prob)
        gridOne[row][col]= !gridOne[row][col];
    }
  }  
}
void god2(bool gridOne[gridSize + 1][gridSize + 1]){

 for (int row = 1; row < gridSize; row++)
  {
    for (int col = 1; col < gridSize; col++)
    {
      if((float) rand()/RAND_MAX<prob)
        gridOne[row][col]= !gridOne[row][col];
    }
  }  
}