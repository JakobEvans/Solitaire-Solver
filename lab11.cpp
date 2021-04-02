// Jakob Evans
// CS315 first section
// Lab11
#include "SeparateChaining.cpp"

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

void makeMove(int in_board[49], vector<int> currentMove, int out_board);

vector<vector <int>>nextMoves(int board[49]);

bool checkMove(int board[49], vector<int> move);

bool solve(int in_board[49], vector<vector <int>> &mySeq);

bool hsolve(int in_board[49], vector<vector <int>> &mySeq, HashTable<long long int> &hash, int size);

bool solved(int in_board[49]);

void displayBoard(int board[49]);

// takes in board and a move and changes the board accordingly
 //(changed board is out_board)
void makeMove(int in_board[49], vector<int> currentMove, int out_board[49]){
  //int out_board[];
  int i = 0;
  while(i < 49){
    out_board[i] = in_board[i];
    i++;
  }

  int startPeg = currentMove[0];


  int jumpPeg = currentMove[1];

  int endPeg = currentMove[2];

  //peg that is moving now will not have a peg...
  out_board[startPeg] = 0;
  //peg that is being jumped over is now an empty space...
  out_board[jumpPeg] = 0;
  //the start peg ends up in this position
  out_board[endPeg] = 1;
  //return out_board;

}



/* 3 vector
vector<vector<vector<int>>> ValidMoves { {{}}, {{}}, {{2,3,4},{2,9,16}}, {{3,10,17}},
{{4,11,18},{4,3,2}}, {{}}, {{}}, {{}}, {{}},{{9,10,11},{9,16,23}}, {{10,17,24}},
{{11,10,9},{11,18,25}}, {{}}, {{}}, {{14,15,16},{14,21,28}}, {{15,16,17}, {15,22,29}},
{{16,15,14},{16,17,18},{16,23,30},{16,9,2}}, {{17,10,3},{17,16,15},{17,18,19},{17,24,31}},
{{18,11,4},{18,17,16},{18,19,20},{18,25,32}}, {{19,18,17},{19,26,33}},{{20,19,18},{20,27,34}},
{{21,22,23}},{{22,23,24}}, {{23,16,9},{23,22,21},{23,24,25},{23,30,37}},{{24,17,10},{24,23,22},
{24,25,26},{24,31,38}}, {{25,18,11},{25,24,23},{25,26,27},{25,32,39}},{{26,25,24}},{{27,26,25}},
{{28,21,14},{28,29,30}},{{29,22,15},{29,30,31}}, {{30,23,16},{30,29,28},{30,31,32},{30,37,44}},
{{31,24,17},{31,30,29},{31,32,33},{31,38,45}}, {{32,25,18},{32,31,30},{32,33,34},{32,39,46}},
{{33,26,19},{33,32,31}}, {{34,27,20},{34,33,32}}, {{}}, {{}}, {{37,30,23},{37,38,39}},
{{38,31,24}}, {{39,32,25},{39,38,37}}, {{}}, {{}}, {{}}, {{}}, {{44,37,30},{44,45,46}},
{{45,38,31}},{{46,39,32},{46,45,44}} };*/

//2d vector
vector<vector<int>> ValidMoves{ {}, {}, {2,3,4},{2,9,16}, {3,10,17},
{4,11,18},{4,3,2}, {}, {}, {}, {},{9,10,11},{9,16,23}, {10,17,24},
{11,10,9},{11,18,25}, {}, {},{14,15,16},{14,21,28},{15,16,17}, {15,22,29},
{16,15,14},{16,17,18},{16,23,30},{16,9,2}, {17,10,3},{17,16,15},{17,18,19},{17,24,31},
{18,11,4},{18,17,16},{18,19,20},{18,25,32}, {19,18,17},{19,26,33},{20,19,18},{20,27,34},
{21,22,23},{22,23,24},{23,16,9},{23,22,21},{23,24,25},{23,30,37},{24,17,10},{24,23,22},
{24,25,26},{24,31,38},{25,18,11},{25,24,23},{25,26,27},{25,32,39},{26,25,24},{27,26,25},
{28,21,14},{28,29,30},{29,22,15},{29,30,31}, {30,23,16},{30,29,28},{30,31,32},{30,37,44},
{31,24,17},{31,30,29},{31,32,33},{31,38,45}, {32,25,18},{32,31,30},{32,33,34},{32,39,46},
{33,26,19},{33,32,31}, {34,27,20},{34,33,32},{}, {},{37,30,23},{37,38,39},
{38,31,24}, {39,32,25},{39,38,37}, {}, {}, {}, {},{44,37,30},{44,45,46},
{45,38,31},{46,39,32},{46,45,44}, {}, {} };

