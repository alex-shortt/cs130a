#include "ternary.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    TST ternary;
    enum TST_FUNCS {
        lookup,
        insert,
        remove,
        range_search,
        none
    };

    string in = argv[1];

    vector<string> split = vector<string>();
    string space = " ";
    while (in.length() > 0){
        int index = in.find(space);
        string emp = "";
        if (index == -1){
            emp = in;
            in = "";
        }
        else{
            emp = in.substr(0, index);
            in = in.substr(index + 1);
        }
        if (emp.find(",") != -1){
            emp = emp.substr(0, emp.find(",")) + emp.substr(emp.find(",") + 1);
        }
        split.push_back(emp);

    }

    TST_FUNCS currentFunction;
    for (int i = 0; i < split.size(); i++){
        string emp = split[i];
        if (emp == "lookup"){
            currentFunction = TST_FUNCS::lookup;
        }
        else if (emp == "insert"){
            currentFunction = TST_FUNCS::insert;
        }
        else if (emp == "delete"){
            currentFunction = TST_FUNCS::remove;
        }
        else if (emp == "range_search"){
            currentFunction = TST_FUNCS::range_search;
        }else{
            if (currentFunction == TST_FUNCS::range_search){
                string word2 = split[i + 2]; //skip the 'to'
                ternary.searchRange(emp, word2);
                i += 2;
            }
            else if (currentFunction == TST_FUNCS::lookup){
                ternary.search(emp);
            }
            else if (currentFunction == TST_FUNCS::insert){
                ternary.insertTST(emp);
            }
            else if (currentFunction == TST_FUNCS::remove){
                ternary.diff(emp);
            }
            currentFunction = TST_FUNCS::none;
        }
    }

    return 0;
}
