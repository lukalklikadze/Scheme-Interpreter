#include "includes.h"
using namespace std;

int main() {
    string tst = "test";
    for (int i = 1; i <= 10; i++) {
        cout << "test " << i << " begin:" << endl;
        string cur_tst = tst + to_string(i) + ".txt";
        Tokenizer Tokenizer(cur_tst);
        Parser Parser;
        vector<string> tokens = Tokenizer.Tokenize();

        vector<Value>code_to_evaluate = Parser.Parse(tokens);
        FunctionRegistry Registry;
        string x = "eval";
        for (int i = 0; i < code_to_evaluate.size(); i++) {
            Value ans = Registry.executeFunction(x, code_to_evaluate[i]);
            ans.display_value();
        }
        cout << "test completed successfully" << endl;
        cout << endl;
    }
    return 0;
}