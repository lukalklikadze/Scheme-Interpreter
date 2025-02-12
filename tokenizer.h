#pragma once
#include<string>
#include<vector>
#include <fstream>
#include<iostream>
#include<cctype>
using namespace std;

class Tokenizer;

class Tokenizer {
public:
    string fileName;
    Tokenizer(string name);
    vector<string> Tokenize();
};