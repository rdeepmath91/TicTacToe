/*
 * Heuristics.h
 *
 *  Created on: Feb 24, 2016
 *      Author: Raymond Christopher
 */

#ifndef HEURISTICS_H_
#define HEURISTICS_H_


int heu1(Board &B, bool is_first) {
	/* counting all possible-winning lines */

	int sum = 0;
	int cur_player = (is_first) ? 1:-1;
	pair<int,bool> tmp;
	// row
	for (int i=0;i<(int) B.BC.row_L.size();i++) {
		tmp = B.BC.row_L[i];
		if (tmp.second && cur_player * tmp.first>0) sum++;
	}
	// column
	for (int i=0;i<(int) B.BC.col_L.size();i++) {
		tmp = B.BC.col_L[i];
		if (tmp.second && cur_player * tmp.first>0) sum++;
	}
	// diag1
	for (int i=0;i<(int) B.BC.diag1_L.size();i++) {
		tmp = B.BC.diag1_L[i];
		if (tmp.second && cur_player * tmp.first>0) sum++;
	}
	// diag2
	for (int i=0;i<(int) B.BC.diag2_L.size();i++) {
		tmp = B.BC.diag2_L[i];
		if (tmp.second && cur_player * tmp.first>0) sum++;
	}
	return sum;
}

int heu2(Board &B, bool is_first) {
	/* counting all elements in possible-winning lines */

	int sum = 0;
	int cur_player = (is_first) ? 1:-1;
	pair<int,bool> tmp;
	// row
	for (int i=0;i<(int) B.BC.row_L.size();i++) {
		tmp = B.BC.row_L[i];
		if (tmp.second && cur_player * tmp.first>0) sum += tmp.first;
	}
	// column
	for (int i=0;i<(int) B.BC.col_L.size();i++) {
		tmp = B.BC.col_L[i];
		if (tmp.second && cur_player * tmp.first>0) sum+= tmp.first;
	}
	// diag1
	for (int i=0;i<(int) B.BC.diag1_L.size();i++) {
		tmp = B.BC.diag1_L[i];
		if (tmp.second && cur_player * tmp.first>0) sum+= tmp.first;
	}
	// diag2
	for (int i=0;i<(int) B.BC.diag2_L.size();i++) {
		tmp = B.BC.diag2_L[i];
		if (tmp.second && cur_player * tmp.first>0) sum+= tmp.first;
	}
	return sum;
}

double final_heu(Board &B, bool is_first, string name) {
	/* heuristic value of a board state B after player is_fist making his move
	 * name: name for strategy which is used to calculate the value
	 */

	int cur_player = is_first ? 1:-1;
	if (B.who_wins*cur_player==1) return INF;
	else if (B.who_wins*cur_player==-1) return -INF;
	if (name=="Expert2")
		return 1.0*(heu2(B,is_first)-heu1(B,!(is_first)));
	else if (name=="Expert1")
		return 1.0*(heu1(B,is_first)-heu1(B,!(is_first)));
	return 0;
}

#endif /* HEURISTICS_H_ */
