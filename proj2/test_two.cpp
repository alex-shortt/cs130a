#include "hash24.h"
#include "dictionary.h"

int main(int argc, char *argv[])
{
    if (argc != 3){
        printf("ERROR\tUsage: ./project2_first.out dataFile outFile\n");
        return 0;
    }

    char* inputFile = argv[1];
    char* words = argv[2];

    printf("%s", words);
    printf("\n");

    Dictionary dict = Dictionary::readFromFile(inputFile);
    // dict.find();
}