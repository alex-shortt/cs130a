#include <string>
#include <vector>
#include "hash24.h"

struct HashNode {
    std::string value;
    Hash24 function;
    int size;
    int hashFunctionsTried = 0;
    std::vector<std::string> values;
};

class Dictionary
{
    private:
        Hash24 hashFunction;
        int size;
        std::vector<HashNode> primaryTable;

    public:
        Dictionary(std::string fname, int tsize);
        bool find(std::string word);
        void writeToFile(std::string fName);
        Dictionary readFromFile(std::string fName);
};