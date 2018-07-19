#include "sud.h"
#include <iostream>
using namespace std;

void sud::LtoB()
{		//block format
	//0,1,2
	//3,4,5,
	//6,7,8
	int i = 0;
	int j = 0;
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {

			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					sudBlock[i][j] = inSudoku[3 * a + x][3 * b + y];
					j++;
				}
			}
			i++;
			j = 0;
		}
	}

	i = 0;
	j = 0;
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {

			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					for (int q = 0; q < 9; q++) {
						workBlock[i][j][q] = workSud[3 * a + x][3 * b + y][q];
					}
					
					j++;
				}
			}
			i++;
			j = 0;
		}
	}

}

void sud::BtoL(){
	int i = 0; int j = 0;

	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			for (int c = 0; c < 3; c++) {
				for (int d = 0; d < 3; d++) {

					for (int z = 0; z < 9; z++) {
					workSud[3 * a + c][3 * b + d][z] = workBlock[i][j][z];
					}
					j++;
				}
			}
			i++;
			j = 0;
		}
	}
}

int sud::convert(int i, int j, int pos) {
	int p = 3 * floor(i / 3) + floor(j / 3); // block number
	i = i % 3; j = j % 3;
	int l = j + 3 * i; //in block

	if(pos) return  l;
	else return p;
}//line coordinates to block coordinates

bool sud::equal(int first[9], int second[9])
{
	int e = 0;
	for (int i = 0; i < 9; i++)
	{
		if (first[i] == second[i]) e++;
	}
	if (e == 9) { return true; }
	else return false;
}

int sud::single(int arr[9]) {
	int r = 0;
	for (int i = 0; i < 9; i++) { if (arr[i] != 0) { r++; } }

	if (r != 1) { return 0; }

	int y = 0;
	for (int i = 0; i < 9; i++) { 
		if (arr[i] != 0) { return arr[i]; }
	}
}

int sud::count(int arr[9]) {
	int r = 0;
	for (int i = 0; i < 9; i++) { if (arr[i] != 0) { r++; } }

	return r;
}

sud::sud(int in[9][9])
{		//line format
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			inSudoku[i][j] = in[i][j];
		}
	}
	
	//fill with numbers
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 1; k < 10; k++) {
				workSud[i][j][k - 1] = k;
			}
		}
	}

	LtoB();//convert to sudBlock;
	clearTemp();
	
}

sud::~sud()
{
}

void sud::clearTemp(){
	for (int i = 0; i < 9; i++) { temp[i] = 0; }
}




void sud::check() {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//for each number in the workSud grid

			//row
				for (int y=0; y < 9; y++) {

					if (inSudoku[i][y] != 0) { workSud[i][j][inSudoku[i][y]-1] = 0; }
				}
			//column
				for (int y=0; y < 9; y++) {

					if (inSudoku[y][j] != 0) { workSud[i][j][inSudoku[y][j]-1] = 0; }
				}
			//block
				for (int y=0; y < 9; y++) {
					

					if (sudBlock[convert(i,j,0)][y] != 0) { workSud[i][j][sudBlock[convert(i, j,0)][y] - 1] = 0; }
				}

		}
	}
}

void sud::nakedSingles() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if(inSudoku[i][j]==0){
				if(single(workSud[i][j])!=0){
					inSudoku[i][j] = single(workSud[i][j]);
				}
			}
		}
	}

	LtoB();
}

void sud::hiddenSingles()
{ 
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//for each number in the workSud grid

			if (inSudoku[i][j] == 0) {
				//row
				for (int k = 0; k < 9; k++) { temp[k] = workSud[i][j][k]; }
				for (int y = 0; y < 9; y++) {
					for (int z = 0; z < 9; z++) {

						if (y != j && inSudoku[i][y] == 0) if (workSud[i][y][z] == temp[z]) { temp[z] = 0; }
					}
				}
				if (single(temp) != 0) { inSudoku[i][j] = single(temp); break; }

				//column
				for (int k = 0; k < 9; k++) { temp[k] = workSud[i][j][k]; }
				for (int y = 0; y < 9; y++) {
					for (int z = 0; z < 9; z++) {

						if (y != i && inSudoku[y][j] == 0) if (workSud[y][j][z] == temp[z]) { temp[z] = 0; }
					}
				}
				if (single(temp) != 0) { inSudoku[i][j] = single(temp); break; }
				//block
				for (int k = 0; k < 9; k++) { temp[k] = workSud[i][j][k]; }
				for (int y = 0; y < 9; y++) {
					for (int z = 0; z < 9; z++) {

						if (y != convert(i, j, 1) && workBlock[convert(i, j, 0)][y] == 0) if (workBlock[convert(i, j, 0)][y][z] == temp[z]) { temp[z] = 0; }
					}
				}
				if (single(temp) != 0) { inSudoku[i][j] = single(temp); break; }
			}//end of if

		}
	}
	clearTemp();
	LtoB();

}

