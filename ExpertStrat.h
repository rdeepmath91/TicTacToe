/*
 * ExpertStrat.h
 *
 *  Created on: Feb 24, 2016
 *      Author: Raymond
 */

#ifndef EXPERTSTRAT_H_
#define EXPERTSTRAT_H_

PII win_or_block(Board &B, int mark) {
	int T = min(B.row,B.col);

	for (int i=0;i<B.row;i++) {
		for (int j=0;j<B.col;j++) {
			if (j+T>B.col) break;
			if (row_count(B,0,i,j)==1 && row_count(B,mark,i,j)==T-1) {
				for (int k=0;k<T;k++) {
					if (B.board[i][j+k]==0) return make_pair(i,j+k);
				}
			}
		}
	}
	// col sum
	for (int i=0;i<B.row;i++) {
		if (i+T>B.row) break;
		for (int j=0;j<B.col;j++) {
			if (col_count(B,0,i,j)==1 && col_count(B,mark,i,j)==T-1) {
				for (int k=0;k<T;k++) {
					if (B.board[i+k][j]==0) return make_pair(i+k,j);
				}
			}
		}
	}
	// diag top left bottom right sum
	for (int i=0;i<B.row;i++) {
		if (i+T>B.row) break;
		for (int j=0;j<B.col;j++) {
			if (j+T>B.col) break;
			if (diag_count1(B,0,i,j)==1 && diag_count1(B,mark,i,j)==T-1) {
				for (int k=0;k<T;k++) {
					if (B.board[i+k][j+k]==0) return make_pair(i+k,j+k);
				}
			}
		}
	}
	// diag top left bottom right sum
	for (int i=0;i<B.row;i++) {
		if (i+T>B.row) break;
		for (int j=0;j<B.col;j++) {
			if (j-(T-1)<0) continue; // careful!!
			if (diag_count2(B,0,i,j)==1 && diag_count2(B,mark,i,j)==T-1) {
				for (int k=0;k<T;k++) {
					if (B.board[i+k][j-k]==0) return make_pair(i+k,j-k);
				}
			}
		}
	}
	return make_pair(-1,-1);
}

PII ExpertStrat(Board &B, bool is_first) {
	int mark = (is_first) ? 1 : -1;
	PII p = win_or_block(B,mark);
	if (p.first!=-1) {
		cout << "Win at ";
		return p;
	}
	p = win_or_block(B,-mark);
	if (p.first!=-1) {
		cout << "Block at ";
		return p;
	}
	return MM(B,is_first);
}


#endif /* EXPERTSTRAT_H_ */
