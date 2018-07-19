#pragma once
class sud
{
public:
	int workSud[9][9][9]; //9x9 dimension and the last is a list of possible values
	int workBlock[9][9][9];
	int inSudoku[9][9];
	int sudBlock[9][9];
	sud(int in[9][9]);
	~sud();
	
	void check();
	void nakedSingles();
	void hiddenSingles();
	void nakedPair();
	
private:
	int temp[9];

	void LtoB();
	void BtoL();
	bool equal(int first[9], int second[9]);
	int single(int arr[9]);
	int count(int arr[9]);
	int convert(int i, int j, int pos); 
	void clearTemp();
	
};