vector<vector <int>>nextMoves(int board[49]) {
  vector<vector <int>>nextMoves;
  vector<int>temp;
  for(int m = 0; m < ValidMoves.size(); m++){
      temp = ValidMoves[m];

      if(temp.size() != 0){

        if(board[temp[0]] == 1){
          //Make sure there is a peg for jump pt
          if(board[temp[1]] == 1){
            //Make sure there IS NOT a peg end pt...
            if(board[temp[2]] == 0){
                nextMoves.push_back(temp);

            } //end of endPeg 0 check (end must have no peg)
          } // end of jumpPeg 1 check (middle must have peg)
        }
      }
    else{
      //break;
      //continue;
    }
  }//end for
  return nextMoves;
}


//check to see if board is solved (AKA has one peg)
bool solved(int board[49]){
  int pegFound = 1;
  int totalPegs = 0;
  int rows_columns = 0;

  while(rows_columns < 49){
    // if I find a 1 on the board
    if(board[rows_columns] == pegFound){
      totalPegs++;
    }
    rows_columns++;
  }//end while loop
  // if there is more than 1 peg return false;
  if(totalPegs > 1){
    return false;
  }
  else {
    return true;
  }
}

// Solves using DFS
bool solve(int in_board[49], vector<vector <int>>& moveSeq){

  int out_board[49];

  if(solved(in_board)){
    return true;
  }
  //Get ALL VALID MOVES (for current state of board)
  vector<vector<int>> currentMoves = nextMoves(in_board); // CONTAINS set of all possible next moves
  for(int m = 0; m < currentMoves.size(); m++) {

    //out_board is my y....
    //(out_board is the altered board after a move is made)
    makeMove(in_board, currentMoves[m], out_board);

    if(solve(out_board, moveSeq) == true){
      //push the cur move to the moveSeq 2d vector
      moveSeq.push_back(currentMoves[m]);
      return true;
    }
  }
  //if it goes through all of the moves and solved is not true, return false...
  return false;

}



bool hsolve(int in_board[49], vector<vector <int>> &moveSeq, HashTable<long long int> &H, int size) {
  // check if solved already...

  int out_board[49];


  if(solved(in_board)) {
    return true;
  }
  //Get ALL VALID MOVES (for current state of board)
  vector<vector<int>> currentMoves = nextMoves(in_board); // CONTAINS set of all possible next moves
  //for every move (vector of moves) in currentMoves
  for(int m = 0; m < currentMoves.size(); m++){

  //out_board is my y
   makeMove(in_board, currentMoves[m], out_board);
   long long int y = 0;
   //(hash table is of type long long int)
   //convert to long long int so it can be inserted into hash table
   for(int i = 0; i < 49; i ++){
     long long int position = i;
     if(out_board[i] == 1){
       //left bitwise shift...
       y = y | 1LL << position;
     }
    }
    //if y is not within Hash table
    if(H.contains(y) == false) {

      if(hsolve(out_board,moveSeq,H,size)){
        //push move vectors to the moveSeq for Solution OUTPUT
        moveSeq.push_back(currentMoves[m]);
        return true;
      }
      else {
        if(H.getSize() <= size){
          H.insert(y);
        }
      }
    }//end of check for y within the hash table
  }
  return false;
}

