#include "SolitaireGame.h"
#include <iostream>
#include <fstream>
using namespace std;

int** board;
int a, b, temp;

SolitaireGame::SolitaireGame()
{
	Username();
	setupBoard();
}

void SolitaireGame::setupBoard()
{
	
	{
		a = 8;
		b = 8;
		board = new int*[a];
		for (int i = 1; i < a; i++)
			board[i] = new int[b];
		
		{
			for (int y = 1; y < a; y++)
			{
				for (int x = 1; x < b; x++)
				{
					if ((y == 1 || y == 2 ||y == 6 || y == 7)
							&& (x == 1 || x == 2 || x == 6|| x == 7)) 
							{								
								board[x][y] = 2;
							}
					else if ((y == 4) && (x == 4))
					{
						board[x][y] = 0;
					}
					else
						board[x][y] = 1;
				}
			}
		}
	}
}

int SolitaireGame::Username()
{
   fstream file; 
   file.open("Leaderboard.txt",ios::app);
    if(!file)
   {
       cout<<"Error in creating file!!!"<<endl;
       return 0;
   }
   cout<< "Welcome!"<<endl;
   cout<< "Enter your name : "<<endl;
   char name[100];
   cin >> name;
   file<< name;  
   file.close();
}

void SolitaireGame::Entry(int a)
{
	fstream file;
	file.open("LeaderBoard.txt",ios::app);
	file<< " : " << a << " marbles left on the board ";
	file << "\n";
}

int SolitaireGame::LeaderBoard()
{
   fstream file;
   char ch; //to read single character
   cout<<"Your position on the leaderboard: "<<endl;    
   int co = winBoard();
   Entry(co);
   file.open("LeaderBoard.txt",ios::in);
   if(!file)
   {
       cout<<"Error in opening file for reading!!!"<<endl;
       return 0;
   }   
   while(!file.eof())
   {
       file>>ch;
       cout << ch;
	}
   file.close();    
   return 0;
}

void SolitaireGame::displayBoard()
{
	cout << "The initial state of your board is: " <<endl << endl;
	for (int y = 1; y < 9; y++)
	{
		for (int x = 1; x < 9; x++)
		{
			
			if (board[x][y] == 2)
				cout << " \t";
			else  if (board[x][y] == 1)
				cout << board[x][y] << "\t";
			else if (board[x][y] == 0)
				cout << board[x][y] << "\t";
			else 
				cout << "idf_row_num"<<"\t";
		}
		cout << "\n\n";
	}
}
void SolitaireGame::Welcome()
 {
 	cout << endl << "There are a set of marbles, represented by the number 1, placed on the board with only the centre portion left vacant represented by number 0. All you have to do is move one marble over the other either horizontally or vertically (diagonal moves are not allowed).";
 	cout << " As soon as you do this, the marble over which you move the other marble disappears." << endl;
 	cout << "Continue moving one marble over the other until there is only one marble left" << endl;
 	cout << "Consider the board as a 7x7 matrix, access the elements by entering the row and column number." << endl;
 	cout << "If you want to move the element present at the 4th row in the 2nd column, enter the numbers 4 and 2." << endl;
 }

