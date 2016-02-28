/*
 * Board.h
 *
 *  Created on: Feb 20, 2016
 *      Author: Raymond
 */

#ifndef BOARD_H_
#define BOARD_H_

#define BOARD_LIMIT 50

class Board{
public:
	int row;
	int col;
	int num_filled;
	int num_empty;
	int board[10][10];

	void create_board() {
		for (int i=0;i<row;i++) {
			for (int j=0;j<col;j++) {
				board[i][j] = 0;
			}
		}
		num_filled = 0;
		num_empty = row*col;
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

	Board(const Board& B) {
		row = B.row;
		col = B.col;
		num_filled = B.num_filled;
		num_empty = B.num_empty;
		for (int i=0;i<row;i++) {
			for (int j=0;j<col;j++) {
				board[i][j] = B.board[i][j];
			}
		}
	}

	void print_board(int sp) {
		for (int i=0;i<row;i++) {
			for (int j=0;j<2*col+1;j++) cout << "-";
			cout << endl;
			for (int j=0;j<col;j++) {
				cout << "|";
				if (board[i][j]==1) cout << "X";
				else if (board[i][j]==-1) cout << "O";
				else cout << " ";
			}
			cout << "|" << endl;
		}
		for (int i=0;i<2*col+1;i++) cout << "-";
		cout << endl;

		/*for (int i=0;i<row;i++) {
			for (int j=0;j<sp;j++) {
				cout << " ";
			}
			for (int j=0;j<col;j++) {
				if (board[i][j]==0) cout << "-";
				else if (board[i][j]==1) cout << "X";
				else if (board[i][j]==-1) cout << "O";
			}
			cout << endl;
		}*/
	}

	bool is_empty(int x,int y) {
		/* return true if position (x,y) has not been filled yet */
		//cout << x << " " << y << " " << board[x][y] << endl;
		return (board[x][y]==0);
	}

	vector<PII> valid_moves()  {
		/* list of all valid moves in a vector */
		vector<PII> v;
		for (int i=0;i<row;i++) {
			for (int j=0;j<col;j++) {
				if (is_empty(i,j)) {
					v.push_back(make_pair(i,j));
				}
			}
		}
		return v;
	}

	void put(bool is_first, int x, int y) {
		/* put O or X at (x,y) depending on whose turn it is currently */
		if (is_first) board[x][y] = 1;
		else board[x][y] = -1;
		num_filled++;
		num_empty--;
	}
};

#endif /* BOARD_H_ */
