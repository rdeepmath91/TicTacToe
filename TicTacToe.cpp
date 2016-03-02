/* * TicTacToe.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: Raymond
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <time.h>

using namespace std;

#define PII pair<int,int>

ofstream file ("moves.txt");

#include "input_checker.h"
#include "Board.h"
#include "Player.h"

Board B; // the TicTacToe board
Human_Player H,H2;
AI_Player A,A2;
Player *P[2], *cur_player;
int GAME_COUNT = 0;

void ask_board_size() {
	int r,c;
	char res;
	while (res!='y' && res!='n') {
		cout << "Do you want to play a default game? (y/n)\n";
		cin >> res;
		if (res=='y') B = Board();
		else if (res=='n') {
			while (true) {
				cout << "Please input the board size\n";
				string in;
				cout << "Row = "; cin >> in;
				if (!is_num(in)) {
					cout << "Invalid input.\n";
					continue;
				}
				r = s_to_num(in);
				cout << "Col = "; cin >> in;
				if (!is_num(in)) {
					cout << "Invalid input.\n";
					continue;
				}
				c = s_to_num(in);
				if (r*c > BOARD_LIMIT) {
					cout << "The board size exceeds the limit (" << BOARD_LIMIT << " squares).\n";
					continue;
				}
				break;
			}
			B = Board(r,c);
		}
		else cout << "Invalid input.\n";
	}
	cout << "Playing with a " << B.row << "x" << B.col << " board...\n";
}

void ask_order() {
	char res;
	while (res!='y' && res!='n') {
		cout << "Are you playing first? (y/n)\n";
		cin >> res;
		if (res=='y') {
			H.set_first();
			cout << "You will be playing first.\n";
			// uncomment if there's a 2nd AI player
			// A2.set_first();
			// cout << A2.name << " will be playing first.\n";
			B.print_board(1);
		}
		else if (res=='n'){
			A.set_first();
			cout << A.name << " will be playing first.\n";
		}
		else cout << "Invalid input.\n";
	}
}

void play() {
	GAME_COUNT++;
	cout << "---Starting a generalized Tic Tac Toe---\n";
	file << "[Game " << GAME_COUNT << "]";
	ask_board_size();
	file << " - " << B.row << "x" << B.col << " board\n";
	H = Human_Player();
	A = AI_Player(); A.set_strat("Expert2");
	// uncomment the next line to add 2nd AI player
	// A2 = AI_Player(); A2.set_strat("Expert1"); A2.name = "Expert1";
	cout << A.name << " will be your opponent.\n";
	ask_order();
	if (H.is_first) {
		P[0] = &H;
		//P[1] = &H2; // uncomment to add 2nd human player
		P[1] = &A;
		//P[0] = &A2; // uncomment to add 2nd AI player
	}
	else {
		P[0] = &A;
		//P[0] = &H2; // uncomment to add 2nd human player
		P[1] = &H;
		//P[1] = &A2; // uncomment to add 2nd AI player
	}
	int player_ind = 0;
	while (true) {
		cur_player = P[player_ind];
		file << cur_player->name << ": ";
		B = cur_player->move(B);
		if (cur_player->is_victorious) break;
		if (B.check_draw()) {
			cout << "It's a draw.\n";
			file << "It's a draw.\n";
			return;
		}
		player_ind = 1-player_ind;
	}
	file << endl;
}

int main() {
	while (true) {
		cout << "Please choose one of the following options (type 1, 2, or 3):\n";
		cout << "[1] New Game\n";
		cout << "[2] Rules - PLEASE READ if you haven't played this game before.\n";
		cout  << "[3] Exit\n";
		string in;
		cin >> in;
		if (!is_num(in)) {
			cout << "Invalid Input.\n";
			continue;
		}
		int choice = s_to_num(in);
		if (choice==1) play();
		else if (choice==2) {
			cout << "[RULES]\n";
			cout << "1. You can either play a default game (3x3) ";
			cout << "or simply choose the board size.\n";
			cout << "2. The first player marks his choice with X, the second with O.\n";
			cout << "3. You win if you put N consecutive marks (vertically, horizontally or diagonally) \n";
			cout <<	"where N is the smaller between the number of rows and columns of the board.\n";
			cout << "(Ex.: If you play 3x5, then one needs to put 3 consecutive Xs or Os to win)\n";
		}
		else if (choice==3) break;
		else cout << "Invalid input.\n";
		cout << endl;
	}
	file.close();
	cout << "Thank you for playing!\n";
	return 0;
}

