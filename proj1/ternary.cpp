#include "ternary.h"

#include <iostream>
#include <string>
#include <utility>

using namespace std;

TST::TST() : root(nullptr) {}

TST::~TST() {
    clear(root);
}

void TST::print() const {
    Print(root);
}

void TST::Print(Node *n) const {
    if (n) {
        Print(n->left);
        cout << n->keyL->first << " ";
        Print(n->middle);
        if (n->keyR) {
            cout << n->keyR->first << " ";
        }
        Print(n->right);
    }
}

void TST::searchRange(string w1, string w2) const {
    lookup(w1, w2, root);
}

void TST::lookup(string w1, string w2, Node *n) const {
    if (n) {
        lookup(w1, w2, n->left);

        if (n->keyL && n->keyL->first.compare(w1) >= 0 && n->keyL->first.compare(w2) <= 0) {
            cout << n->keyL->first << endl;
        }
        lookup(w1, w2, n->middle);

        if (n->keyR && n->keyL->first.compare(w1) >= 0 && n->keyR->first.compare(w2) <= 0) {
            cout << n->keyR->first << endl;
        }
        lookup(w1, w2, n->right);
    }
}

void TST::clear(Node *n){
    if (n){
        clear(n->left);
        clear(n->middle);
        clear(n->right);

        delete n;
    }
}

int TST::insertTST(string w)
{
    if (!root) {
        root = new Node(w);
        cout << w << " inserted, new count = " << 1 << endl;
        return 1;
    }
    else {
        return insert(w, root);
    }
}

int TST::insert(string w, Node *n)
{
    int compareL = w.compare(n->keyL->first);
    if (compareL == 0) {
        n->keyL->second++;
        cout << w << " inserted, new count = " << n->keyL->second << endl;
        return n->keyL->second;
    }
    if (n->keyR == nullptr){
        if (w.compare(n->keyL->first) < 0) {
            n->keyR = n->keyL;
            n->keyL = new pair<string, int>(w, 1);
        } else {
            n->keyR = new pair<string, int>(w, 1);
        }
        cout << w << " inserted, new count = " << 1 << endl;
        return 1;
    }
    int compareR = w.compare(n->keyR->first);
    if (compareR == 0) {
        n->keyR->second++;
        cout << w << " inserted, new count = " << n->keyR->second << endl;
        return n->keyR->second;
    }
    if (compareL < 0) {
        if (n->left == nullptr){
            n->left = new Node(w);
            n->left->parent = n;
            cout << w << " inserted, new count = " << 1 << endl;
            return 1;
        }

        return insert(w, n->left);
    }
    if (compareR > 0){
        if (n->right == nullptr) {
            n->right = new Node(w);
            n->right->parent = n;
            cout << w << " inserted, new count = " << 1 << endl;
            return 1;
        }

        return insert(w, n->right);
    }
    if (n->middle == nullptr) {
        n->middle = new Node(w);
        n->middle->parent = n;
        cout << w << " inserted, new count = " << 1 << endl;
        return 1;
    }
    return insert(w, n->middle);
}

void TST::search(string w) const
{
    Node *node = getNode(w, root);
    if (node) {
        if (w.compare(node->keyL->first) == 0){
            cout << w << " found, count = " << node->keyL->second << endl;
        }
        else if (node->keyR && w.compare(node->keyR->first) == 0){
            cout << w << " found, count = " << node->keyR->second << endl;
        } else {
            cout << w << " not found" << endl;
        }
    } else {
        cout << w << " not found" << endl;
    }
}

Node *TST::getNode(string w, Node *n) const{
    if (n) {
        int compareL = w.compare(n->keyL->first);
        int compareR = -1;
        if (n->keyR) {
            compareR = w.compare(n->keyR->first);
        }

        if (compareL < 0) {
            return getNode(w, n->left);
        }

        if (compareR > 0) {
            return getNode(w, n->right);
        }

        if (compareL == 0 || compareR == 0) {
            return n;
        }

        return getNode(w, n->middle);
    }
    return nullptr;
}

Node *TST::successor(string w) const{
    Node *n = getNode(w, root);
    if (n) {
        if (w.compare(n->keyL->first) == 0) {
            Node *suc = n->middle;
            if (suc != nullptr) {
                while (suc->left != nullptr) {
                    suc = suc->left;
                }
            } else {
                suc = n->parent;
                if (suc != nullptr) {
                    while (suc->keyL < n->keyL) {
                        suc = suc->parent;
                        if (suc == root || suc == nullptr) {
                            return nullptr;
                        }
                    }
                }
            }
            return suc;
        }
        else if (w.compare(n->keyR->first) == 0) {
            Node *s = n->right;
            if (s != nullptr){
                while (s->left != nullptr) {
                    s = s->left;
                }
            } else {
                s = n->middle;
                if (s != nullptr)
                {
                    while (s->right != nullptr)
                    {
                        s = s->right;
                    }
                }else{
                    s = n->parent;
                    if (s != nullptr) {
                        while (s->keyL > n->keyR) {
                            s = s->parent;
                            if (s == root || s == nullptr) {
                                return nullptr;
                            }
                        }
                    }
                }
            }
            return s;
        }
    }
    return nullptr;
}

bool TST::removeK(string w) {
    Node *n = getNode(w, root);
    if (n == nullptr) {
        return false;
    }
    bool Left = w.compare(n->keyL->first) == 0;
    if (Left) {
        if (n->keyR == nullptr) {
            if (n->parent->left == n) {
                n->parent->left = nullptr;
            }
            else if (n->parent->middle == n) {
                n->parent->middle = nullptr;
            }
            else if (n->parent->right == n) {
                n->parent->right = nullptr;
            }
            return true;
        } else {
            n->keyL = n->keyR;
            n->keyR = nullptr;
        }

        Node *s = successor(n->keyL->first);
        if (s != nullptr) {
            n->keyL = s->keyL;
            return removeK(s->keyL->first);
        }
        return false;
    } else {
        Node *s = successor(n->keyR->first);
        if (s != nullptr) {
            n->keyL = s->keyL;
            return removeK(s->keyR->first);
        }
        return false;
    }
}


int TST::diff(string w) {
    Node *n = getNode(w, root);
    if (n == nullptr){
        return -1;
    }
    bool Left = w.compare(n->keyL->first) == 0;
    if (Left){
        n->keyL->second--;
        if (n->keyL->second == 0){
            Node *s = successor(n->keyL->first);
            if (s != nullptr){
                removeK(s->keyL->first);
                n->keyL = s->keyL;
            }else{
                removeK(w);
            }
            cout << w << " deleted" << endl;
            return 0;
        } else {
            cout << w << " deleted, new count = " << n->keyL->second << endl;
            return n->keyL->second;
        }
        return n->keyL->second;
    } else {
        n->keyR->second--;
        if (n->keyR->second == 0){
            Node *s = successor(n->keyR->first);
            if (s != nullptr){
                removeK(s->keyR->first);
                n->keyL = s->keyR;
            }else{
                removeK(w);
            }
            cout << w << " deleted " << endl;
            return 0;
        }else{
            cout << w << " deleted, new count = " << n->keyR->second << endl;
            return n->keyR->second;
        }
        return n->keyL->second;
    }
}
