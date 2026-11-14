#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int board[4][4], score = 0;

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