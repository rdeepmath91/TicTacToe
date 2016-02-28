/*
 * TicTacToe.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: Raymond
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <time.h>

using namespace std;

#define PII pair<int,int>

#include "input_checker.h"
#include "Board.h"
#include "Player.h"

Board B; // the TicTacToe board
Human_Player H,H2; // the Human players
AI_Player A,A2; // the AI players
Player *P[2], *cur_player;

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
			B.print_board(1);
		}
		else if (res=='n'){
			A.set_first();
			cout << A2.name << " will be playing first.\n";
		}
		else cout << "Invalid input.\n";
	}
}

void play() {
	cout << "---Starting a generalized Tic Tac Toe---\n";
	ask_board_size();
	H = Human_Player();
	A = AI_Player(); A.set_strat("Expert");
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
		//P[0] = &A2; // uncomment to add 2nd AI player
		P[1] = &H;
		//P[0] = &H2; // uncomment to add 2nd human player
	}
	int player_ind = 0;
	while (B.num_empty) {
		cur_player = P[player_ind];
		B = cur_player->move(B);
		if (cur_player->is_victorious) break;
		player_ind = 1-player_ind;
	}
	if (!P[0]->is_victorious && !P[1]->is_victorious) cout << "It's a draw.\n";
}

int main() {
	while (true) {
		cout << "Please choose one of the following options (type 1,2 or 3):\n";
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
	cout << "Thank you for playing!\n";
	return 0;
}

