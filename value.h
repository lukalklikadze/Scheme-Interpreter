#pragma once
#include<string>
#include<vector>
#include <stdexcept>
#include <functional>

using namespace std;

class Value;


class Value {
public:
    int type; 
    int Integer;
    double Double;
    string Function;
    vector<Value> List;
    bool operate;
    bool Bool;
    string String;
    string var;
    function<Value(Value)> Lambda;

    Value(int i);
    Value(double d);
    Value(string& name, bool isFunc);
    Value(vector<Value>& list);
    Value(bool i);
    Value(string& curvar, int varType);


    bool isInteger();
    bool isDouble();
    bool isFunction();
    bool isList();
    bool isBool();
    bool isString();
    bool isVar();
    
    void display_value();
    void print_list();

    int asInteger();
    double asDouble();
    string& asFunction();
    vector<Value>& asList();
    bool asBool();
    string asString();
};