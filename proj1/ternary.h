#ifndef ternary_h
#define ternary_h

#include <string>
#include <utility>

using namespace std;

struct Node {
    pair<string, int> *keyL;
    pair<string, int> *keyR;
    Node *left, *middle, *right, *parent;
    Node(string word) : keyL(new pair<string, int>(word, 1)), keyR(nullptr), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}
};

class TST {
  public:
      TST();
      ~TST();

      Node *successor(string w) const;
      int insertTST(string w);
      void print() const;
      int diff(string w);
      void searchRange(string w1, string w2) const;
      void search(string w) const;

  private:
    Node *root;
      void lookup(string w1, string w2, Node *n) const;
      Node *getNode(string w, Node *n) const;
      int insert(string w, Node *n);
      void clear(Node *n);
      void Print(Node *n) const;
      bool removeK(string w);
};

#endif
