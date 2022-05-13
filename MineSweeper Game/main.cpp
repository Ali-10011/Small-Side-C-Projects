#include <iostream>													//I have applied Inheritance when MasterBoard and Userboard inherits Minesweeper
#include <stdio.h>													//I have achieved Polymorphism when  when I made minesweeper an abstract class and overloaded its print functions
#include <stdlib.h>													//I have achieved Abstraction when I made the data members private, hiding the data from user and using getter functions instead
#include <ctime>													//At Last, Encapsulation is already achieved by class which combined the data members and member functions into one
using namespace std;
class Minesweeper {				//abstract base 
public:
	virtual void print() = 0; //pure virtual print function
};
class MasterBoard : public Minesweeper { //derived class from Minesweeper which prints and manages the locations of mines and the numbers
private:
	char board[5][5];			//masterboard, with all locations uncovered 
public:
	MasterBoard() { //a default constructor basically just makes a random  masterboard with the help of mines which are scattered on random locations
		for (int i = 0; i < 5; i++) { //initializing all board by 0 first
			for (int j = 0; j < 5; j++) {
				board[i][j] = '0';
			}
		}


		int tempx = 0;
		int tempy = 0;
		int count = 0;
		srand((unsigned)time(0));
		for (; count != 5;) {		//This function just makes 5 random mines anywhere on board
			do {
				tempx = 0 + (rand() % 5);
				tempy = 0 + (rand() % 5);
			} while ((tempx == 0 && tempy == 0) || (board[tempy][tempx] == 'X'));
			board[tempy][tempx] = 'X';
			count++;

		}
		AddNumbers(); //after the mines are made, this function is called
	}
	void AddNumbers() { //this function basically just adds the "numbers" to all locations by counting the mines in the vicinity of each location
		int count = 0;
		int row = 0;
		int	col = 0;
		for (int x = 0; x < 5; x++) { //as there are  8 possible locations, hence each coordinate is checked for these 8 locations
			for (int y = 0; y < 5; y++) {
				count = 0;
				row = 0;
				col = 0;
				if (board[x][y] != 'X') {
					row = x + 1;
					col = y - 1;
					if (row < 0 || row>4 || col < 0 || col>4) {

					}
					else {
						if (board[row][col] == 'X'){
							count++;
						}
					}
					row = x + 1;
					col = y;
					if (row < 0 || row>4 || col < 0 || col>4) {

					}
					else {
						if (board[row][col] == 'X') {
							count++;
						}
					}
					row = x + 1;
					col = y + 1;
					if (row < 0 || row>4 || col < 0 || col>4) {

					}
					else {
						if (board[row][col] == 'X') {
							count++;
						}
					}
					row = x;
					col = y + 1;
					if (row < 0 || row>4 || col < 0 || col>4) {

					}
					else {
						if (board[row][col] == 'X') {
							count++;
						}
					}
					row = x - 1;
					col = y + 1;
					if (row < 0 || row>4 || col < 0 || col>4) {

					}
					else {
						if (board[row][col] == 'X') {
							count++;
						}
					}
					row = x - 1;
					col = y;
					if (row < 0 || row>4 || col < 0 || col>4) {

					}
					else {
						if (board[row][col] == 'X') {
							count++;
						}
					}
					row = x - 1;
					col = y - 1;
					if (row < 0 || row>4 || col < 0 || col>4) {

					}
					else {
						if (board[row][col] == 'X') {
							count++;
						}
					}
					row = x;
					col = y - 1;
					if (row < 0 || row > 4 || col < 0 || col>4) {

					}
					else {
						if (board[row][col] == 'X') {
							count++;
						}
					}

					board[x][y] = char(count + 48); //after counting how many mines are located in the vicinity of each location, that number is added to master board
				}

			}
		}
	}
	void print() {		//overloaded print function
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}
	char get_location(int x, int y) {
		return board[x][y];
	}
};

class UserBoard : public Minesweeper { //This is basically the board that is printed on the user's side. This will contain all the input entered by user
private:							
	int moves;			//number of moves played by user
	char board[5][5];		//The board in which user inputs
public:
	UserBoard(){
		moves = 0;		//applying "*" to all locations on board
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				board[i][j] = '*';
			}
		}
	}
	bool TakeInput(MasterBoard & obj) {		//This function takes input from the user and processes it until it is valid, it will be called multiple times
		int x = -1;
		int y = -1;
		bool mine = false;
		do {
			if ((x < 0 || x>4) || (y < 0 || y>4)) {
				cout << "Please enter the row and column correctly between 0&4 " << endl;
			}
			else{
				if (this->board[x][y] != '*') {
					cout << "You have already made a move on this location ! Choice another !" << endl;
				}
			}

			cout << "Please enter row coordinate: ";
			cin >> x;
			cout << "Please enter column coordinate: ";
			cin >> y;

		} while ((x < 0 || x>4) || (y < 0 || y>4)||(this->board[x][y] !='*'));

		if (obj.get_location(x,y) == 'X') {
			system("CLS");
			cout << "oops, you stepped on a mine at " << x << "," << y << endl;
			this->board[x][y] = obj.get_location(x,y);
			this->moves = this->moves + 1;
			mine = true;
		}
		else {
			this->board[x][y] = obj.get_location(x,y);
			this->moves = this->moves + 1;

		}
		return mine;
	}
	void print() {
		for (int i = 0; i < 5; i++) {
			cout << i << " ";
			for (int j = 0; j < 5; j++) {
				cout <<board[i][j] << " ";
			}
			cout << endl;
		}
		cout << "Number of moves used: " << this->moves << endl;
	}
	char get_loc(int x, int y) {
		return this->board[x][y];
	}
	

};
				//HOW THIS ALL WORKS ??
				//Basically, we made two boards. One is in MasterBoard class which already has all of the locations of class uncovered
				//Second one, is the UserBoard which is displayed to the user at run time. The changes in this board are directly influenced by user's input
				//Both of these boards are connected through logic and when the user makes a move, the location one UserBoard is uncovered one by one
				//The game ends, when either the user uncovereds all "*" locations without stepping on a mine or if the user steps on a mine. In that case, the game immediately ends

int main() {
	UserBoard a; //board at the frontend
	MasterBoard b;//board at the backend
	Minesweeper*ptr = &a;
	bool mine = false;

	int count = 0;
	while (!(mine)) {		
		system("CLS");		//clears screen
		cout << endl << '\t' << "* Welcome to MINESWEEPER * " << endl;
		cout << endl;
		cout << "  ";
		for (int k = 0; k < 5; k++)
		{
			cout << k << " ";
		}
		cout << endl;
		ptr->print();
		mine = a.TakeInput(b);
		count = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (a.get_loc(i,j) == '*' || a.get_loc(i, j )== 'X') {					//counter to check if user completes the game without stepping on a mine	
				}
				else {
					count++;
				}
			}
		}
		if (count == 20) {
			break;
		}

	}
	if (mine) {		//The final output, which tells if user has won or not
		ptr->print();
		cout << endl << endl;
		ptr = &b;
		cout << "The true locations !" << endl;
		ptr->print();
	}
	else {
		system("CLS");
		ptr->print();
		cout << "You've Won !" << endl;
	}
	system("pause");
	return 0;
}
