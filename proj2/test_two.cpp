#include "hash24.h"
#include "dictionary.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERROR\tUsage: ./project2_first.out dataFile outFile\n");
        return 0;
    }

    char *inputFile = argv[1];
    char *wordString = argv[2];

    Dictionary dict = Dictionary::readFromFile(inputFile);

    char *token = strtok(wordString, ", ");
    while (token != NULL)
    {
        printf("%s %s\n", token, dict.find(token) ? "found" : "not found");
        token = strtok(NULL, ", ");
    }
}