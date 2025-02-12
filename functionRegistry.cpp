#include"functionRegistry.h"
#include<cmath>
#include <algorithm>
FunctionRegistry::FunctionRegistry() {
	registerBuiltins();
}


void FunctionRegistry::registerFunction(string& name, function<Value(Value)> func) {
	func_map[name] = func;
}

function<Value(Value)> FunctionRegistry::getFunction(string& name) {
    auto it = func_map.find(name);
    if (it == func_map.end()) {
        throw runtime_error("Function not found: " + name);
    }
    return it->second;
}


bool FunctionRegistry::hasFunction(const string& name) {
    return func_map.find(name) != func_map.end();
}

Value FunctionRegistry::eval(Value arg) {
	if (arg.operate == 0) {
		return arg;
	}
	update_functions(arg);
	string func_name;
	if (arg.isList() && arg.List[0].isList() && arg.List[0].List[0].Function == "lambda") {
		func_name = "lambda";
		function<Value(Value)> func = func_map[func_name];
		return func(arg);
	}
	if (arg.isList()) {
		func_name = arg.List[0].asFunction();
		if (func_name == "eval") {
			Value tmp = arg.List[1];
			arg = tmp;
			arg.operate = 1;
		}
	}
	else
		func_name = arg.Function;
    function<Value(Value)> func = func_map[func_name];
    return func(arg);
}

Value FunctionRegistry::apply(Value arg) {
	string func_name = arg.List[1].Function;
	function<Value(Value)> func = func_map[func_name];
	Value to_perform = eval(arg.List[2]);
	
	return func(to_perform);
}

Value FunctionRegistry::add(Value arg) {
	double sum = 0;
	int ind = 0;
	for (Value i : arg.List) {
		if (i.isFunction()&&ind==0) {
			ind = 1;
			continue;
		}
		i = eval(i);
		if (i.isInteger()) {
			sum += i.asInteger();
		}
		if (i.isDouble()) {
			sum += i.asDouble();
		}
	}
	if (sum == trunc(sum)) {
		int int_sum = sum;
		return Value(int_sum);
	}
	return Value(sum);
}

Value FunctionRegistry::subtract(Value arg) {
	double ans = 0;
	bool is_first = 1;
	int ind = 0;
	for (Value i : arg.List) {
		double x;
		if (i.isFunction()&&ind==0) {
			ind = 1;
			continue;
		}
		i = eval(i);
		if (i.isInteger()) {
			x= i.asInteger();
		}
		if (i.isDouble()) {
			x = i.asDouble();
		}
		if (is_first == 1) {
			is_first = 0;
			ans = x;
		}
		else {
			ans -= x;
		}
	}
	if (ans == trunc(ans)) {
		int int_ans=ans;
		return Value(int_ans);
	}
	return Value(ans);
}

Value FunctionRegistry::multiply(Value arg) {
	double ans = 1;
	int ind = 0;
	for (Value i : arg.List) {
		if (i.isFunction()&&ind==0) {
			ind = 1;
			continue;
		}
		i = eval(i);
		if (i.isInteger()) {
			ans *= i.asInteger();
		}
		if (i.isDouble()) {
			ans *= i.asDouble();
		}
	}
	if (ans == trunc(ans)) {
		int int_ans = ans;
		return Value(int_ans);
	}
	return Value(ans);

}

Value FunctionRegistry::divide(Value arg) {
	double ans = 0;
	bool is_first = 1;
	int ind = 0;
	for (Value i : arg.List) {
		double x;
		if (i.isFunction()&&ind==0) {
			ind = 1;
			continue;
		}
		i = eval(i);
		if (i.isInteger()) {
			x = i.asInteger();
		}
		if (i.isDouble()) {
			x = i.asDouble();
		}
		if (is_first == 1) {
			is_first = 0;
			ans = x;
		}
		else {
			ans /= x;
		}
	}
	if (ans == trunc(ans)) {
		int int_ans = ans;
		return Value(int_ans);
	}
	return Value(ans);
}

Value FunctionRegistry::length(Value arg) {
	Value ans = eval(arg.List[1]);
	int sz = ans.List.size();
	return Value(sz);
}

Value FunctionRegistry::is_null(Value arg) {
	Value ans = eval(arg.List[1]);
	if (ans.isInteger()) {
		return Value(ans.Integer == 0);
	}
	else {
		return Value(ans.List.size() == 0);
	}
}

Value FunctionRegistry::car(Value arg) {
	Value ans=eval(arg.List[1]);
	return Value(ans.List[0]);
}

