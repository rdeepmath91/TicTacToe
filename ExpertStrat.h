/*
 * ExpertStrat.h
 *
 *  Created on: Feb 24, 2016
 *      Author: Raymond
 */

#ifndef EXPERTSTRAT_H_
#define EXPERTSTRAT_H_

PII win_or_block(Board B, bool is_first) {
	/* 1) return (x,y) where marking there means a win
	 * 2) else, blocking the other player from certain win
	 * 3) else, return (-1,-1)
	 */
	vector<PII> v = B.valid_moves();

	int cur_player = (is_first)? 1:-1;

	// check for win
	for (int i=0;i<(int)v.size();i++) {
		Board B1 = B;
		B1.put(is_first,v[i].first,v[i].second);
		if (B1.who_wins==cur_player) {
			cout << "Win at ";
			return v[i];
		}
	}

	// check for block
	for (int i=0;i<(int)v.size();i++) {
		Board B1 = B;
		B1.put(!is_first,v[i].first,v[i].second);
		if (B1.who_wins==-cur_player) {
			cout << "Block at ";
			return v[i];
		}
	}

	return make_pair(-1,-1);
}

PII ExpertStrat(Board B, bool is_first, string name, int depth) {
	PII p = win_or_block(B,is_first);
	if (p.first!=-1) return p;
	return MM(B,is_first,name);
}


#endif /* EXPERTSTRAT_H_ */
