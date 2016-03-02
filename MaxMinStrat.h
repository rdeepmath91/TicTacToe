/*
 * MaxMinStrat.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Raymond
 */

#ifndef MAXMINSTRAT_H_
#define MAXMINSTRAT_H_

#define INF 1000


void log_moves(int val) {
	if (val==-INF) {
		cout << "I will lose if you play correctly...\n";
		file << "I will lose if you play correctly...\n";
	}
	else if (val==INF) {
		cout << "I will win no matter what!\n";
		file << "I will win no matter what!\n";
	}
	else {
		if (val>0) cout << "I feel I have a slight advantage! ";
		else if (val==0) cout << "We're kinda in an even situation. ";
 		else cout << "I feel I am lagging behind. ";
		cout << "[Value = " << val << "]\n";
		file << "[Value = " << val << "]\n";
	}
}

int board_value(Board B, bool is_first) {
	/* value for a TERMINAL board B
	 * +INF if win, -INF if lost, 0 if draw
	 */
	int cur_player = (is_first)? 1:-1;
	return cur_player*B.who_wins*INF;
}

int MM(Board B, bool is_first, bool cur_player, int depth, string name) {
	/* Board B: the board state before cur_player moves
	 * return max of all possible if is_first = cur_player
	 * else return min
	 */

	if (B.is_terminal()) return board_value(B,is_first);

	vector<PII> v = B.valid_moves();
	int res,tmp;

	DEPTH_LIMIT = 4;

	if (depth>=DEPTH_LIMIT) { // condition to do heuristic
		tmp = -INF;
		int tmp2;
		PII p;
		for (int i=0;i<(int)v.size();i++) {
			Board B1 = B;
			B1.put(cur_player,v[i].first,v[i].second);
			tmp2 = final_heu(B1,cur_player,name);
			if (tmp<tmp2) tmp = tmp2;
		}
		return tmp;
	}

	if (is_first==cur_player) res = -INF;
	else res = INF;
	for (int i=0;i<(int)v.size();i++) {
		Board B1 = B;
		B1.put(cur_player,v[i].first,v[i].second);
		tmp = MM(B1,is_first,1-cur_player,depth+1,name);
		if (is_first==cur_player) {
			if (res<=tmp) res = tmp;
			if (res==INF) break;
		}
		else {
			if (res>=tmp) res = tmp;
			if (res==-INF) break;
		}
	}
	v.clear();
	return res;
}


PII MM(Board B, bool is_first, string name) {
	vector<PII> v = B.valid_moves();
	// guaranteed there exists at least 1 valid move from Board B
	PII res1;
	int res2 = -INF, tmp;
	for (int i=0;i<(int)v.size();i++) {
		Board B1 = B;
		B1.put(is_first,v[i].first,v[i].second);
		tmp = MM(B1,is_first,1-is_first,1,name);
		if (res2<=tmp) {
			res2 = tmp;
			res1 = v[i];
		}
		if (res2==INF) break;
	}
	// Some log after making the moves
	log_moves(res2);
	return res1;
}

#endif /* MAXMINSTRAT_H_ */