/*
void displayBoard(int board[49]){


  //int index = 0;
  //cout << setw(5);

  for(int index = 0; index < 49; index++){
  // 2x2 corners
    if(board[index] == 2){
      cout << " ";
    }
    //peg
    else if(board[index] == 1){
      cout << "*";
    }
    //no peg
    else if(board[index] == 0){
      cout << "o";
    }
    if((index%7)==0){
      cout << endl;
    }

 }
}*/

int main(){

  int i;
  string filename;
/*
  // cout << "Index:\n";
  for(int i = 0; i < 47; i++){
    cout << i << ' ';

  }
  cout << endl;
  //cout << "\nPeg or empty (1 or 0):\n";
  for(int i = 0; i < 47; i++){
  if(i >= 10) {
    cout << ' ';
  }
  cout << board[i] << ' ';
  }
 cout << endl;
*/
  int counter = 0;
  int choice = 5;

  while(choice){

    //set board to have no pegs
    int board[49] = {2,2,0,0,0,2,2,2,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,2,2,0,0,0,2,2,2,2,0,0,0,2,2};

    cout << "\nEnter a .txt file containing the starting board position: ";
    cin >> filename;
    ifstream input(filename);
    while(input.is_open() == false){
      cout << "\n\nERROR: File does not exist.\n";
      exit(1);
    }
    // change board accordingly
    while(input >> i){
      board[i] = 1;
    }

   cout << "\nOptions: (1) Run DFS w/out hash table, (2) Run DFS using open hashing, (3) Quit\n";
   cin >> choice;

   //NO HASHING
    if(choice == 1)
    {
      //contains the moves used to win...
      vector<vector<int>> moveSeq;

      // need variable to hold value once I calculate totalTime
      double totalTime;
      // variable of type clock_t to store start time
      clock_t start_time = clock();

      bool solveResult = solve(board, moveSeq);

      clock_t end_time = clock();
      //calculate TotalTime for building the Tree
      totalTime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
      cout << "\nDFS (No Hashing) Solution:";

      if(solveResult == true){
        //get each triplet (accept last one) in reverse order...
        for(int triplets = moveSeq.size()-1; triplets >= 0;triplets--){
          cout<< "(";
          //get each move index from the triplets
          for(int move = 0; move < 2; move++){
            cout<< moveSeq[triplets][move] << ' ';
          }
          //get last value and put closing )
          cout << moveSeq[triplets][2] << ") ";
        }
        cout << "\n\nCPU Time: " << totalTime << endl << endl;
      }
      else {
        cout << " No solution\n\n";
        cout << "CPU Time (No Hashing): " << totalTime << endl << endl;

      }
    }// end choice == 1

    else if(choice == 2)
    {


    /*---------------------------------------------*/
    /*                                             */
    /*              Hash 10,000                    */
    /*                                             */
    /*---------------------------------------------*/
      vector<vector<int>>moveSeq1;
      //HashTable Size: 10,000
      HashTable<long long int>hash1(10000);

      // need variable to hold value once I calculate totalTime
      double totalTime1;
      // variable of type clock_t to store start time
      clock_t start_time1 = clock();

      //HashTable Size: 10,000
      bool hashSolveResult1 = hsolve(board, moveSeq1, hash1, 10000);

      clock_t end_time1 = clock();

      totalTime1 = (double)(end_time1 - start_time1) / CLOCKS_PER_SEC;

      cout << "\nStoring failed board positions in the hash table of size 10,000:\n";
      cout <<"\nSolution: ";
      int display1 = 0;
      if(hashSolveResult1 == true){
        cout << endl;
        // iterate backwards through the moveSeq vector
        for(int triplets = moveSeq1.size()-1; triplets >= 0;triplets--){
          cout<< "(";
          //get each move from vector (index:0, 1)
          for(int move = 0; move < 2; move++){
            cout<< moveSeq1[triplets][move] << ' ';
          }
        //get last value (index:2) and put closing )
          cout << moveSeq1[triplets][2] << ") ";
          //prevents from running off terminal window
          if (display1 == 10){
            cout << endl;
          }
          if (display1 == 20){
            cout << endl;
          }
          display1++;
        }
        cout << "\n\nCPU Time for storing in hash table (10,000): " << totalTime1 << endl << endl;
      }
      else{
        cout << "No Solution!\n";
        cout << "\nCPU Time for storing in hash table (10,000): " << totalTime1 << endl << endl;

      }

    /*---------------------------------------------*/
    /*                                             */
    /*              Hash 50,000                    */
    /*                                             */
    /*---------------------------------------------*/

      //HashTable Size: 50,000
      vector<vector<int>>moveSeq2;
      HashTable<long long int>hash2(50000);

      double totalTime2;
      clock_t start_time2 = clock();

      bool hashSolveResult2 = hsolve(board, moveSeq2, hash2, 50000);

      clock_t end_time2 = clock();

      totalTime2 = (double)(end_time2 - start_time2) / CLOCKS_PER_SEC;

      cout << "\nStoring failed board positions in the hash table of size 50,000:\n";
      cout <<"\nSolution:";
      int display2 = 0;
      if(hashSolveResult2 == true){
        cout << endl;
        // iterate backwards through the moveSeq vector
        for(int triplets = moveSeq2.size()-1; triplets >= 0;triplets--){
          cout<< "(";
          //get each move from vector (index:0, 1)
          for(int move = 0; move < 2; move++){
            cout<< moveSeq2[triplets][move] << ' ';
          }
        //get last value (index:2) and put closing )
          cout << moveSeq2[triplets][2] << ") ";
          if (display2 == 10){
            cout << endl;
          }
          if (display2 == 20){
            cout << endl;
          }
          display2++;
        }
        cout << "\n\nCPU Time for storing in hash table (50,000): " << totalTime2 << endl << endl;
      }
      else{

        cout << " No Solution!\n";
        cout << "\nCPU Time for storing in hash table (50,000): " << totalTime2 << endl << endl;

      }


      /*---------------------------------------------*/
      /*                                             */
      /*              Hash 100,000                   */
      /*                                             */
      /*---------------------------------------------*/

        //HashTable Size: 100,000
        vector<vector<int>>moveSeq3;
        HashTable<long long int>hash3(100000);


        double totalTime3;
        clock_t start_time3 = clock();

        bool hashSolveResult3 = hsolve(board, moveSeq3, hash3, 100000);

        clock_t end_time3 = clock();
        //calculate TotalTime for building the Tree
        totalTime3 = (double)(end_time3 - start_time3) / CLOCKS_PER_SEC;

        cout << "\nStoring failed board positions in the hash table of size 100,000:\n";
        cout <<"\nSolution:";
        int display3 = 0;
        if(hashSolveResult3 == true){
          cout << endl;
          // iterate backwards through the moveSeq vector
          for(int triplets = moveSeq3.size()-1; triplets >= 0;triplets--){
            cout<< "(";
            //get each move from vector (index:0, 1)
            for(int move = 0; move < 2; move++){
              cout<< moveSeq3[triplets][move] << ' ';
            }
          //get last value (index:2) and put closing )
            cout << moveSeq3[triplets][2] << ") ";
            if (display3 == 10){
              cout << endl;
            }
            if (display3 == 20){
              cout << endl;
            }
            display3++;
          }
          cout << "\n\nCPU Time for storing in hash table (100,000): " << totalTime3 << endl << endl;

        }
        else{

          cout << " No Solution!\n";
          cout << "\nCPU Time for storing in hash table (100,000): " << totalTime3 << endl << endl;

        }



  }

    else if(choice == 3)
    {

      cout << "\n\nExiting program...\n\n";
      exit(1);
    }
    counter++;

  }
  return 0;
}
