/*
 * Board.h
 *
 *  Created on: Feb 20, 2016
 *      Author: Raymond
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Board_Checker.h"
#define BOARD_LIMIT 50

class Board{

	bool update_line(pair<int,bool> &line, int cur_player,int limit) {
		/* update a specific line after adding new mark within it
		 * return true iff the line is a win
		*/

		if (line.second) {
			if (line.first*cur_player>=0) {
				line.first += cur_player;
				if (abs(line.first)==limit) return true;
			}
			else {
				line.second = false;
				BC.pos_lines--;
			}
		}
		return false;
	}

	bool update(int cur_player, int x, int y) {
		/* update the vectors for lines as cur_player makes a move at (x,y)
		 cur_player = 1 for 1st player, = -1 for 2nd player
		 return true if cur_player wins, else return 0
		 */
		int T = min(row,col);
		pair<int,bool> tmp;
		// check row lines
		for (int i=max(y-(T-1),0);i<=y;i++) {
			if (i+T>col) break;
			if (row<col) {
				if (update_line(BC.row_L[x*(col-row+1)+i],cur_player,T)) return true;
			}
			else if (update_line(BC.row_L[x],cur_player,T)) return true;
		}

		// check column lines
		for (int i=max(x-(T-1),0);i<=x;i++) {
			if (i+T>row) break;
			if (row<col) {
				if (update_line(BC.col_L[y],cur_player,T)) return true;
			}
			else if (update_line(BC.col_L[i+y*(row-col+1)],cur_player,T)) return true;
		}

		int t1,t2;
		// check diag1 line
		t1 = x-min(x,y);
		t2 = y-min(x,y);
		if (row<col) {
			if (t1==0 && t2+T<=col)
				if (update_line(BC.diag1_L[t2],cur_player,T)) return true;
		}
		else {
			if (t1+T<=row && t2==0)
				if (update_line(BC.diag1_L[t1],cur_player,T)) return true;
		}

		// check diag2 line
		t1 = x+min(row-1-x,y);
		t2 = y-min(row-1-x,y);
		if (row<col) {
			if (t1==row-1 && t2+T<=col)
				if (update_line(BC.diag2_L[t2],cur_player,T)) return true;
		}
		else {
			if (t1>=T-1 && t2==0)
				if (update_line(BC.diag2_L[t1-(T-1)],cur_player,T)) return true;
		}
		return 0;
	}

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


	void print_board_checker() {
		cout << "Print row lines...\n";
		for (int i=0;i<(int) BC.row_L.size();i++)
			cout << "Row Line " << i << ": " << BC.row_L[i].first << " " << BC.row_L[i].second << endl;

		cout << "Print col lines...\n";
		for (int i=0;i<(int)BC.col_L.size();i++)
			cout << "Col Line " << i << ": " << BC.col_L[i].first << " " << BC.col_L[i].second << endl;

		cout << "Print diag1 lines...\n";
		for (int i=0;i<(int)BC.diag1_L.size();i++)
			cout << "Diag1 Line " << i << ": " << BC.diag1_L[i].first << " " << BC.diag1_L[i].second << endl;

		cout << "Print Diag2 lines...\n";
		for (int i=0;i<(int)BC.diag2_L.size();i++)
			cout << "Diag2 Line " << i << ": " << BC.diag2_L[i].first << " " << BC.diag2_L[i].second << endl;
	}

	void print_board(int sp) {
		for (int i=0;i<row;i++) {
			for (int j=0;j<2*col+1;j++) {
				cout << "-";
				file << "-";
			}
			cout << endl;
			file << endl;
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
			cout << "|" << endl;
			file << "|" << endl;
		}
		for (int i=0;i<2*col+1;i++) {
			cout << "-";
			file << "-";
		}
		cout << endl;
		file << endl;
		//print_board_checker();
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
		/* cur_player put a mark at (x,y)  */
		int cur_player = is_first ? 1:-1;
		board[x][y] = cur_player;
		if(update(cur_player, x,y))
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
