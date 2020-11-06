#include <string>
#include <vector>
#include <fstream>
#include "hash24.h"

struct HashNode
{
    std::string value;
    Hash24 function;
    int size;
    int hashFunctionsTried;
    std::vector<std::string> values;
};

class Dictionary
{
private:
    Hash24 hashFunction;
    int size;
    std::vector<HashNode> primaryTable;

public:
    Dictionary(Hash24 *hashFunction, int size, std::vector<HashNode> primaryTable);
    Dictionary(std::string fname, int tsize);
    bool find(std::string word);
    void writeToFile(std::string fName);
    static Dictionary readFromFile(std::string fName)
    {
        Hash24 *hashFunction;
        int size;
        std::vector<HashNode> *primaryTable;

        for (int i = 0; i < size; i++)
        {
            HashNode *hNode;
            (*primaryTable).push_back(*hNode);
        }

        std::ifstream file;
        file.open(fName, std::ios::in | std::ios::binary);

        file.read((char *)&hashFunction, sizeof(hashFunction));
        file.read((char *)&size, sizeof(size));
        for (int i = 0; i < size; i++)
        {
            HashNode *node = &(*primaryTable)[i];
            file.read((char *)&(node->function), sizeof(node->function));
            file.read((char *)&(node->size), sizeof(node->size));
            file.read((char *)&(node->hashFunctionsTried), sizeof(node->hashFunctionsTried));
        }
        Dictionary *dict = new Dictionary(hashFunction, size, *primaryTable);

        return *dict;
    }
};