int SolitaireGame::Selection()
{
	int f_col_num, f_row_num, t_col_num, t_row_num; 
	cout << "Enter the row and column number of the marble you want to move " <<endl;
	cin >> f_row_num;
	cin >> f_col_num;
	if (((1 <= f_row_num ) && (f_row_num <= 7)) && ((1 <= f_col_num ) && (f_col_num <= 7)))
	{
		if ((((f_row_num == 1) || (f_row_num == 2)) || ((f_row_num == 5) || (f_row_num == 6))) && (((f_col_num == 1) || (f_col_num == 2)) || ((f_col_num == 5) || (f_col_num == 6))))
		{
			cout << "You have selected to move an invalid marble"<<endl;
			return 0;
		}
		else
		{ 
			cout << "You have selected to move the element present at column: " << f_row_num << " and column: " << f_col_num <<endl << endl;
			cout << "Enter the destination for this marble"<<endl;
			cin >> t_row_num;
			cin >> t_col_num;
			if (((1 <= t_row_num ) && (t_row_num <= 7)) && ((1 <= t_col_num ) && (t_col_num <= 7)))
			{
				if ((f_row_num == t_row_num) && (f_col_num == t_col_num))
				{
					cout << "The initial and final position of the marble cannot be same" << endl;
					return 0;
				}
				else if ((((t_row_num == 1) || (t_row_num == 2)) || ((t_row_num == 5) || (t_row_num == 6))) && (((t_col_num == 1) || (t_col_num == 2)) || ((t_col_num == 5) || (t_col_num == 6))))
				{		
					cout << "You have selected to move an invalid marble"<<endl;
					return 0;
				}	
				else if (((f_row_num - t_row_num) == 0) || ((f_row_num - t_row_num) == 2) || ((f_row_num - t_row_num) == -2) && (((f_col_num - t_col_num) == 0) || ((f_col_num - t_col_num) == 2) || ((f_col_num - t_col_num) == -2)))
					{
						//cout << "Subtraction condition true"<<endl<<endl;
						if ((board[t_row_num][t_col_num]) - (board[f_row_num][f_col_num]) == -1 )
						{
							cout << "Marble subtraction also true at " << board[f_row_num][f_col_num] << " to " << board[t_row_num][t_col_num] <<endl;
					    	board[f_row_num][f_col_num] = 0;
					    	board[t_row_num][t_col_num] = 1;
					    	if ( (f_row_num - t_row_num) != 0  && (f_col_num - t_col_num) == 0)
					    	{ 
					    		if(f_row_num > t_row_num)
					    		{
					    			board[f_row_num - 1][f_col_num] = 0;
								}
								else
								{
									board[t_row_num - 1][t_col_num] = 0;
								}
					    	
							}
							else if ( (f_row_num - t_row_num) == 0  && (f_col_num - t_col_num) != 0)
					    	{ 
					    		if(f_col_num > t_col_num)
					    		{
					    			board[f_row_num][f_col_num - 1] = 0;
								}
								else
								{
									board[t_row_num][t_col_num - 1] = 0;
								}
							}
							else { cout << "Please make a valid selection"<<endl;
									 return 0;}
					    	
						}
						else { cout << "Cannot move marble over empty space. "<<endl; 
								return 0;
						}
							cout<< "The marble from row: "<< f_row_num << " and column: "<< f_col_num << " has been moved to row: " << t_row_num << " and column: " << t_col_num <<endl;
							cout << "Positions of marbles on the new board:"<<endl<<endl;
							for (int y = 1; y < 8; y++)
							{
								for (int x = 1; x < 8; x++)
								{
									if ((y == 1 || y == 2 ||y == 6 || y == 7)
									&& (x == 1 || x == 2 || x == 6|| x == 7)) 
									{	cout << " \t"; }								
									else if (board[x][y] == 0)
										cout << 0 << "\t";
									else if (board[x][y] == 1)
										cout << 1 << "\t";		
									else 
										cout << 1 <<"\t";
								}
								cout << "\n\n";
							}
					 	return 1;
						}
						else return 0;
					}
	
		
		else 
			{
				cout << "Enter a valid row and column number ranging between 0 and 6"<<endl;
				return 0;
			}
		}
		
}
	else 
		{
			cout << "Enter a valid row and column number ranging between 0 and 6"<<endl;
			return 0;
		}
}

int SolitaireGame::winBoard()
{
	int count = 0;
	for (int y = 1; y < 8; y++)
	{
		for (int x = 1; x < 8; x++)
		{
			if (board[x][y] == 1){
				count++;
			}
		}
	}
	return count;
}

void SolitaireGame::Recurssion()
{
	int num = 0;
	int i =1;
	num = Selection();
	
	if (winBoard() == 1)
		{
			cout << "Congratulation! You are a genius!"<<endl;
			LeaderBoard();
		}
	else if( i = num)
	{
		--i;
		Recurssion();
	}
	else {
		char c;
		cout << "Do you wish to continue? Y for Yes N for No"<< endl;
		cin >> c;
		if (c == 'y')
		{
			Recurssion();
		}
		else
		{
			cout << "You opted to quit the game"<<endl;
			LeaderBoard();
		 } 
	}
	
}



int main()
{
	int num;
	SolitaireGame game;
	game.Welcome();
	game.displayBoard();
	game.Recurssion();
		
}
