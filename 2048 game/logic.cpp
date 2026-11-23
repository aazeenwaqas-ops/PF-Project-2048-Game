#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
int board[4][4], score = 0, bestscore = 0;

void initializeboard() {
	for (int row = 0; row < 4;row++) {
		for (int col = 0;col < 4;col++) {
			board[row][col] = 0;
		}
	}
	score = 0;
}
void generatetile() {
	int empty = 0; //counts all positions that are empty
	for (int row = 0;row < 4;row++) {
		for (int col = 0; col < 4;col++) {
			if (board[row][col] == 0) {
				empty++;
			}
		}
	}
	if (empty == 0) { //if board is full (no empty positions), function is exited
		return;
	}
	int randompos = rand() % empty; //selecting random empty position (remainder when dividing an int by empty can only be between 0 and (empty - 1))
	for (int row = 0;row < 4;row++) {
		for (int col = 0;col < 4;col++) {
			if (board[row][col] == 0) { //only consider empty positions
				if (randompos == 0) { //is selected position reached
					int randomval = rand() % 10;
					if (randomval < 9) {
						board[row][col] = 2; //90%
					}
					else {
						board[row][col] = 4; //10%
					}
					return;
				}
				randompos--; //if current is empty but not selected position
			}
		}
	}
}
void setupgame() {
	srand(time(0)); //seeds random num generator
	initializeboard(); //new board with random tiles setup
	generatetile();
	generatetile(); //game begins with 2 tiles
}
bool shiftleft() {
	bool moved = false;
	for (int row = 0;row < 4;row++) {
		for (int col = 0;col < 4;col++){
			if (board[row][col] == 0) {
				for (int nextcol = col + 1;nextcol < 4;nextcol++) {
					if (board[row][nextcol] != 0) {
						board[row][col] = board[row][nextcol];
						board[row][nextcol] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	return moved;
}

bool moveleft() {
	bool moved = shiftleft();
	for (int row = 0; row < 4; row++) { // merging adjacent tiles
		for (int col = 0; col < 3; col++) {
			if (board[row][col] != 0 && board[row][col] == board[row][col + 1]) {
				board[row][col] = board[row][col] * 2;
				board[row][col + 1] = 0;
				score = score + board[row][col];
				if (score > bestscore) {
					bestscore = score;
				}
				moved = true;
				col++;
			}
		}
	}
	shiftleft(); // removing empty spaces created by merging
	return moved;
}
bool shiftright() {
	bool moved = false;
	for (int row = 0; row < 4; row++) {
		for (int col = 3; col >= 0; col--) {
			if (board[row][col] == 0) {
				for (int nextcol = col - 1; nextcol >= 0; nextcol--) {
					if (board[row][nextcol] != 0) {
						board[row][col] = board[row][nextcol];
						board[row][nextcol] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	return moved;
}
bool moveright() {
	bool moved = shiftright();
	for (int row = 0; row < 4; row++) {
		for (int col = 3; col > 0; col--) {
			if (board[row][col] != 0 && board[row][col] == board[row][col - 1]) {
				board[row][col] = board[row][col] * 2;
				board[row][col - 1] = 0;
				score = score + board[row][col];
				if (score > bestscore) {
					bestscore = score;
				}
				moved = true;
				col--;
			}
		}
	}
	shiftright();
	return moved;
}
bool shiftup() {
	bool moved = false;
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			if (board[row][col] == 0) {
				for (int nextrow = row + 1; nextrow < 4; nextrow++) {
					if (board[nextrow][col] != 0) {
						board[row][col] = board[nextrow][col];
						board[nextrow][col] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	return moved;
}
bool moveup() {
	bool moved = shiftup();
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 3; row++) {
			if (board[row][col] != 0 && board[row][col] == board[row + 1][col]) {
				board[row][col] = board[row][col] * 2;
				board[row + 1][col] = 0;
				score = score + board[row][col];
				if (score > bestscore) {
					bestscore = score;
				}
				moved = true;
				row++;
			}
		}
	}
	shiftup();
	return moved;
}
bool shiftdown() {
	bool moved = false;
	for (int col = 0; col < 4; col++) {
		for (int row = 3; row >= 0; row--) {
			if (board[row][col] == 0) {
				for (int nextrow = row - 1; nextrow >= 0; nextrow--) {
					if (board[nextrow][col] != 0) {
						board[row][col] = board[nextrow][col];
						board[nextrow][col] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	return moved;
}
bool movedown() {
	bool moved = shiftdown();
	for (int col = 0; col < 4; col++) {
		for (int row = 3; row > 0; row--) {
			if (board[row][col] != 0 && board[row][col] == board[row - 1][col]) {
				board[row][col] = board[row][col] * 2;
				board[row - 1][col] = 0;
				score = score + board[row][col];
				if (score > bestscore) {
					bestscore = score;
				}
				moved = true;
				row--;
			}
		}
	}
	shiftdown();
	return moved;
}
bool checkwin() {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4;col++) {
			if (board[row][col] == 2048) {
				return true;
			}
		}
	}
	return false;
}
bool checkgameover() { //no empty cell left or no merging possible
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4;col++) {
			if (board[row][col] == 0) {
				return false;
			}
			if (col < 3 && board[row][col] == board[row][col + 1]) {
				return false;
			}
			if (row < 3 && board[row][col] == board[row + 1][col]) {
				return false;
			}
		}
	}
	return true;
}
void loadbestscore() {
	ifstream file("bestscore.txt");
	if (file.is_open()) {
		file >> bestscore;
		file.close();
	}
}
void savebestscore() {
	ofstream file("bestscore.txt");
	if (file.is_open()) {
		file << bestscore;
		file.close();
	}
}
