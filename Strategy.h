/*
 * Strategy.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Raymond
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "Heuristics.h"
#include "MaxMinStrat.h"
#include "ExpertStrat.h"

PII Random(Board& B, bool is_first) {
	/* default strategy: put in to the board randomly */

	int r = B.row;
	int c = B.col;
	int tmp = rand()%(B.num_empty);
	//cout << "tmp = " << tmp << endl;
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			if (B.is_empty(i,j)) {
				tmp--;
				if (tmp<0) {
					return make_pair(i,j);
				}
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
	Strategy() {
		name = "Random";
	}

	PII use_strat(Board &B, bool is_first) {
		if (name=="Expert") return ExpertStrat(B, is_first);
		else if (name=="Medium") return MM(B,is_first);
		return Random(B, is_first);
	}

	Board make_move(Board &B, bool is_first) {
		vector<PII> v = B.valid_moves();
		Board B1(B);
		PII opt = use_strat(B, is_first);
		cout << "(" << opt.first+1 << "," << opt.second+1 << ")" << endl;
		B1.put(is_first,opt.first,opt.second);
		v.clear();
		B1.print_board(1);
		return B1;
	}
};

#endif /* STRATEGY_H_ */
