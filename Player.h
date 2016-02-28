/*
 * Player.h
 *
 *  Created on: Feb 21, 2016
 *      Author: Raymond
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board_Checker.h"
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

	virtual Board move(Board& B) {
		cout << "astaga\n";
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
		name = "Anonymous";
	}

	virtual Board move(Board& B) {
		int x,y;
		Board B1(B);
		cout << "Your turn, please input your move.\n";
		while (true) {
			x = input_row(B1.row); x--;
			y = input_col(B1.col); y--;
			if (!B1.is_empty(x,y)) cout << "This spot has been filled. Choose another spot.\n";
			else break;
		}
		B1.put(is_first,x,y);
		B1.print_board(1);
		is_victorious = check_win(B1,is_first);
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
		strat.name = s;
	}

	virtual Board move(Board& B) {
		cout << name << "'s turn...\n";
		clock_t t = clock();
		Board B1 = strat.make_move(B,is_first);
		t = clock()-t;
		cout << "It takes " << name << " " << t/1000.0 << " seconds to make a move.\n";
		is_victorious = check_win(B1,is_first);
		if (is_victorious) cout << "Sorry, you lost.\n";
		return B1;
	}
};

#endif /* PLAYER_H_ */