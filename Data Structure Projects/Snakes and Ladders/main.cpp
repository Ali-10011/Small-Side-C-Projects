#include <iostream>
#include <queue>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

void game() {
	queue<string> Names; //Separate Queues for storing Names/Score/Winner in order
	queue<int> Score;
	queue<string> Winner;
	string temp;
	int random_num = 0;
	int players = 0;
	int temp_num = 0;
	string temp_name;
	do{								//This loop asks for input from user, number of players, their names and initializes their scores with 0
		cout << "Please enter the number of players that are playing the game(1-10): ";
		cin >> players;
	} while (players <= 0 || players > 10);
	for (int i = 0; i < players; i++) {
		cout << "Please enter the name of Player no " << i + 1 << " :";
		cin >> temp;
		Names.push(temp);
		Score.push(0);
	}
	cout << endl << "Let the Game Begin !" << endl;			//As it says ! Let the game begin !
	for (; players > 1;) { //As a player's score reaches 100, the total number of players are subtracted by 1
		for (int j = 0; j < players; j++) { //all players getting their turns
			random_num = 0;
			temp_num = 0;
			srand(time(NULL)); //randomizes time ...well every time !
			cout << endl;
			cout << "It is " << Names.front() << "'s turn" << endl;  //displays the name and current score of player, whose turn is next
			cout << "Current Score: " << Score.front() << endl;
			system("pause");
			random_num = (rand() % 6) + 1; //generates a random number 
			cout << endl;
			cout << Names.front() << " rolled a " << random_num << endl;
			if ((Score.front() + random_num) > 100) { //condition to not add score it it goes 100+
				temp_name = Names.front();
				temp_num = Score.front(); 
				Names.pop();		//All the players who had their turn, their names and score are pushed back into queue(in the back)
				Score.pop();
				Names.push(temp_name);
				Score.push(temp_num);
			}
			else if ((Score.front() + random_num) == 100) { //if the score is 100, then permanently dequeue from queue and push into another queue
				temp_num = Score.front() + random_num;
				cout << Names.front() << " has reached the end !" << endl;
				Winner.push(Names.front());
				Names.pop();
				Score.pop();
				players--;		//if a player has reached the end, the total number of players is decremented by 1

			}
			else {				//reward and penalty section
				if ((Score.front() + random_num) == 20) {
					cout << Names.front() << "has found a ladder at 20 ! Their score is now 40 !" << endl;
					temp_num = 40;
				}
				else if ((Score.front() + random_num) == 60) {
					cout << Names.front() << "has found a ladder at 60 ! Their score is now 75 !" << endl;
					temp_num = 75;
				}
				else if ((Score.front() + random_num) == 50) {
					cout << Names.front() << "has found a snake at 50 ! Their score is now 40 !" << endl;
					temp_num = 40 ;
				}
				else if ((Score.front() + random_num) == 90) {
					cout << Names.front() << "has found a snake at 90 ! Their score is now 79!" << endl;
					temp_num = 79;
				}
				else {
					temp_num = Score.front() + random_num;
				}
				cout << endl;
				temp_name = Names.front();
				Names.pop();
				Score.pop();
				Names.push(temp_name);
				Score.push(temp_num);
			}
			
		}
	}
	cout << endl << endl << endl;		
	for (int i = 0; !Winner.empty();i++) { //prints the list of winners, in the same order that they reached the end
		cout << "Place no " << i + 1 << " belongs to " << Winner.front() << endl;
		Winner.pop();
		
	}
	cout << endl << endl;
	cout << Names.front() << " loses the game !" << endl; //Prints the name of player who lost the game !

}



int main() {
	game();
	system("pause");
	return 0;
}