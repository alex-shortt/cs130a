#include <string>
#include <vector>
#include <fstream>
#include <iostream>
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
        Hash24 hashFunction;
        int size = 0;
        std::vector<HashNode> primaryTable;

        std::ifstream file;
        file.open(fName, std::ios::in);

        file.read((char *)&hashFunction, sizeof(hashFunction));
        file.read((char *)&size, sizeof(size));

        for (int i = 0; i < size; i++)
        {
            HashNode hNode;
            primaryTable.push_back(hNode);
        }

        for (int i = 0; i < size; i++)
        {
            HashNode *node = &(primaryTable)[i];
            int node_values_size;

            size_t value_len;
            file.read((char *)&(value_len), sizeof(value_len));

            std::string value;
            value.resize(value_len);
            file.read(&value[0], value_len);
            node->value = value;

            file.read((char *)&(node->function), sizeof(node->function));
            file.read((char *)&(node->size), sizeof(node->size));
            file.read((char *)&(node->hashFunctionsTried), sizeof(node->hashFunctionsTried));
            file.read((char *)&(node_values_size), sizeof(node_values_size));

            for (int y = 0; y < node_values_size; y++)
            {
                size_t length;
                file.read((char *)&(length), sizeof(length));

                std::string secondaryValue;
                secondaryValue.resize(length);
                file.read(&secondaryValue[0], length);

                node->values.push_back(secondaryValue);
            }
        }
        Dictionary *dict = new Dictionary(&hashFunction, size, primaryTable);

        return *dict;
    }
};