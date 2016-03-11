/*
 * Board_Checker.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Raymond Christopher
 */

#ifndef BOARD_CHECKER_H_
#define BOARD_CHECKER_H_

/* CLASS DESCRIPTION
 * Board_Checker will update the state of each lines everytime
 * a new mark is put on the board. A lines is a sequence of
 */

class Board_Checker {
	bool update_line(pair<int,bool> &line, int cur_player) {
		/* update a specific line after adding new mark within it
		 * return true iff the line is a win
		*/

		if (line.second) {
			if (line.first*cur_player>=0) {
				line.first += cur_player;
				if (abs(line.first)==WIN_SEQ) return true;
			}
			else {
				line.second = false;
				pos_lines--;
			}
		}
		return false;
	}

public:
	vector<pair<int,bool> > row_L, col_L;
	vector<pair<int,bool> > diag1_L, diag2_L;
	int pos_lines;

	Board_Checker() {
		pos_lines = 0;
	}

	Board_Checker(int row, int col) {
		pair<int,bool> tmp = make_pair(0,true);
		// row lines
		if (col>=WIN_SEQ){
			for (int i=0;i<row;i++)
				for (int j=0;j<(col-WIN_SEQ+1);j++)
					row_L.push_back(tmp);
		}

		// column lines
		if (row>=WIN_SEQ) {
			for (int i=0;i<col;i++) {
				for (int j=0;j<(row-WIN_SEQ+1);j++) {
					col_L.push_back(tmp);
				}
			}
		}
		// diagonal lines
		if (row>=WIN_SEQ && col>=WIN_SEQ) {
			for (int i=0;i<(row-WIN_SEQ+1);i++) {
				for (int j=0;j<(col-WIN_SEQ+1);j++) {
					diag1_L.push_back(tmp);
					diag2_L.push_back(tmp);
				}
			}
		}
		pos_lines = (int) row_L.size()+ (int) col_L.size();
		pos_lines += (int) diag1_L.size() + (int) diag2_L.size();
	}

	bool update(int cur_player, int x, int y, int row, int col) {
		/* update the vectors for lines as cur_player makes a move at (x,y)
		 cur_player = 1 for 1st player, = -1 for 2nd player
		 return true if cur_player wins after making the move, else return false
		 */
		// check row lines
		if (col>=WIN_SEQ) {
			for (int i=max(y-WIN_SEQ+1,0);i<=y;i++) {
				if (i+WIN_SEQ>col) break;
				if (update_line(row_L[x*(col-WIN_SEQ+1)+i],cur_player)) return true;
			}
		}

		// check column lines
		if (row>=WIN_SEQ) {
			for (int i=max(x-WIN_SEQ+1,0);i<=x;i++) {
				if (i+WIN_SEQ>row) break;
				if (update_line(col_L[i+y*(row-WIN_SEQ+1)],cur_player)) return true;
			}
		}

		int tmp;
		if (row>=WIN_SEQ && col>=WIN_SEQ) {
			// check NW-SE diagonals
			tmp = x - min(WIN_SEQ-1,min(x,y));
			for (int i=tmp;i<=x;i++) {
				if (i+WIN_SEQ>row) break;
				int j = i+(y-x);
				if (j+WIN_SEQ>col) break;
				if (update_line(diag1_L[i*(col-WIN_SEQ+1)+j],cur_player)) return true;
			}

			// check NE-SW diagonals
			tmp = x - min(WIN_SEQ-1,min(x,col-1-y));
			for (int i=tmp;i<=x;i++) {
				if (i+WIN_SEQ>row) break;
				int j = x+y-i;
				if (j-WIN_SEQ+1<0) break;
				if (update_line(diag2_L[i*(col-WIN_SEQ+1)+(j-WIN_SEQ+1)],cur_player)) return true;
			}
		}
		return false;
	}


	void print_board_checker() {
		cout << "WIN SEQ = " << WIN_SEQ << endl;
		cout << "Printing row lines...\n";
		for (int i=0;i<(int) row_L.size();i++)
			cout << "Row Line " << i << ": " << row_L[i].first << " " << row_L[i].second << endl;

		cout << "Printing col lines...\n";
		for (int i=0;i<(int)col_L.size();i++)
			cout << "Col Line " << i << ": " << col_L[i].first << " " << col_L[i].second << endl;

		cout << "Printing diag1 lines...\n";
		for (int i=0;i<(int)diag1_L.size();i++)
			cout << "Diag1 Line " << i << ": " << diag1_L[i].first << " " << diag1_L[i].second << endl;

		cout << "Printing Diag2 lines...\n";
		for (int i=0;i<(int)diag2_L.size();i++)
			cout << "Diag2 Line " << i << ": " << diag2_L[i].first << " " << diag2_L[i].second << endl;
	}
};

#endif /* BOARD_CHECKER_H_ */
