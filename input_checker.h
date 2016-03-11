/*
 * input_checker.h
 *
 *  Created on: Feb 21, 2016
 *      Author: Raymond Christopher
 */

#ifndef INPUT_CHECKER_H_
#define INPUT_CHECKER_H_

bool is_num(char c) {
	return (c>='0' && c<='9');
}

bool is_num(string s) {
	int L = (int) s.length();
	if (L==0) return false;
	for (int i=0;i<L;i++) {
		if (!is_num(s[i])) return false;
	}
	return true;
}

int s_to_num(string s) {
	int res = 0;
	for (int i=0;i<(int) s.length();i++) {
		res = 10*res + (s[i]-'0');
	}
	return res;
}

pair<int,bool> input_num(string in, int low, int high) {
	/* checking whether in is a number between low and high
	 * if yes, then input
	 * */
	if (!is_num(in)) {
		cout << "Invalid Input.\n";
		return make_pair(0,false);
	}
	int tmp = s_to_num(in);
	bool b = false;
	if (tmp<low) cout << "The input should be at least " << low << ".\n";
	else if (tmp>high) cout << "The input should be at most " << high << ".\n";
	else b = true;
	return make_pair(tmp,b);
}


#endif /* INPUT_CHECKER_H_ */
