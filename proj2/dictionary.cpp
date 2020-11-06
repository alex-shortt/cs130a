#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "hash24.h"
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary(Hash24 *hashFunction, int size, vector<HashNode> primaryTable)
{
    this->hashFunction = *hashFunction;
    this->size = size;
    this->primaryTable = primaryTable;
}

Dictionary::Dictionary(string fname, int tsize)
{
    hashFunction = *(new Hash24());
    size = tsize;
    int collisions[size];

    // stats
    int num_words = 0;
    int max_collisions = 0;
    int max_collisions_index;
    vector<string> max_collisions_words;
    int primary_slots_count[21];
    int secondary_slots_count[20];
    float average_hash_attempts;

    // read file
    ifstream infile1(fname);
    ifstream infile2(fname);
    string line;

    // setup secondary slots count
    for (int i = 0; i < 20; i++)
    {
        secondary_slots_count[i] = 0;
    }

    // setup collision tracker
    for (int i = 0; i < size; i++)
    {
        collisions[i] = -1;
    }

    // set up primary table
    for (int i = 0; i < size; i++)
    {
        HashNode hNode;
        hNode.value = "";
        hNode.size = 0;
        hNode.hashFunctionsTried = 0;
        primaryTable.push_back(hNode);
    }

    // track collisions
    while (getline(infile1, line))
    {
        istringstream iss(line);
        int index = hashFunction.hash(line) % size;
        collisions[index]++;
        num_words++;
        if (collisions[index] > max_collisions)
        {
            max_collisions = collisions[index];
            max_collisions_index = index;
        }
    }

    // hash values
    while (getline(infile2, line))
    {
        istringstream iss(line);
        int index = hashFunction.hash(line) % size;
        int num_collisions = collisions[index];
        int num_elements = num_collisions + 1;
        HashNode *node = &(primaryTable[index]);

        // stats
        if (index == max_collisions_index)
        {
            max_collisions_words.push_back(line);
        }

        // begin the hashing!
        if (!num_collisions)
        {
            // individual value
            node->value = line;
        }
        else if (node->size == 0)
        {
            // hash table not created at location
            node->size = num_elements * num_elements;
            for (int i = 0; i < node->size; i++)
            {
                node->values.push_back("");
            }
            node->function = Hash24();
            node->hashFunctionsTried++;
            int newIndex = node->function.hash(line) % node->size;
            node->values[newIndex] = line;
        }
        else
        {
            // hash table already created, try to insert new value
            int newIndex = node->function.hash(line) % node->size;
            if (node->values[newIndex] == "")
            {
                node->values[newIndex] = line;
            }
            else
            {
                // oops, collision. try new hash function
                int newHashFunctionFound = 0;
                vector<string> allValues;

                // store values from second table and clear it
                for (int i = 0; i < node->size; i++)
                {
                    if (node->values[i] != "")
                    {
                        allValues.push_back(node->values[i]);
                        node->values[i] = "";
                    }
                }

                // find new hash function
                do
                {
                    node->function = Hash24();
                    node->hashFunctionsTried++;
                    int newCollisions[node->size];
                    for (int i = 0; i < allValues.size(); i++)
                    {
                        int newNewIndex = node->function.hash(allValues[i]) % node->size;
                        newCollisions[newNewIndex]++;
                        if (newCollisions[newNewIndex] > 1)
                        {
                            continue;
                        }
                    }
                    newHashFunctionFound = 1;
                } while (!newHashFunctionFound);

                // redo hashing with new hash function
                for (int i = 0; i < allValues.size(); i++)
                {
                    int newNewIndex = node->function.hash(allValues[i]) % node->size;
                    node->values[newNewIndex] = allValues[i];
                }
            }
        }
    }

    // count primary slots
    for (int i = 0; i < 21; i++)
    {
        primary_slots_count[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        if (collisions[i] < 20)
        {
            primary_slots_count[collisions[i] + 1]++;
        }
    }

    // count secondary slots and calc hash attempts
    int hash_attempts_sum = 0;
    int hash_attempts_count = 0;
    for (int i = 0; i < size; i++)
    {
        if (primaryTable[i].size > 0)
        {
            hash_attempts_sum += primaryTable[i].hashFunctionsTried;
            hash_attempts_count++;
            if (primaryTable[i].hashFunctionsTried < 21 && primaryTable[i].hashFunctionsTried > 0)
            {
                secondary_slots_count[primaryTable[i].hashFunctionsTried - 1]++;
            }
        }
    }
    average_hash_attempts = (float)hash_attempts_sum / (float)hash_attempts_count;

    // print results
    hashFunction.dump();
    printf("Number of words = %d\n", num_words);
    printf("Table size = %d\n", size);
    printf("Max collisions = %d\n", max_collisions);
    for (int i = 0; i < 21; i++)
    {
        printf("# of primary slots with %d words = %d\n", i, primary_slots_count[i]);
    }
    printf("** Words in the slot with most collisions ***\n");
    for (int i = 0; i < max_collisions_words.size(); i++)
    {
        cout << max_collisions_words[i] << endl;
    }
    for (int i = 0; i < 20; i++)
    {
        printf("# of secondary hash tables trying %d hash functions = %d\n", i + 1, secondary_slots_count[i]);
    }
    printf("Average # of hash functions tried = %f\n", average_hash_attempts);
}

bool Dictionary::find(string word)
{
    int index = hashFunction.hash(word) % size;
    HashNode *node = &(primaryTable[index]);
    if (node->value != "")
    {
        return word.compare(node->value) == 0;
    }
    if (node->size == 0)
    {
        return false;
    }

    int secondIndex = node->function.hash(word) % node->size;
    return word.compare(node->values[secondIndex]) == 0;
}

void Dictionary::writeToFile(std::string fName)
{
    ofstream file;
    file.open(fName, ios::out);

    file.write((char *)&hashFunction, sizeof(hashFunction));
    file.write((char *)&size, sizeof(size));
    for (int i = 0; i < primaryTable.size(); i++)
    {
        HashNode *node = &(primaryTable[i]);
        // file.write((char *)node, sizeof(node));
        // file.write(node->value.c_str(), sizeof(node->value));
        file.write((char *)&(node->function), sizeof((node->function)));
        file.write((char *)&(node->size), sizeof(node->size));
        file.write((char *)&(node->hashFunctionsTried), sizeof(node->hashFunctionsTried));
        // for(int y = 0; y < node->values.size(); y++){
        //     file.write(node->values[y].c_str(), sizeof(node->values[y]));
        // }
    }

    file.close();
}
