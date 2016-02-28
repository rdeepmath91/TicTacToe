/*
 * Board_Checker.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Raymond
 */

#ifndef BOARD_CHECKER_H_
#define BOARD_CHECKER_H_

int row_count(Board &B, int mark, int row, int col) {
	/* left to right */
	int res = 0;
	for (int i=0;i<min(B.col,B.row);i++) {
		if (B.board[row][col+i]==mark) res++;
		else if (B.board[row][col+i]==-mark) return 0;
	}
	return res;
}

int col_count(Board &B, int mark, int row, int col) {
	/* top to bottom */
	int res = 0;
	for (int i=0;i<min(B.row,B.col);i++) {
		if (B.board[row+i][col]==mark) res++;
		else if (B.board[row+1][col]==-mark) return 0;
	}
	return res;
}

int diag_count1(Board &B, int mark, int row, int col) {
	/* top left bottom right diagonal */
	int res = 0;
	for (int i=0;i<min(B.row,B.col);i++) {
		if (B.board[row+i][col+i]==mark) res++;
		else if (B.board[row+i][col+i]==-mark) return 0;
	}
	return res;
}

int diag_count2(Board &B, int mark, int row, int col) {
	/* top right bottom left diagonal */
	int res = 0;
	for (int i=0;i<min(B.row,B.col);i++) {
		if (B.board[row+i][col-i]==mark) res++;
		else if (B.board[row+i][col-i]==-mark) return 0;
	}
	return res;
}

bool check_win(Board &B, bool is_first) {
		/* check whether the current board is a win */
		int mark,T = min(B.row,B.col);
		if (is_first) mark = 1;
		else mark = -1;
		for (int i=0;i<B.row;i++) {
			for (int j=0;j<B.col;j++) {
				if (j+T<=B.col && row_count(B,mark,i,j)==T) return true;
				if (i+T<=B.row && col_count(B,mark,i,j)==T) return true;
				else if (i+T<=B.row && j+T<=B.col && diag_count1(B,mark,i,j)==T) return true;
				else if (i+T<=B.row && j-(T-1)>=0 && diag_count2(B,mark,i,j)==T) return true;
			}
		}

		return false;
}

bool is_terminal(Board &B) {
	/* check whether the current board is a terminal */
	if (B.num_empty==0 || check_win(B,0) || check_win(B,1)) return true;
	return false;
}


#endif /* BOARD_CHECKER_H_ */
