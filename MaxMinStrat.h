/*
 * MaxMinStrat.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Raymond Christopher
 */

#ifndef MAXMINSTRAT_H_
#define MAXMINSTRAT_H_


void log_moves(double val) {
	if (fabs(val+INF)<1e-8) cout << "I will lose if you play correctly...\n";
	else if (fabs(val-INF)<1e-8) cout << "I will win no matter what!\n";
	else {
		if (val>0.0) cout << "I feel I have a slight advantage! ";
		else if (val==0.0) cout << "We're kinda in an even situation. ";
 		else cout << "I feel I am lagging behind. ";
		cout << "[Value = " << val*1.0 << "]\n";
		file << "[Value = " << val*1.0 << "]\n";
	}
}

double board_value(Board B, bool is_first) {
	/* value for a TERMINAL board B
	 * +INF if win, -INF if lost, 0 if draw
	 */
	int cur_player = (is_first)? 1:-1;
	return cur_player*B.who_wins*INF;
}

double MM(Board B, bool is_first, bool cur_player, int depth, double alpha, double beta) {
	/* The MinMax strategy, optimized by Alpha-Beta pruning
	 * given a board B and the evaluating player
	 * return the value of the next board state B1 where B1 has:
	 * 	1) the maximal value if the current player = evaluating player
	 * 	2) the minimal value, otherwise
	 * among all possible choices.
	 */

	if (B.is_terminal()) return board_value(B,is_first);

	vector<PII> v = B.valid_moves();
	double res,tmp;

	if (depth>=DEPTH_LIMIT) { // condition to do heuristic
		tmp = -INF;
		int max_ind;
		Board B1;
		for (int i=0;i<(int)v.size();i++) {
			B1 = B;
			B1.put(cur_player,v[i].first,v[i].second);
			tmp = final_heu(B1,cur_player,CUR_STRAT);
			if (i==0 || res<tmp) {
				res = tmp;
				max_ind = i;
			}
		}
		B1 = B;
		B1.put(cur_player,v[max_ind].first,v[max_ind].second);
		return final_heu(B1,is_first,CUR_STRAT);
	}

	if (is_first==cur_player) res = -INF;
	else res = INF;
	for (int i=0;i<(int)v.size();i++) {
		Board B1 = B;
		B1.put(cur_player,v[i].first,v[i].second);
		tmp = MM(B1,is_first,!cur_player,depth+1,alpha,beta);
		if (is_first==cur_player) {
			if (i==0 || res<tmp) res = tmp;
			alpha = max(alpha,res);
			if (res==INF) break;
		}
		else {
			if (i==0 || res>tmp) res = tmp;
			beta = min(beta,tmp);
			if (res==-INF) break;
		}
		if (beta<=alpha) break;
	}
	v.clear();
	return res;
}


PII MM(Board B, bool is_first) {
	vector<PII> v = B.valid_moves();
	PII res1;
	double res2 = -INF, tmp;
	double alpha = -INF,beta = INF;
	Board Bmove;

	// guaranteed Board B is not a terminal state
	for (int i=0;i<(int)v.size();i++) {
		Board B1 = B;
		B1.put(is_first,v[i].first,v[i].second);
		tmp = MM(B1,is_first,!is_first,1,alpha,beta);
		if (i==0 || res2<tmp) {
			res2 = tmp;
			res1 = v[i];
			//Bmove = B1; // uncomment to check heuristic value of this move
		}
		alpha = max(alpha,res2);
		if (res2==INF) break;
		if (beta<=alpha) break;
	}
	// Some log after making the moves
	log_moves(res2);
	//cout << "Heuristics : " << final_heu(Bmove,is_first,"Expert2") << endl;
	return res1;
}

#endif /* MAXMINSTRAT_H_ */
