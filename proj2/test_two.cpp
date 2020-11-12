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

    char *inputFile = argv[1];
    char *wordChars = argv[2];

    Dictionary dict = Dictionary::readFromFile(inputFile);

    size_t pos = 0;
    string word;
    string wordString(wordChars);
    while ((pos = wordString.find(", ")) != string::npos) {
        word = wordString.substr(0, pos);
        printf("%s %s\n", word.c_str(), dict.find(word.c_str()) ? "found" : "not found");
        wordString.erase(0, pos + 2);
    }
}