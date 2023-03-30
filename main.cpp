#include <iostream>
#include <unistd.h>

using namespace std;
const float prob=.00001;
const int gridSize = 100;
void printGrid(bool gridOne[gridSize + 1][gridSize + 1]);
void deterministic(bool gridOne[gridSize + 1][gridSize + 1]);
void god1(bool gridOne[gridSize + 1][gridSize + 1]);
void god2(bool gridOne[gridSize + 1][gridSize + 1]);
void god3(bool gridOne[gridSize + 1][gridSize + 1]);
void add_glunder(bool gridOne[gridSize + 1][gridSize + 1],int x,int y);
void seed_pulsar(bool gridOne[gridSize + 1][gridSize + 1], int x, int y);
void myShape(bool gridOne[gridSize + 1][gridSize + 1],int x,int y);
void buffer_train(bool gridOne[gridSize + 1][gridSize + 1], int x, int y);
void loopQuarterForGod3(bool gridOne[gridSize + 1][gridSize + 1],int startX,int endX,int startY,int endY);
void loopQuarterForGod2(bool gridOne[gridSize + 1][gridSize + 1],int startX,int endX,int startY,int endY);
int main()
{

  bool gridOne[gridSize + 1][gridSize + 1] = {};

  for (int row = 1; row < gridSize; row++)
  {
    for (int col = 1; col < gridSize; col++)
    {  
      if(row%2==0 )
        gridOne[row][col] = true;
    }
  }
  printGrid(gridOne);
  for (int i =0;i<100;i++)
  {
    printGrid(gridOne);
    deterministic(gridOne);
    god1(gridOne);
    god2(gridOne);
    god3(gridOne);
    
    
    usleep(200000);
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
      else if (alive == 3 or alive == 2 and gridTwo[row][col]){
        gridOne[row][col] = true;
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
  loopQuarterForGod2(gridOne,1,(gridSize/4)+15,1,(gridSize/4)+15);
  loopQuarterForGod2(gridOne,1,(gridSize/4)+15,(gridSize/2)+10,gridSize);
  loopQuarterForGod2(gridOne,(gridSize/2)+10,gridSize,1,(gridSize/4)+15);
  loopQuarterForGod2(gridOne,(gridSize/2)+10,gridSize,(gridSize/2)+10,gridSize);
  loopQuarterForGod2(gridOne,(gridSize/4)+16,(gridSize/2)+10,(gridSize/4)+16,(gridSize/2)+10);
}
void god3(bool gridOne[gridSize + 1][gridSize + 1]){
loopQuarterForGod3(gridOne,1,gridSize/2,1,gridSize/2);
loopQuarterForGod3(gridOne,1,gridSize/2,gridSize/2,gridSize);
loopQuarterForGod3(gridOne,gridSize/2,gridSize,1,gridSize/2);
loopQuarterForGod3(gridOne,gridSize/2,gridSize,gridSize/2,gridSize);
}
void loopQuarterForGod2(bool gridOne[gridSize + 1][gridSize + 1],int startX,int endX,int startY,int endY){
  bool checkEmpty=true;
  for(int row =startX;row<=endX;row++){
    for(int col =startY;col<=endY;col++){
      if(gridOne[row][col]==true){
        checkEmpty=false;
      }
    }
  }
  
  if (checkEmpty)
    if (startX==1 && startY==1)
      add_glunder(gridOne,startX+(gridSize/4)-6,startY+(gridSize/4)-15);
    else if(startX==1 && startY>=gridSize/2)
      seed_pulsar(gridOne,startX+(gridSize/4)-6,startY+(gridSize/4)-6);
    else if(startX>=gridSize/2 && startY==1)
      seed_pulsar(gridOne,startX+(gridSize/4)-6,startY+(gridSize/4)-15);
    else if(startX>=gridSize/2 && startY>=gridSize/2)
      add_glunder(gridOne,startX+(gridSize/4)-6,startY+(gridSize/4)-6);
    else{
      
      myShape(gridOne,startX,startY);
    }
}
void loopQuarterForGod3(bool gridOne[gridSize + 1][gridSize + 1],int startX,int endX,int startY,int endY){
  int count=0;
  for(int row =startX;row<=endX;row++){
    for(int col =startY;col<=endY;col++){
      if (gridOne[row][col])
        count++;
    }
  }
  if (count>= ((gridSize/2)*(gridSize/2))*.5){
    for(int row =startX;row<=endX;row++){
      for(int col =startY;col<=endY;col++){
        gridOne[row][col]=false;
      }
    }
  }
  else if(count<10){
    for(int row =startX;row<=endX;row++){
      for(int col =startY;col<=endY;col++){
        if((float) rand()/RAND_MAX<prob)
          gridOne[row][col]=true;
      }
    }
  }
}
void myShape(bool gridOne[gridSize + 1][gridSize + 1],int x,int y){
    gridOne[x][y] = true;
    gridOne[x][y+1] = true;
    gridOne[x][y+2] = true;
    gridOne[x][y+6] = true;
    gridOne[x][y+7] = true;
    gridOne[x][y+8] = true;

    gridOne[x+1][y-1] = true;
    gridOne[x+1][y+3] = true;
    gridOne[x+1][y+5] = true;
    gridOne[x+1][y+9] = true;

    gridOne[x+3][y-1] = true;
    gridOne[x+3][y+3] = true;
    gridOne[x+3][y+5] = true;
    gridOne[x+3][y+9] = true;

    gridOne[x+4][y] = true;
    gridOne[x+4][y+1] = true;
    gridOne[x+4][y+2] = true;
    gridOne[x+4][y+6] = true;
    gridOne[x+4][y+7] = true;
    gridOne[x+4][y+8] = true;
}
void add_glunder(bool gridOne[gridSize + 1][gridSize + 1],int x,int y){
    gridOne[x+5][y+1] = true;
    gridOne[x+5][y+2] = true;
    gridOne[x+6][y+1] = true;
    gridOne[x+6][y+2] = true;

    gridOne[x+3][y+13] = true;
    gridOne[x+3][y+14] = true;
    gridOne[x+4][y+12] = true;
    gridOne[x+4][y+16] = true;
    gridOne[x+5][y+11] = true;
    gridOne[x+5][y+17] = true;
    gridOne[x+6][y+11] = true;
    gridOne[x+6][y+15] = true;
    gridOne[x+6][y+17] = true;
    gridOne[x+6][y+18] = true;
    gridOne[x+7][y+11] = true;
    gridOne[x+7][y+17] = true;
    gridOne[x+8][y+12] = true;
    gridOne[x+8][y+16] = true;
    gridOne[x+9][y+13] = true;
    gridOne[x+9][y+14] = true;

 
}
void seed_pulsar(bool gridOne[gridSize + 1][gridSize + 1], int x, int y) {
    gridOne[x + 2][y] = true;
    gridOne[x + 3][y] = true;
    gridOne[x + 4][y] = true;
    gridOne[x + 8][y] = true;
    gridOne[x + 9][y] = true;
    gridOne[x + 10][y] = true;
    gridOne[x][y + 2] = true;
    gridOne[x][y + 3] = true;
    gridOne[x][y + 4] = true;
    gridOne[x][y + 8] = true;
    gridOne[x][y + 9] = true;
    gridOne[x][y + 10] = true;
    gridOne[x + 5][y + 2] = true;
    gridOne[x + 5][y + 3] = true;
    gridOne[x + 5][y + 4] = true;
    gridOne[x + 5][y + 8] = true;
    gridOne[x + 5][y + 9] = true;
    gridOne[x + 5][y + 10] = true;
    gridOne[x + 7][y + 2] = true;
    gridOne[x + 7][y + 3] = true;
    gridOne[x + 7][y + 4] = true;
    gridOne[x + 7][y + 8] = true;
    gridOne[x + 7][y + 9] = true;
    gridOne[x + 7][y +10 ]=true;

}
void buffer_train(bool gridOne[gridSize + 1][gridSize + 1], int x, int y) {
    gridOne[x][y+1]   = true;
    gridOne[x+1][y+2] = true;
    gridOne[x+2][y]   = true;
    gridOne[x+2][y+1] = true;
    gridOne[x+2][y+3] = true;
    gridOne[x+2][y+4] = true;
    gridOne[x+3][y+1] = true;
    gridOne[x+3][y+4] = true;
    gridOne[x+4][y+1] = true;
    gridOne[x+4][y+2] = true;
    gridOne[x+4][y+3] = true;
    gridOne[x+4][y+4] = true;
}