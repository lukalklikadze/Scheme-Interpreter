#include "value.h"
#include <iostream>
#include <map>
#include "functionRegistry.h"


Value::Value(int i) {
    type = 1;
    Integer = i;
    Double = 0.0;
    Function = "";
    operate = 0;
    Bool = 0;
    String = "";
    var = "";
    List.clear();
}

Value::Value(double d) {
    type = 2;
    Integer = 0;
    Double = d;
    Function = "";
    operate = 0;
    Bool = 0;
    String = "";
    var = "";
    List.clear();
}

Value::Value(string& name, bool isFunc) {
    Integer = 0;
    Double = 0.0;
    operate = 0;
    Bool = 0;
    List.clear();
    var = "";
    if (isFunc == 1) {
        type = 3;
        Function = name;
        String = "";
        operate = 1;
    }
    else {
        type = 6;
        Function = "";
        String = name;
    }
}

Value::Value(vector<Value>& list) {
    type = 4;
    Integer = 0;
    Double = 0.0;
    Function = "";
    operate = 1;
    Bool = 0;
    String = "";
    List = list;
    var = "";
}

Value::Value(bool i) {
    type = 5;
    Integer = 0;
    Double = 0.0;
    Function = "";
    operate = 0;
    Bool = i;
    String = "";
    List.clear();
    var = "";
}

Value::Value(string& curvar, int varType) {
    type = varType;
    Integer = 0;
    Double = 0.0;
    Function = "";
    operate = 0;
    Bool = 0;
    String = "";
    List.clear();
    var = curvar;
}




bool Value::isInteger() {
    return type == 1;
}
bool Value::isDouble() {
    return type == 2;
}
bool Value::isFunction() {
    return type == 3;
}
bool Value::isList() {
    return type == 4;
}

bool Value::isBool() {
    return type == 5;
}

bool Value::isString() {
    return type == 6;
}

bool Value::isVar() {
    return type == 7;
}




int Value::asInteger() {
    if (!isInteger()) {
        throw runtime_error("This value is not an integer.");
    }
    return Integer;
}
double Value::asDouble() {
    if (!isDouble()) {
        throw runtime_error("This value is not a double.");
    }
    return Double;
}
string& Value::asFunction() {
    if (!isFunction()) {
        throw runtime_error("This value is not a function.");
    }
    return Function;
}
vector<Value>& Value::asList() {
    if (!isList()) {
        throw runtime_error("This value is not a list.");
    }
    return List;
}

bool Value::asBool() {
    if (!isBool()) {
        throw runtime_error("This value is not a bool.");
    }
    return Bool;
}

string Value::asString() {
    if (!isString()) {
        throw runtime_error("This value is not a string.");
    }
    if (String.size() == 0) {
        return String;
    }
    else
       return String.substr(1,String.size()-2);
}

void Value::print_list() {
    cout << "( ";
    for (int i = 0; i < List.size(); i++) {
        if (List[i].isString()) {
            cout << List[i].String << ' ';
        }
        if (List[i].isInteger()) {
            cout << List[i].Integer<<' ';
        }
        if (List[i].isDouble()) {
            cout << List[i].Double << ' ';
        }
        if (List[i].isFunction()) {
            cout << List[i].Function << ' ';
        }
        if (List[i].isList()) {
            List[i].print_list();
        }
    }
    cout << ") ";
   
}

void Value::display_value() {
    if (isInteger()) {
        cout << asInteger()<<endl;
    }
    if (isDouble()) {
        cout << asDouble() << endl;
    }
    if (isFunction()) {
        if(asFunction()!="")
          cout << asFunction() << endl;
    }
    if (isString()) {
        if (asString() != "")
          cout << asString() << endl;
    }
    if (isList()) {
        print_list();
        cout << endl;
    }
    if (isBool()) {
        if (Bool == 0)
            cout << "#f";
        else
            cout << "#t";
        cout << endl;
    }
}

