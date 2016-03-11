/*
 * Board.h
 *
 *  Created on: Feb 20, 2016
 *      Author: Raymond
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Board_Checker.h"

class Board{



public:
	int row;
	int col;
	int num_empty;
	int who_wins; // 0,1,-1 = none,1st,2nd player wins
	vector<vector<int> > board;
	Board_Checker BC;

	void create_board() {
		vector<int> v;
		for (int i=0;i<col;i++) v.push_back(0);
		for (int i=0;i<row;i++)
			board.push_back(v);
		v.clear();
		num_empty = row*col;
		who_wins = 0;
		BC = Board_Checker(row,col);
	}

	// default constructor 3x3
	Board() {
		row = 3;
		col = 3;
		create_board();
	}

	Board(int r, int c) {
		row = r;
		col = c;
		create_board();
	}

	void print_board(int sp) {
		cout << "    ";
		file << "    ";
		for (int i=0;i<col;i++) {
			cout << i+1 << " ";
			file << i+1 << " ";
		}
		cout << "\nROW";
		file << "\nROW";
		for (int j=0;j<2*col+1;j++) {
			cout << "-";
			file << "-";
		}
		cout << endl;
		file << endl;
		for (int i=0;i<row;i++) {
			// to change if # of row >= 10
			cout << " " << i+1 << " ";
			file << " " << i+1 << " ";
			for (int j=0;j<col;j++) {
				cout << "|";
				file << "|";
				if (board[i][j]==1) {
					cout << "X";
					file << "X";
				}
				else if (board[i][j]==-1) {
					cout << "O";
					file << "O";
				}
				else {
					cout << " ";
					file << " ";
				}
			}
			cout << "|" << endl << "   ";
			file << "|" << endl << "   ";
			for (int j=0;j<2*col+1;j++) {
				cout << "-";
				file << "-";
			}
			cout << endl;
			file << endl;
		}
		//BC.print_board_checker();
	}

	bool is_empty(int x,int y) {
		/* return true if position (x,y) has not been filled yet */
		return (board[x][y]==0);
	}

	vector<PII> valid_moves()  {
		/* list of all valid moves in a vector */
		vector<PII> v;
		for (int i=0;i<row;i++)
			for (int j=0;j<col;j++)
				if (is_empty(i,j)) v.push_back(make_pair(i,j));

		return v;
	}

	void put(bool is_first, int x, int y) {
		/* cur_player marks his move at (x,y)  */
		int cur_player = is_first ? 1:-1;
		board[x][y] = cur_player;
		if(BC.update(cur_player,x,y,row,col))
			who_wins = cur_player;
		num_empty--;
	}

	bool check_draw() {
		/* check whether the board still has some winnable lines */
		return (BC.pos_lines == 0);
	}

	bool is_terminal() {
		if (num_empty==0 || who_wins!=0) return true;
		return false;
	}

};

#endif /* BOARD_H_ */
