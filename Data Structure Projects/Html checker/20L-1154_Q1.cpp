#include <iostream>
#include <stack>
#include <fstream>
#include <string>
using namespace std;
bool IsCorrect(string name) {
	stack<string> opening; //stores all the opening tags and pops opening tags whenever their closing tag is found
	string temp; 
	string push; //temp variable to push tag into the html file
	ifstream file;
	file.open(name);//open this file
	while (!file.eof()) { //do this while the end of file is not reached
		file >> temp;//reads one line
		push.clear(); 
		for (int i = 0; i < temp.length(); i++) { //do this loop until that whole line is read
			if (temp.at(i) == '<'){ //if an opeing tag is found, push it till the last closing bracket
				push.clear();
				if (temp.at(i + 1) != '/') { //if it is an opening and NOT closing
					i--;
					do {
						i++;
						push.push_back(temp.at(i)); //using chars to perform string operations

					} while (temp.at(i) != '>');
					opening.push(push); //push contains a whole tag and it pushes it into the stack
					push.clear(); //clears the push variabe

				} 
				else{  //if the tag is closing, then push the closing tag into a temp string
					push.clear();
					i--;
					do {
						i++;
						if (temp.at(i) != '/') {							
							push.push_back(temp.at(i));
						}

					} while (temp.at(i) != '>');
					//comparing the opening tag with the closing tag stored in temp variable
					if (opening.empty()) { //some  if and else conditions
						return false; 
					}
					if (opening.top() == push) { //if the first closing tag (as it should be) is at the coressponding to the tag at the top of stack then pop it
						opening.pop();
					}
					else {
						return false; //otherwise the html document is false
					}
				}
			}
		}
	}
		return (opening.empty());
}


int main() {
	bool temp;
	temp = IsCorrect("file.txt"); // name of file
	if(temp) {
		cout << "The HTML file is correct" << endl;
	}
	else {
		cout << "The HTML fie is not correct" << endl;
	}
	system("pause");
	return 0;
}