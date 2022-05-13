#include <iostream>
using namespace std;

int main() {
	int rows = 0,columns = 0;
	cout << "Please enter the number of rows of your 2D array: ";
	cin >> rows;
	cout << "Please enter the number of columns of your 2D array: ";
	cin >> columns;
	int **ptr = new int *[rows];
	for (int c = 0; c < rows; c++) {
		ptr[c] = new int[columns];
	};
	for (int i = 0; i < rows; i++) {
		for (int c = 0; c < columns; c++) {
			cout << "Please fill row number " << (i + 1) << ": ";
			cin >> *(*(ptr + i) + c);
		}
		cout << endl;
	}
	cout << endl;
	cout << "This is the array you entered" << endl;
	for (int i = 0; i < rows; i++) {
		for (int c = 0; c < columns; c++) {
			cout << *(*(ptr + i) + c) << " ";
		}
		cout << endl;
	}
	
	
	int **resultant = new int *[rows]; //because the resultant array will have atmost the number of rows the input array has
	int resrow = 0; // number of rows the 2D array will have;
	int rescol = 0; //number of columns of a specific row of the resultant array
	bool fill = false;
	for (int i = 0; i < rows; i++) {
		rescol = 0;
		for (int c = 0; c < columns; c++) {
			if (*(*(ptr + i) + c) > 0) {
				rescol++;
			}
		}
		if (rescol > 0) {
			resultant[resrow] = new int[rescol];
			resrow++;
		}
	} //now we have all the lengths of each row sorted out for the resultant array !
	if (resrow == 0) {
		cout << "There are all 0 entered in the entered array" << endl;
		system("pause");
		return 0;
	}
	int j = 0;
	cout << "This is the new array " << endl;
	for (int i = 0; i < rows; i++) {
		for (int c = 0, k =0; c < columns; c++) {
			if (*(*(ptr+i)+c) > 0) {
				*(*(resultant + j) + k) = *(*(ptr + i) + c);
				cout << *(*(resultant + j) + k) << " ";
				k++;
				fill = true;
			}
		}
		if (fill) { //That we can move the next array.
			j++;
		}
		fill = false;
		cout << endl;
	}
	

	system("pause");
	return 0;
}