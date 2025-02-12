#include "parser.h"
#include <map>
#include "functionRegistry.h"
#include<stack>


bool isDouble(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '.')
			return 1;
	}
	return 0;
}

bool isBool(string s) {
	if (s[0] == '#' && (s[1] == 't' || s[1] == 'f')) {
		return 1;
	}
	return 0;
}

Value parse_this_List(vector<string>& vec, int l, int r, map<int,int> &locations) {
	FunctionRegistry Registry;
	vector<Value> empty_list;
	Value ans(empty_list);

	if (vec[l][0] == '\'') {
		ans.operate = 0;
	}


	for (int i = l + 1; i <= r - 1; i++) {
		if (vec[i][0] != '(' && vec[i][0] != '\'' && vec[i][0] != ')') {
			if ((vec[i][0] >= '0' && vec[i][0] <= '9') || vec[i][0] == '#') {
				if (isDouble(vec[i])) {
					double x = stod(vec[i]);
					Value val(x);
					ans.List.push_back(val);
				}
				else {
					if (isBool(vec[i])) {
						bool x;
						if (vec[i][1] == 't')
							x = 1;
						else x = 0;
						Value val(x);
						ans.List.push_back(val);
					}
					else {
						int x = stoi(vec[i]);
						Value val(x);
						ans.List.push_back(val);
					}
				}
			}
			else {
				if (vec[i][0] == '"') {
					bool bl = 0;
					Value val(vec[i], bl);

					ans.List.push_back(val);
				}
				else {
					if (Registry.hasFunction(vec[i])) {
						bool bl = 1;
						Value val(vec[i], bl);
						ans.List.push_back(val);
					}
					else {
						int type = 7;
						Value val(vec[i], type);
						ans.List.push_back(val);
					}
				}
			}
		}
		else {
			int new_l = i;
			int new_r = locations[i];
			Value val = parse_this_List(vec, new_l, new_r, locations);
			ans.List.push_back(val);
			i = new_r;
		}

	}

	return ans;
}


vector<Value> Parser::Parse(vector<string> &vec) {
	vector<Value> ans;
	map<int, int> locations;
	stack<int> st;
	for (int i = 0; i <vec.size(); i++) {
		if (vec[i][0] == '(' || vec[i][0] == '\'') {
			st.push(i);
		}
		if (vec[i][0] == ')') {
			int x = st.top();
			st.pop();
			locations[x] = i;
		}
	}
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i][0] != '(' && vec[i][0] != '\'' && vec[i][0] != ')') {
			if ((vec[i][0] >= '0' && vec[i][0] <= '9') || vec[i][0] == '#') {
				if (isDouble(vec[i])) {
					double x = stod(vec[i]);
					Value val(x);
					ans.push_back(val);
				}
				else {
					if (isBool(vec[i])) {
						bool x;
						if (vec[i][1] == 't')
							x = 1;
						else x = 0;
						Value val(x);
						ans.push_back(val);
					}
					else {
						int x = stoi(vec[i]);
						Value val(x);
						ans.push_back(val);
					}
				}
			}
			else {
				if (vec[i][0] != '"') {
					bool bl = 1;
					Value val(vec[i], bl);
					val.operate = 1;
					ans.push_back(val);
				}
				else {
					bool bl = 0;
					Value val(vec[i], bl);
					ans.push_back(val);
				}
			}
		}
		else {
			int l = i;
			int r = locations[i];
			Value val = parse_this_List(vec, l, r, locations);
			ans.push_back(val);
			i = r;
		}
	}

	return ans;
}


