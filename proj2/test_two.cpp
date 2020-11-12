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

    string wordString(wordChars);
    size_t pos = wordString.find(", ");
    string word;
    do
    {
        word = wordString.substr(0, pos);
        printf("%s %s\n", word.c_str(), dict.find(word.c_str()) ? "found" : "not found");
        wordString.erase(0, pos + 2);
    } while ((pos = wordString.find(", ")) != string::npos);

    //print last one
    printf("%s %s\n", wordString.c_str(), dict.find(wordString.c_str()) ? "found" : "not found");
}