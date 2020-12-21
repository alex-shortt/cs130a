#include <tuple>
#include <iostream>
#include <string>
#include "kavl.h"

using namespace std;

string get_tuple_string(Tuple tuple)
{
    return to_string(tuple.whole) + "." + to_string(tuple.fraction);
}

Tuple parse_tuple(string tuple_str)
{
    int len = tuple_str.length();
    int fraction = atoi(tuple_str.substr(len - 1, 1).c_str());
    tuple_str.erase(len - 2, 2);
    int whole = atoi(tuple_str.c_str());
    Tuple tuple(whole, fraction);
    return tuple;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERROR\tUsage: ./project3.out commands\n");
        return 0;
    }

    int end_found = false;
    int stop_i = 0;
    KAVL *kavl;
    int i = 0;
    string commands(argv[1]);
    size_t pos = commands.find(", ");
    while (!end_found || i <= stop_i)
    {
        string command = commands.substr(0, pos);

        if (i == 0)
        {
            int k = atoi(command.c_str());
            kavl = new KAVL(k);
        }
        else
        {
            if (command.find("approx_search") != string::npos)
            {
                command.erase(0, 14);
                Tuple tuple = parse_tuple(command);
                Tuple *closest_tuple = kavl->approximate_search(tuple);
                if (closest_tuple)
                {
                    cout << "closest to " << get_tuple_string(tuple) << " is " << get_tuple_string(*closest_tuple) << endl;
                }
            }
            else if (command.find("search") != string::npos)
            {
                command.erase(0, 6);
                Tuple tuple = parse_tuple(command);
                bool found = kavl->search(tuple);

                cout << get_tuple_string(tuple) << (found ? " found" : " not found") << endl;
            }
            else if (command.find("insert") != string::npos)
            {
                command.erase(0, 7);
                Tuple tuple = parse_tuple(command);
                bool inserted = kavl->insert(tuple);
                if (inserted)
                {
                    cout << get_tuple_string(tuple) << " inserted" << endl;
                }
            }
            else if (command.find("delete") != string::npos)
            {
                command.erase(0, 7);
                Tuple tuple = parse_tuple(command);
                int removed = kavl->remove(tuple);
                if (removed)
                {
                    cout << get_tuple_string(tuple) << " deleted" << endl;
                }
            }
            else if (command.find("in_order") != string::npos)
            {
                kavl->print_in_order();
            }
            else if (command.find("pre_order") != string::npos)
            {
                kavl->print_pre_order();
            }
        }

        if (!end_found)
        {
            commands.erase(0, pos + 2);
            pos = commands.find(", ");
        }
        if (!end_found && pos == string::npos)
        {
            stop_i = i + 1;
            end_found = true;
        }
        i++;
    }

    delete kavl;
}