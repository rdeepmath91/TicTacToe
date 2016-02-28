/*
 * MaxMinStrat.h
 *
 *  Created on: Feb 23, 2016
 *      Author: Raymond
 */

#ifndef MAXMINSTRAT_H_
#define MAXMINSTRAT_H_

#define INF 100

int board_value(Board &B, bool is_first) {
/* value for a TERMINAL board B
 * +INF if win, -INF if lost
 */
	bool b1 = check_win(B,is_first);
	if (b1) return INF;
	bool b2 = check_win(B,1-is_first);
	if (b2) return -INF;
	return 0;
}

int MM(Board &B, bool is_first, bool cur_player, int depth) {
	/* Board B: the board state before cur_player moves
	 * return max of all possible if is_first = cur_player
	 * else return min
	 */

	if (is_terminal(B)) return board_value(B,is_first);
	vector<PII> v = B.valid_moves();
	int res,tmp;

	if (depth>=4) { // heuristic
		tmp = -INF;
		int tmp2;
		PII p;
		for (int i=0;i<(int)v.size();i++) {
			Board B1(B);
			B1.put(cur_player,v[i].first,v[i].second);
			//B1.print_board(depth);
			int t1,t2;
			t1 = heu1(B1,cur_player);
			t2 = heu1(B1,1-cur_player);
			tmp2 = t1-t2;
			//for (int j=0;j<depth;j++) cout << " ";
			//cout << t1 << "-" << t2 << "=" << tmp2 << endl;
			if (tmp<tmp2) tmp = tmp2;
		}
		return tmp;
		//B.print_board(depth);
		//for (int i=0;i<depth;i++) cout << " ";
		//cout << "heu = " << tmp << " at (" << p.first+1 << "," << p.second+1 << ")" << endl;
	}

	if (is_first==cur_player) res = -INF;
	else res = INF;
	for (int i=0;i<(int)v.size();i++) {
		Board B1(B);
		B1.put(cur_player,v[i].first,v[i].second);
		tmp = MM(B1,is_first,1-cur_player,depth+1);
		if (is_first==cur_player) {
			if (res<tmp) res = tmp;
			if (res==INF) break;
		}
		else {
			if (res>tmp) res = tmp;

			if (res==-INF) break;
		}
	}
	//for (int i=0;i<depth;i++) cout << " ";
	//cout << "depth " << depth << ",value = " << res << endl;
	v.clear();
	return res;
}


PII MM(Board &B, bool is_first) {
	vector<PII> v = B.valid_moves();
	// guaranteed there exists at least 1 valid move from Board B
	PII res1;
	int res2 = -INF, tmp;\
	for (int i=0;i<(int)v.size();i++) {
		Board B1(B);
		B1.put(is_first,v[i].first,v[i].second);
		tmp = MM(B1,is_first,1-is_first,1);
		if (res2<tmp) {
			res2 = tmp;
			res1 = v[i];
		}
		if (res2==INF) break;
	}
	if (res2==-INF) cout << "I will lose if you play correctly...\n";
	else if (res2==INF) cout << "I will win no matter what!\n";
	else {
		if (res2>0) cout << "I feel I have a slight advantage! ";
		else if (res2==0) cout << "We're kinda in an even situation. ";
 		else cout << "I feel I am lagging behind. ";
		cout << "Value = " << res2 << endl;
	}
	//if (is_heur) cout << "<The saying above might not be accurate>\n";
	return res1;
}

#endif /* MAXMINSTRAT_H_ */
