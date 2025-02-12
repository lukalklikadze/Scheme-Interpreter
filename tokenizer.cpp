#include"tokenizer.h"

Tokenizer::Tokenizer(string name) {
    fileName = name;
}

vector<string> Tokenizer::Tokenize() {
    ifstream file(fileName);
    vector<string> tokens;
    string token;

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
    }

    char ch;
    while (file.get(ch)) {
        if (isspace(ch) || ch == '\n') {
            continue;
        }

        if (ch == '\'') {
            char nextChar;
            if (file.get(nextChar)) {
                if (nextChar == '(') {
                    tokens.push_back("'(");
                }
                else {
                    file.putback(nextChar);
                    tokens.push_back("'");
                }
            }
            else {
                tokens.push_back("'");
            }
            continue;
        }


        if (ch == '(') {
            tokens.push_back("(");
            continue;
        }


        if (ch == ')') {
            tokens.push_back(")");
            continue;
        }

        if (ch == '#') {
            char nextChar;
            if (file.get(nextChar)) {
                if (nextChar == 't' || nextChar == 'f') {
                    token = "#";
                    token += nextChar;  
                    tokens.push_back(token);
                }
                else {
                    file.putback(nextChar);
                    cerr << "Invalid character after #: " << nextChar << endl;
                }
            }
            else {
                cerr << "Unexpected end of input after #" << endl;
            }
            continue;
        }

        if (ch == '>' || ch == '<' || ch == '=') {
            char nextChar;
            token = ch;
            if (file.get(nextChar)) {
                if ((ch == '>' || ch == '<') && nextChar == '=') {
                    token += nextChar; 
                }
                else {
                    file.putback(nextChar); 
                }
            }
            tokens.push_back(token);
            continue;
        }

        if (isdigit(ch) || ch == '.') {
            token = ch;
            while (file.get(ch) && (isdigit(ch) || ch == '.')) {
                token += ch;
            }
            file.putback(ch);
            tokens.push_back(token);
            continue;
        }

        if (isalpha(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '?') {
            token = ch;
            while (file.get(ch) && (isalnum(ch) || ch == '_' || ch == '-' || ch == '?')) {
                token += ch;
            }
            file.putback(ch);
            tokens.push_back(token);
            continue;
        }

        if (ch == '"') {
            token = "\"";
            while (file.get(ch) && ch != '"') {
                token += ch;
            }
            if (ch == '"') {
                token += "\"";
                tokens.push_back(token);
            }
            else {
                cerr << "String not properly closed with a quote." << endl;
            }
            continue;
        }

        cerr << "Invalid character encountered: " << ch << endl;
    }

    file.close();
    return tokens;
}