/*
 * Heuristics.h
 *
 *  Created on: Feb 24, 2016
 *      Author: Raymond
 */

#ifndef HEURISTICS_H_
#define HEURISTICS_H_

int heu1(Board &B, bool is_first) {
	/* checking all possible-winning lines
	 * the count methods are in Board_Checker.h
	 */

	int sum = 0,tsum;
	int mark, T = min(B.row,B.col);
	if (is_first) mark = 1;
	else mark = -1;
	// row
	for (int i=0;i<B.row;i++) {
		for (int j=0;j<B.col;j++) {
			if (j+T>B.col) break;
			tsum = row_count(B,mark,i,j);
			if (tsum>0) sum++;
		}
	}
	// column
	for (int i=0;i<B.row;i++) {
		if (i+T>B.row) break;
		for (int j=0;j<B.col;j++) {
			tsum = col_count(B,mark,i,j);
			if (tsum>0) sum ++;
		}
	}
	// top-left-bottom right diagonal
	for (int i=0;i<B.row;i++) {
		if (i+T>B.row) break;
		for (int j=0;j<B.col;j++) {
			if (j+T>B.col) break;
			tsum = diag_count1(B,mark,i,j);
			if (tsum>0) sum ++;
		}
	}
	//  top-left-bottom-right diagonal
	for (int i=0;i<B.row;i++) {
		if (i+T>B.row) break;
		for (int j=0;j<B.col;j++) {
			if (j-(T-1)<0) continue; // careful!!
			tsum = diag_count2(B,mark,i,j);
			if (tsum>0) sum++;
		}
	}
	return sum;
}

#endif /* HEURISTICS_H_ */
