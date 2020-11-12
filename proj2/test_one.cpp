#include <sstream>
#include <fstream>
#include <string>
#include "hash24.h"
#include "dictionary.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERROR\tUsage: ./project2_first.out dataFile outFile\n");
        return 0;
    }

    char *dataFile = argv[1];
    char *outFile = argv[2];

    ifstream infile(dataFile);
    string line;
    int count = 0;

    while (getline(infile, line))
    {
        istringstream iss(line);
        count++;
    }

    Dictionary *dict = new Dictionary(dataFile, count);
    dict->writeToFile(outFile);
}