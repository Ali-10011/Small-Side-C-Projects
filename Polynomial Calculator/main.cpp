#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <Windows.h>
#include <stdlib.h>

using namespace std;
void sorting(int& terms, int deg[], int coef[]);
void Input(int & terms, int  deg[], int coef[]);
void Input(string filename, int & terms, int deg[], int coef[]);
int Solve(int terms, int deg[], int coef[], int variable);void Add(int & aterms, int adeg[], int acoef[], int & bterms, int bdeg[], int bcoef[],
	int & rterms, int rdeg[], int rcoef[]);void Subtract(int & aterms, int adeg[], int acoef[], int& bterms, int bdeg[], int bcoef[],
	int& rterms, int rdeg[], int rcoef[]);bool Equal(int & aterms, int adeg[], int acoef[], int & bterms, int bdeg[], int bcoef[]);void Print(int & terms, int deg[], int coef[]);void Multiply(int & aterms, int adeg[], int acoef[], int & bterms, int bdeg[], int bcoef[],
	int & rterms, int rdeg[], int rcoef[]);void Menu();
int main() {
	//this code can check for redundacies when the user inputs, but it will not check for them when input from file(no instructions were specified)
	//but this code will sort both in descending order nonetheless 
	string afilename;
	string bfilename;
	int aterms = 0;
	int bterms = 0;
	int rterms = 0;
	int variable;
	int answer = 0;
	int adeg[15];
	int acoef[15];
	int bdeg[15];
	int bcoef[15];
	int rdeg[225];	//15*15 = 225
	int rcoef[225];
	char option = 'a';
	int mini = 0;
	int token = 0;
	bool eq = false;

	while (int(option) != 8) {
		system("CLS");
		Menu();
		cout << "Your Option: ";
		cin >> option;	//Please only enter integers, and not strings and chars.
		option = int(option) - 48;
		if (int(option) == 0) {
			cin.ignore();
			if (token == 1) {
				cout << "Note: You have already taken input, you are taking it again" << endl;
			}
			cout << "Enter the name of your first file: ";
			getline(cin, afilename);
			cout << "Enter the name of your second file: ";
			getline(cin, bfilename);
			cout << "Please wait..." << endl;
			Sleep(2000);
			ifstream read;
			read.open(afilename);
			ifstream readb;
			readb.open(bfilename);
			if ((read.is_open()) && (readb.is_open())) {
				read.close();
				readb.close();
				token = 1;
				Input(afilename, aterms, adeg, acoef);
				Input(bfilename, bterms, bdeg, bcoef);
				cout << "Done !" << endl;
				system("pause");
			}
			else {
				cout << "One or more files doesn't exit" << endl;
				system("pause");
			}
		}
		if (int(option) == 1) {
			if (token == 1) {
				cout << "Note: you have alread taken input, you are taking it again" << endl;
			}
			cout << "Please enter the number of terms in your first polynomial: ";
			cin >> aterms;
			cout << "Please enter the number of terms in your second polynomial: ";
			cin >> bterms;
			Input(aterms, adeg, acoef);
			Input(bterms, bdeg, bcoef);
			token = 1;
			system("pause");
		}
		if (int(option) == 2) {
			if (token == 1) {
				cout << "Please enter the value of variable to solve polynomial: ";
				cin >> variable;
				while (mini < 1 || mini>2) {	//please only enter int here
					cout << "Which polynomial do you want to solve ? Enter 1 for first, and 2 for second: ";
					cin >> mini;
				}
				if (mini == 1) {
					cout << "Answer is " << Solve(aterms, adeg, acoef, variable) << endl;
					system("pause");
				}
				if (mini == 2) {
					cout << "Answer is " << Solve(bterms, bdeg, bcoef, variable) << endl;
					system("pause");
				}
			}
			else {
				cout << "Please take input first !" << endl;
				system("pause");
			}
		}
		if (int(option) == 3) {
			if (token == 1) { // to check if the user has taken input first or not
				mini = 0;
				while (mini < 1 || mini>3) {
					cout << "Which polynomial do you want to print ? Enter 1 for first, 2 for second and 3 for both: ";
					cin >> mini;
				}
				if (mini == 1) {
					Print(aterms, adeg, acoef);
					system("pause");
				}
				if (mini == 2) {
					Print(bterms, bdeg, bcoef);
					system("pause");
				}
				if (mini == 3) {
					cout << "First Polynomial: ";
					Print(aterms, adeg, acoef);
					cout << endl;
					cout << "Second Polynomial: ";
					Print(bterms, bdeg, bcoef);
					system("pause");
				}
			}
			else {
				cout << "Please take input first" << endl;
				system("pause");
			}
		}
		if (int(option) == 4) {
			if (token == 1) {
				Multiply(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
				cout << "Result is: ";
				Print(rterms, rdeg, rcoef);
				cout << endl;
				system("pause");
			}
			else {
				cout << "Please take input first" << endl;
				system("pause");
			}

		}
		if (int(option) == 5) {
			if (token == 1) {
				Subtract(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
				cout << "Result is: ";
				Print(rterms, rdeg, rcoef);
				cout << endl;
				system("pause");
			}
			else {
				cout << "Please take input first" << endl;
				system("pause");
			}

		}
		if (int(option) == 6) {
			if (token == 1) {
				Add(aterms, adeg, acoef, bterms, bdeg, bcoef, rterms, rdeg, rcoef);
				cout << "Result is: ";
				Print(rterms, rdeg, rcoef);
				cout << endl;
				system("pause");
			}
			else {			
					cout << "Please take input first" << endl;
					system("pause"); 
			}

		}
		if (int(option) == 7) {
			if (token == 1) {
				eq = Equal(aterms, adeg, acoef, bterms, bdeg, bcoef);
				if (eq == true) {
					cout << "Both polynomials are equal" << endl;
				}
				else {
					cout << "Both polynomials are not equal" << endl;
				}
				system("pause");
			}
			else {

				cout << "Please take input first" << endl;
				system("pause");
			}
		}
		if (int(option) == 8) {
			cout << "Take Care." << endl;
			system("pause");
		}
		if (int(option) <0 || int(option)>8) {
			cout << "Invalid Option entered Please try again. " << endl;
			system("pause");
		}
	}
	return 0;
}

void sorting(int& terms, int deg[], int coef[]) { //to sort program degrees and their coefcients in desending order
	int c = 0;	int c1 = 0;	int temp = 0;	while (c != terms) {		while (c1 != terms) {			if (deg[c1 + 1] > deg[c1]) {				temp = deg[c1];				deg[c1] = deg[c1 + 1];				deg[c1 + 1] = temp;				temp = coef[c1];				coef[c1] = coef[c1 + 1];				coef[c1 + 1] = temp;			}			c1++;		}		c1 = 0;		c++;	}
}
void Input(int & terms, int deg[], int coef[]) {
	int c = 0;
	int c1 = 0;
	bool present = false;
	cout << "Please enter the degrees of your polynomials in descending order: ";
	cin >> deg[c];
	c = c + 1;
	while (c != terms) {
		cout << "Please enter the degrees of your polynomials in descending order: ";
		cin >> deg[c];
		c1 = 0;
		present = false;
		while (c1 < c) {
			if (deg[c1] == deg[c]) {
				cout << "This degree is already present, Please enter another " << endl;
				present = true;
			}
			c1++;
			if (present == true) {
				c1 = c;
				c--;
			}
		}
		c++;
	}
	c = 0;
	while (c != terms) {
		cout << "Please enter the coeffcients of the degree you entered in the same order: ";
		cin >> coef[c];
		c++;
	}
	sorting(terms, deg, coef);
}
void Input(string filename, int & terms, int  deg[], int coef[]) {
	ifstream read;
	int c = 0;
	read.open(filename);
	while (!(read.eof())) {
		read >> terms;
		while (c != terms) {
			read >> coef[c];
			c++;
		}
		c = 0;
		while (c != terms) {
			read >> deg[c];
			c++;
		}
	}
	read.close();
	sorting(terms, deg, coef);
}
int Solve(int terms, int deg[], int coef[], int variable) {
	int sum = 0;
	int c = 0;
	while (c != terms) {
		sum = sum + (coef[c] * (pow(variable, deg[c])));
		c++;
	}
	return sum;
}
void Add(int & aterms, int adeg[], int acoef[], int & bterms, int bdeg[], int bcoef[],
	int & rterms, int rdeg[], int rcoef[]) {
	int c = 0;
	int c1 = 0;
	int index = 0;
	int r = 0;

	while ((c1 != bterms) || (c != aterms)) {
		if (adeg[c] > bdeg[c1]) {
			rdeg[r] = adeg[c];
			rcoef[r] = acoef[c];
			r++;
			c++;
			index++;
		}

		else if (adeg[c] < bdeg[c1]) {
			rdeg[r] = bdeg[c1];
			rcoef[r] = bcoef[c];
			r++;
			c1++;
			index++;
		}
		else if (adeg[c] == bdeg[c1]) {
			rdeg[r] = adeg[c];
			rcoef[r] = acoef[c] + bcoef[c1];
			r++;
			c++;
			c1++;
			index++;
		}
	}
	if (c == aterms) {
		int temp = 0;
		temp = c1;
		while (temp != bterms) {
			rdeg[r] = bdeg[c1];
			rcoef[r] = bcoef[c1];
			temp++;
			index++;
		}
	}
	if (c1 == bterms) {
		int temp = 0;
		temp = c;
		while (temp != aterms) {
			rdeg[r] = bdeg[c];
			rcoef[r] = bcoef[c];
			temp++;
			index++;
		}
	}
	rterms = index;

}
void Subtract(int &aterms, int adeg[], int acoef[], int& bterms, int bdeg[], int bcoef[],
	int& rterms, int rdeg[], int rcoef[]) {	int c = 0;
	int c1 = 0;
	int index = 0;
	int r = 0;

	while ((c1 != bterms) || (c != aterms)) {
		if (adeg[c] > bdeg[c1]) {
			rdeg[r] = adeg[c];
			rcoef[r] = acoef[c];
			r++;
			c++;
			index++;
		}

		else if (adeg[c] < bdeg[c1]) {
			rdeg[r] = bdeg[c1];
			rcoef[r] = -1 * bcoef[c];
			r++;
			c1++;
			index++;
		}
		else if (adeg[c] == bdeg[c1]) {
			rdeg[r] = adeg[c];
			rcoef[r] = acoef[c] - bcoef[c1];
			r++;
			c++;
			c1++;
			index++;
		}
	}
	if (c == aterms) {
		int temp = 0;
		temp = c1;
		while (temp != bterms) {
			rdeg[r] = bdeg[c1];
			rcoef[r] = -1 * bcoef[c1];
			temp++;
			index++;
		}
	}
	if (c1 == bterms) {
		int temp = 0;
		temp = c;
		while (temp != aterms) {
			rdeg[r] = bdeg[c];
			rcoef[r] = -1 * bcoef[c];
			temp++;
			index++;
		}
	}	rterms = index;}bool Equal(int & aterms, int adeg[], int acoef[], int & bterms, int bdeg[], int bcoef[]) {	int c = 0;	bool equal = true;	if (aterms != bterms) {		equal = false;		return equal;	}	while (c != aterms) {		if (adeg[c] == bdeg[c]) {		}		else {			equal = false;			return equal;		}		c++;	}	c = 0;	while (c != aterms) {		if (acoef[c] == bcoef[c]) {		}		else {			equal = false;			return equal;		}		c++;	}	return equal;}void Print(int & terms, int deg[], int coef[]) {	int c = 0;	while (c < terms) {		if (deg[c] != 0) {			if (coef[c] < 0) {				cout << coef[c] << "x^" << deg[c];			}			else if (coef[c] > 0) {				if (c == 0) {					cout << coef[c] << "x^" << deg[c];				}				else {					cout << "+" << coef[c] << "x^" << deg[c];				}			}		}		else if (deg[c] == 0) {			if (coef[c] < 0) {				cout << coef[c];			}			else if (coef[c] > 0) {				cout << "+"<< coef[c];			}		}		c++;	}	cout << endl;}void Multiply(int & aterms, int adeg[], int acoef[], int & bterms, int bdeg[], int bcoef[],
	int & rterms, int rdeg[], int rcoef[]) {	int c = 0;	int c1 = 0;	int c2 = 0;	int tempd = 0;	int tempc = 0;	int rep = 0;	while (c1 != bterms) {		rcoef[c1] = acoef[c] * bcoef[c1];		rdeg[c1] = adeg[c] + bdeg[c1];		c1++;	}	rterms = c1;	c1 = 0;	c++;	while (c != aterms) {		while (c1 != bterms) {			tempd = adeg[c] + bdeg[c1];			tempc = acoef[c] * bcoef[c1];			while (c2 < rterms) {				if (tempd == rdeg[c2]) {					rcoef[c2] = rcoef[c2] + tempc;					c2 = 0;					rep = 1;				}				c2++;				if (rep == 1) {					c2 = rterms;				}			}			if (rep == 1) {				c2 = 0;			}			rep = 0;			if (c2 == rterms) {				rdeg[rterms] = tempd;				rcoef[rterms] = tempc;				rterms++;			}			c2 = 0;			c1++;		}		c++;		c1 = 0;	}	sorting(rterms, rdeg, rcoef);}void Menu() {	cout << "0) Input two polynomials from files." << endl;	cout << "1) Input two polynomials from the user." << endl;	cout << "2) Solve one of the polynomials for a value(result is also printed)." << endl;	cout << "3) Print the polynomials(you will be given more options for printing)." << endl;	cout << "	i." << "\t" << "First polynomial." << endl;	cout << "	ii." << "\t" << "Second polynomial." << endl;	cout << "	iii." << "\t" << "Both polynomails." << endl;	cout << "4) Multiply the polynomials(result is also printed)." << endl;	cout << "5) Subtract the polynomials(result is also printed)." << endl;	cout << "6) Add the polynomials(prints the result as well)." << endl;	cout << "7) Check if both polynomials are equal." << endl;	cout << "8) Exit." << endl;	cout << endl;}