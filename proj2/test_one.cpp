#include "hash24.h"
#include "dictionary.h"

int main(int argc, char *argv[])
{
    if (argc != 3){
        printf("ERROR\tUsage: ./project2_first.out dataFile outFile\n");
        return 0;
    }

    char* dataFile = argv[1];
    char* outFile = argv[2];

    Dictionary *dict = new Dictionary(dataFile, 1000); 
    dict->writeToFile(outFile);
}