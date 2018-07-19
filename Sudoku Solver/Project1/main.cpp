#include <iostream>
#include "sud.h"
#include <windows.h>
using namespace std;

int inSudoku[9][9] = //0's indicate an unknowkn value
{
{ 7,9,0,0,0,0,6,0,0 },
{ 0,0,3,9,0,4,0,0,0 },
{ 0,0,0,0,8,0,0,9,3 },//row,column
{ 0,3,2,0,0,0,0,0,0 },
{ 9,0,7,0,4,0,2,0,0 },
{ 8,1,0,2,0,0,9,0,7 },
{ 0,7,9,4,2,0,0,0,0 },
{ 0,0,0,5,0,0,7,6,0 },
{ 1,0,0,0,3,0,5,0,9 },
};

sud puz(inSudoku);


int main()
{
	puz.check();
	puz.nakedSingles();
	puz.hiddenSingles();
	


	//out checked puzzle
	for (int j = 0; j < 9; j++) {
		for (int k = 0; k < 9; k++) {
			for (int i = 0; i < 9; i++) {
				cout << puz.workSud[j][k][i] << ", ";
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}


		for (int k = 0; k < 9; k++) {
			for (int i = 0; i < 9; i++) {
				cout << puz.inSudoku[k][i] << ", ";
			}
			cout << endl;
		}
		cout << endl << endl;
		cout << endl << endl;

		//Success /missing numbers
		int success = 0;
		for (int k = 0; k < 9; k++) {
			for (int i = 0; i < 9; i++) {
				if (inSudoku[i][k] != puz.inSudoku[i][k]) success++;
			}
		}
		cout << success << endl;
	
		Sleep(60000);

	return 0;
}