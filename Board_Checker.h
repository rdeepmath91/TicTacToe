/*
 * Board_Checker.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Raymond
 */

#ifndef BOARD_CHECKER_H_
#define BOARD_CHECKER_H_

class Board_Checker {
public:

	/*
	 * V.second = true if and only if the line is still winnable/just won
	 * The following are possible V.first values:
	 * 0 (non-marked, winnable)
	 * k>0 (marked by k Xs, no Os)
	 * k<0 (marked by k O's, no Xs)
	 */

	vector<pair<int,bool> > row_L, col_L;
	vector<pair<int,bool> > diag1_L, diag2_L;
	int pos_lines;

	Board_Checker() {
		pos_lines = 0;
	}

	Board_Checker(int row, int col) {
		pair<int,bool> tmp = make_pair(0,true);
		if (row<col) {
			for (int i=0;i<(col-row+1)*row;i++) row_L.push_back(tmp);
			for (int i=0;i<col;i++) col_L.push_back(tmp);
		}
		else {
			for (int i=0;i<row;i++) row_L.push_back(tmp);
			for (int i=0;i<(row-col+1)*col;i++) col_L.push_back(tmp);
		}
		for (int i=0;i<abs(row-col)+1;i++) {
			diag1_L.push_back(tmp);
			diag2_L.push_back(tmp);
		}
		pos_lines = (int) row_L.size()+ (int) col_L.size();
		pos_lines += (int) diag1_L.size() + (int) diag2_L.size();
	}
};

#endif /* BOARD_CHECKER_H_ */