Value FunctionRegistry::cdr(Value arg) {
	Value ans = eval(arg.List[1]);
	vector<Value> cur = ans.List;
	cur.erase(cur.begin());
	return Value(cur);
}

Value FunctionRegistry::cons(Value arg) {
	Value ans1 = eval(arg.List[1]);
	Value ans2 = eval(arg.List[2]);
	ans2.List.insert(ans2.List.begin(), ans1);
	return ans2;
}

Value FunctionRegistry::append(Value arg) {
	Value ans1 = eval(arg.List[1]);
	Value ans2 = eval(arg.List[2]);
	ans1.List.insert(ans1.List.end(), ans2.List.begin(), ans2.List.end());
	return ans1;
}

Value FunctionRegistry::and_op(Value arg) {
	for (int i = 1; i < arg.List.size(); i++) {
		Value cur_val = eval(arg.List[i]);
		if (cur_val.Bool == 0) {
			bool ans = 0;
			return Value(ans);
		}
	}
	bool ans = 1;
	return Value(ans);
}

Value FunctionRegistry::or_op(Value arg) {
	for (int i = 1; i < arg.List.size(); i++) {
		Value cur_val = eval(arg.List[i]);
		if (cur_val.Bool == 1) {
			bool ans = 1;
			return Value(ans);
		}
	}
	bool ans = 0;
	return Value(ans);
}

Value FunctionRegistry::more(Value arg) {
	Value fir = eval(arg.List[1]);
	Value sec = eval(arg.List[2]);
	double x1=0, x2=0;
	if (fir.isString() && sec.isString()) {
		return fir.String > sec.String;
	}
	if (fir.isBool()) {
		x1 = fir.Bool;
	}
	if (fir.isInteger()) {
		x1 = fir.Integer;
	}
	if (fir.isDouble()) {
		x1 = fir.Double;
	}
	if (sec.isBool()) {
		x2 = sec.Bool;
	}
	if (sec.isInteger()) {
		x2 = sec.Integer;
	}
	if (sec.isDouble()) {
		x2 = sec.Double;
	}
	return x1 > x2;

}

Value FunctionRegistry::less(Value arg) {
	Value fir = eval(arg.List[1]);
	Value sec = eval(arg.List[2]);
	double x1 = 0, x2 = 0;
	if (fir.isString() && sec.isString()) {
		return fir.String < sec.String;
	}
	if (fir.isBool()) {
		x1 = fir.Bool;
	}
	if (fir.isInteger()) {
		x1 = fir.Integer;
	}
	if (fir.isDouble()) {
		x1 = fir.Double;
	}
	if (sec.isBool()) {
		x2 = sec.Bool;
	}
	if (sec.isInteger()) {
		x2 = sec.Integer;
	}
	if (sec.isDouble()) {
		x2 = sec.Double;
	}
	return x1 < x2;

}

Value FunctionRegistry::equal(Value arg) {
	Value fir = eval(arg.List[1]);
	Value sec = eval(arg.List[2]);
	double x1 = 0, x2 = 0;
	if (fir.isString() && sec.isString()) {
		return fir.String == sec.String;
	}
	if (fir.isBool()) {
		x1 = fir.Bool;
	}
	if (fir.isInteger()) {
		x1 = fir.Integer;
	}
	if (fir.isDouble()) {
		x1 = fir.Double;
	}
	if (sec.isBool()) {
		x2 = sec.Bool;
	}
	if (sec.isInteger()) {
		x2 = sec.Integer;
	}
	if (sec.isDouble()) {
		x2 = sec.Double;
	}
	return x1 == x2;
}

Value FunctionRegistry::less_equal(Value arg) {
	if (less(arg).Bool || equal(arg).Bool) {
		return Value(true);
	}
	return Value(false);
}

Value FunctionRegistry::more_equal(Value arg) {
	if (more(arg).Bool || equal(arg).Bool) {
		return Value(true);
	}
	return Value(false);
}

Value FunctionRegistry::if_statement(Value arg) {
	Value if_ans = eval(arg.List[1]);
	if (if_ans.Bool != 0 || if_ans.Integer != 0 || if_ans.Double != 0 || if_ans.Function != "" || if_ans.String != "" || if_ans.List.size() != 0) {
		Value ans = eval(arg.List[2]);
		return ans;
	}
	else {
		bool bl = 0;
		Value ans(bl);
		if (arg.List.size() > 3) {
			ans = eval(arg.List[3]);
		}
		return ans;
	}
}

