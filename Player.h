/*
 * Player.h
 *
 *  Created on: Feb 21, 2016
 *      Author: Raymond Christopher
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Strategy.h"

class Player {

public:
	string name;
	bool is_first;
	bool is_victorious;

	// each player is defaulted as 2nd player
	Player() {
		is_first = false;
		is_victorious = false;
	}

	virtual ~Player() {}

	void set_name(string s) {name = s;}
	void set_first() {is_first = true;}

	virtual Board move(Board B) {
		return B;
	}
};

class Human_Player: public Player {

	int input_row(int row) {
		/* Input the number of rows for non-default game */

		string in;
		while (true) {
			cout << "Row = ";
			cin >> in;
			pair<int,bool> tmp = input_num(in,1,row);
			if (tmp.second) return tmp.first;
		}
	}

	int input_col(int col) {
		/* Input the number of rows for non-default game */

		string in;
		while (true) {
			cout << "Column = ";
			cin >> in;
			pair<int,bool> tmp = input_num(in,1,col);
			if (tmp.second) return tmp.first;
		}
	}

public:
	Human_Player() {
		name = "Anon";
	}

	virtual Board move(Board B) {
		int x,y;
		Board B1 = B;
		cout << "Your turn, please input your move.\n";
		while (true) {
			x = input_row(B1.row); x--;
			y = input_col(B1.col); y--;
			if (!B1.is_empty(x,y))
				cout << "This spot has been filled. Choose another one.\n";
			else break;
		}
		file << "(" << x+1 << "," << y+1 << ")\n";
		B1.put(is_first,x,y);
		B1.print_board(1);
		int cur_player = (is_first)? 1:-1;
		is_victorious = (B1.who_wins == cur_player) ? 1:0;
		if (is_victorious) cout << "Congratulations, you win the game!\n";
		return B1;
	}
};

class AI_Player: public Player {

	Strategy strat;

public:
	AI_Player() {
		name = "LORD OF GAME";
	}

	void set_strat(string s){
		name = s;
		strat.name = s;
	}

	virtual Board move(Board B) {
		cout << endl << name << "'s turn...\n";
		clock_t t = clock();
		Board B1 = strat.make_move(B,is_first);
		t = clock()-t;
		cout << "It takes " << name << " " << t*1.0/CLOCKS_PER_SEC << " seconds to make a move.\n";
		int cur_player = (is_first)? 1:-1;
		is_victorious = (B1.who_wins == cur_player) ? 1:0;
		if (is_victorious) {
			cout << name << " wins the game.\n";
			file << name << " wins the game.\n";
		}
		cout << endl;
		return B1;
	}
};

#endif /* PLAYER_H_ */