void sud::nakedPair()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//for each number in the workSud grid
			if (inSudoku[i][j] == 0) {
				
				for (int a = 0; a < 9; a++) {
					for (int b = 0; b < 9; b++) {
	
						if (equal(workSud[i][j], workSud[a][b]) && inSudoku[a][b] == 0 && count(workSud[i][j]) == 2 && count(workSud[a][b]) == 2 && (i!=a||j!=b)) {
								//row
							if (i == a) {
								for (int y = 0; y < 9; y++) {
									if (y != a && y != i) { 
										for (int z = 0; z < 9; z++) {
											workSud[i][y][z] -= workSud[i][j][z];
										}
									}
								}
								LtoB();
							}
								//column
							if (j == b) {
								for (int y = 0; y < 9; y++) {
									if (y != b && y != j) {
										for (int z = 0; z < 9; z++) {
											workSud[y][j][z] -= workSud[i][j][z];
										}
									}
								}
								LtoB();
							}
								//block
							if (convert(i, j, 0) == convert(a, b, 0)) {
								
								for (int y = 0; y < 9; y++) {
									if (y != convert(i,j,1) && y != convert(a,b,1)) {
										for (int z = 0; z < 9; z++) {
											workBlock[convert(i, j, 0)][y][z] -= workSud[i][j][z];
										}
									}
								}
								BtoL();
							}


						}
					}
				}


			}
		}
	}
}

void sud::pointingPair() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//for each number in the workSud grid
			if (inSudoku[i][j] == 0) {

				for (int a = 0; a < 9; a++) {
					for (int b = 0; b < 9; b++) {

						if (equal(workSud[i][j], workSud[a][b]) && inSudoku[a][b] == 0 && count(workSud[i][j]) == 2 && count(workSud[a][b]) == 2 && (i != a || j != b)) {
							//row
							if (i == a) {
								for (int y = 0; y < 9; y++) {
									if (y != a && y != i) {
										for (int z = 0; z < 9; z++) {
											workSud[i][y][z] -= workSud[i][j][z];
										}
									}
								}
								LtoB();
							}
							//column
							if (j == b) {
								for (int y = 0; y < 9; y++) {
									if (y != b && y != j) {
										for (int z = 0; z < 9; z++) {
											workSud[y][j][z] -= workSud[i][j][z];
										}
									}
								}
								LtoB();
							}
							//block
							if (convert(i, j, 0) == convert(a, b, 0)) {

								for (int y = 0; y < 9; y++) {
									if (y != convert(i, j, 1) && y != convert(a, b, 1)) {
										for (int z = 0; z < 9; z++) {
											workBlock[convert(i, j, 0)][y][z] -= workSud[i][j][z];
										}
									}
								}
								BtoL();
							}


						}
					}
				}


			}
		}
	}for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//for each number in the workSud grid
			if (inSudoku[i][j] == 0) {

				for (int a = 0; a < 9; a++) {
					for (int b = 0; b < 9; b++) {

						if (equal(workSud[i][j], workSud[a][b]) && inSudoku[a][b] == 0 && count(workSud[i][j]) == 2 && count(workSud[a][b]) == 2 && (i != a || j != b)) {
							//row
							if (i == a) {
								for (int y = 0; y < 9; y++) {
									if (y != a && y != i) {
										for (int z = 0; z < 9; z++) {
											workSud[i][y][z] -= workSud[i][j][z];
										}
									}
								}
								LtoB();
							}
							//column
							if (j == b) {
								for (int y = 0; y < 9; y++) {
									if (y != b && y != j) {
										for (int z = 0; z < 9; z++) {
											workSud[y][j][z] -= workSud[i][j][z];
										}
									}
								}
								LtoB();
							}
							//block
							if (convert(i, j, 0) == convert(a, b, 0)) {

								for (int y = 0; y < 9; y++) {
									if (y != convert(i, j, 1) && y != convert(a, b, 1)) {
										for (int z = 0; z < 9; z++) {
											workBlock[convert(i, j, 0)][y][z] -= workSud[i][j][z];
										}
									}
								}
								BtoL();
							}


						}
					}
				}


			}
		}
	}
}

void sudr() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//for each number in the workSud grid
			if (inSudoku[i][j] == 0) {

				for (int a = 0; a < 9; a++) {
					for (int b = 0; b < 9; b++) {

						if (equal(workSud[i][j], workSud[a][b]) && inSudoku[a][b] == 0 && count(workSud[i][j]) == 2 && count(workSud[a][b]) == 2 && (i != a || j != b)) {
							//row
							if (i == a) {
								for (int y = 0; y < 9; y++) {
									if (y != a && y != i) {
										for (int z = 0; z < 9; z++) {
											workSud[i][y][z] -= workSud[i][j][z];
										}
									}
								}
								LtoB();
							}
							//column
							if (j == b) {
								for (int y = 0; y < 9; y++) {
									if (y != b && y != j) {
										for (int z = 0; z < 9; z++) {
											workSud[y][j][z] -= workSud[i][j][z];
										}
									}
								}
								LtoB();
							}
							//block
							if (convert(i, j, 0) == convert(a, b, 0)) {

								for (int y = 0; y < 9; y++) {
									if (y != convert(i, j, 1) && y != convert(a, b, 1)) {
										for (int z = 0; z < 9; z++) {
											workBlock[convert(i, j, 0)][y][z] -= workSud[i][j][z];
										}
									}
								}
								BtoL();
							}


						}
					}
				}


			}
		}
	}
}