Value FunctionRegistry::define_func(Value arg) {
	if (arg.List[1].isList() == 0) {
		string s = arg.List[1].var;
		Value ans = eval(arg.List[2]);
		func_map[s] = [ans](Value) { return ans; };
	}
	else {
		string s = arg.List[1].List[0].var;
		function<Value(Value)> func;
		Value capturedValue = arg;
		function<void(map<string, int>&, Value&, Value&)> changeVarsFunc = change_vars_in_list;
		function<Value(string&, Value)> exec = executeFunction;
		func = [capturedValue, changeVarsFunc, &func, exec](Value arg) {
			Value var_list = capturedValue.List[1];
			map<string, int> mp;
			for (int i = 1; i < var_list.List.size(); i++) {
				mp[var_list.List[i].var] = i;
			}
			Value to_execute = capturedValue.List[2];
			changeVarsFunc(mp, to_execute, arg);
			string s = "eval";
			Value ans = exec(s, to_execute);
			return ans;
			};
		func_map[s] = func;
	}
	bool bl = 0;
	string tmp = "";
	Value ret(tmp, bl);
	return ret;
}

Value FunctionRegistry::lambda_func(Value capturedValue) {
	vector<Value> empty_list;
	Value arg(empty_list);
	for (int i = 1; i < capturedValue.List.size(); i++) {
		arg.List.push_back(capturedValue.List[i]);
	}
	Value var_list = capturedValue.List[0].List[1];
	map<string, int> mp;
	for (int i = 0; i < var_list.List.size(); i++) {
		mp[var_list.List[i].var] = i;
	}
	Value to_execute = capturedValue.List[0].List[2];
	change_vars_in_list(mp, to_execute, arg);
	string s = "eval";
	Value ans = executeFunction(s, to_execute);
	return ans;
}

Value FunctionRegistry::list(Value arg) {
	vector<Value>empty_lst;
	Value ans(empty_lst);
	ans.operate = 0;
	for (int i = 1; i < arg.List.size(); i++) {
		Value to_ins = eval(arg.List[i]);
		ans.List.push_back(to_ins);
	}
	return ans;
}

Value FunctionRegistry::map_func(Value arg) {
	int lst_sz=1e9;
	for (int i = 2; i < arg.List.size(); i++) {
		if (arg.List[i].List.size() < lst_sz)
			lst_sz = arg.List[i].List.size();
	}
	vector<Value> empty_lst;
	Value ans(empty_lst);
	for (int i = 0; i < lst_sz; i++) {
		Value cur_lambda(empty_lst);
		cur_lambda.List.push_back(arg.List[1]);
		for (int j = 2; j < arg.List.size(); j++) {
			cur_lambda.List.push_back(arg.List[j].List[i]);
		}
		Value cur = eval(cur_lambda);
		ans.List.push_back(cur);
	}
	return ans;
}

void FunctionRegistry::registerBuiltins() {

    func_map["eval"] = [this](Value arg) { return this->eval(arg); };
	func_map["apply"] = [this](Value arg) { return this->apply(arg); };
	func_map["+"] = [this](Value arg) { return this->add(arg); };
	func_map["-"] = [this](Value arg) { return this->subtract(arg); };
	func_map["*"] = [this](Value arg) { return this->multiply(arg); };
	func_map["/"] = [this](Value arg) { return this->divide(arg); };
	func_map["length"] = [this](Value arg) { return this->length(arg); };
	func_map["null?"] = [this](Value arg) { return this->is_null(arg); };
	func_map["car"] = [this](Value arg) { return this->car(arg); };
	func_map["cdr"] = [this](Value arg) { return this->cdr(arg); };
	func_map["cons"] = [this](Value arg) { return this->cons(arg); };
	func_map["append"] = [this](Value arg) { return this->append(arg); };
	func_map["and"] = [this](Value arg) { return this->and_op(arg); };
	func_map["or"] = [this](Value arg) { return this->or_op(arg); };
	func_map[">"] = [this](Value arg) { return this->more(arg); };
	func_map["<"] = [this](Value arg) { return this->less(arg); };
	func_map["="] = [this](Value arg) { return this->equal(arg); };
	func_map["<="] = [this](Value arg) { return this->less_equal(arg); };
	func_map[">="] = [this](Value arg) { return this->more_equal(arg); };
	func_map["if"] = [this](Value arg) { return this->if_statement(arg); };
	func_map["define"] = [this](Value arg) { return this->define_func(arg); };
	func_map["lambda"] = [this](Value arg) { return this->lambda_func(arg); };
	func_map["list"] = [this](Value arg) { return this->list(arg); };
	func_map["map"] = [this](Value arg) { return this->map_func(arg); };
}

