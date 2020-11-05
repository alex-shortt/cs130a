#include "hash24.h"
#include "dictionary.h"


int main(int argc, char *argv[])
{
    Dictionary *dict = new Dictionary("PA2_dataset.txt", 1000); 
    printf("Found aaaugh: %d\n", dict->find("aaaugh"));
    printf("Found abominating: %d\n", dict->find("abominating"));
    printf("Found yade: %d\n", dict->find("yade"));
    printf("Found yadena: %d\n", dict->find("yadena"));
}