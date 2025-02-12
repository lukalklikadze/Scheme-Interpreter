#pragma once
#include <unordered_map>
#include <functional>
#include"value.h"
#include<map>
using namespace std;

class FunctionRegistry;

class FunctionRegistry{

public:

	FunctionRegistry();

	void registerFunction(string& name, function<Value(Value)> func);

	function<Value(Value)> getFunction(string& name);


	bool hasFunction(const string& name);

	std::function<Value(string&, Value)> executeFunction = [this](string& name, Value arg) {
		auto func = getFunction(name);
		return func(arg);
		};

	

private:
	unordered_map<string, function<Value(Value)> > func_map;
	std::function<void(std::map<std::string, int>&, Value&, Value&)>
	change_vars_in_list = [&](std::map<std::string, int>& mp, Value& to_change, Value& subs) {
		for (int i = 0; i < to_change.List.size(); i++) {
			if (to_change.List[i].isList()) {
				change_vars_in_list(mp, to_change.List[i], subs);  
			}
			if (to_change.List[i].isVar() && mp.count(to_change.List[i].var) > 0) {
				int k = mp[to_change.List[i].var];
				to_change.List[i] = subs.List[k];  
			}
		}
		};



	void update_functions(Value &arg) {
		if (arg.isVar() && hasFunction(arg.var)) {
			bool bl = 1;
			Value tmp(arg.var, bl);
			arg = tmp;
		}
		else {
			if(arg.isList()){
				for (int i = 0; i < arg.List.size(); i++) {
					update_functions(arg.List[i]);
				}
			}
		}
	}


    void registerBuiltins();
	Value eval(Value arg);
	Value apply(Value arg);
	Value add(Value arg);
	Value subtract(Value arg);
	Value multiply(Value arg);
	Value divide(Value arg);
	Value length(Value arg);
	Value is_null(Value arg);
	Value car(Value arg);
	Value cdr(Value arg);
	Value cons(Value arg);
	Value append(Value arg);
	Value and_op(Value arg);
	Value or_op(Value arg);
	Value more(Value arg);
	Value less(Value arg);
	Value equal(Value arg);
	Value less_equal(Value arg);
	Value more_equal(Value arg);
	Value if_statement(Value arg);
	Value define_func(Value arg);
	Value lambda_func(Value capturedValue);
	Value list(Value arg);
	Value map_func(Value arg);
};