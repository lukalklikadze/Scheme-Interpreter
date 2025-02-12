#pragma once
#include "value.h"
using namespace std;
class Parser;

class Parser{
public:
	vector<Value> Parse(vector<string> &vec);
};