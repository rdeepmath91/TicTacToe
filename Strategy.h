/*
 * Strategy.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Raymond Christopher
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

int DEPTH_LIMIT = 4; // the depth to use heuristic
string CUR_STRAT; // strategy of current player
double INF = 1000.0; // a value acting as 'infinite value' for maxmin

#include "Board_Checker.h"
#include "Heuristics.h"
#include "MaxMinStrat.h"
#include "ExpertStrat.h"

PII Random(Board B, bool is_first) {
	/* random strategy: put the mark in an empty square board randomly */

	int r = B.row;
	int c = B.col;
	int tmp = rand()%(B.num_empty);
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			if (B.is_empty(i,j)) {
				tmp--;
				if (tmp<0)
					return make_pair(i,j);
			}
		}
	}
	return make_pair(0,0);
}


class Strategy{
	/* Strategy is an object a board and current player
	 * having methods to determine the next move
	 */

public:
	string name;
	int depth;
	Strategy() {
		name = "Random";
		depth = 0;
	}

	PII use_strat(Board B, bool is_first) {
		CUR_STRAT = name;
		return ExpertStrat(B, is_first);
		return Random(B, is_first);
	}

	Board make_move(Board B, bool is_first) {
		Board B1 = B;
		PII opt = use_strat(B,is_first);
		cout << "(" << opt.first+1 << "," << opt.second+1 << ")" << endl;
		file << "(" << opt.first+1 << "," << opt.second+1 << ")" << endl;
		B1.put(is_first,opt.first,opt.second);
		B1.print_board(1);
		return B1;
	}
};

#endif /* STRATEGY_H_ */
