#include <string>
#include <iostream>
#include <cmath>
#include "kavl.h"

using namespace std;

KAVL::KAVL(int k)
{
    this->k = k;
    this->root = nullptr;
}

string tuple_string(Tuple tuple)
{
    return to_string(tuple.whole) + "." + to_string(tuple.fraction);
}

int compare_tuples(Tuple val1, Tuple val2)
{
    int first = val1.whole * 10 + val1.fraction;
    int second = val2.whole * 10 + val2.fraction;

    return first - second;
}

int calc_height(Node *node)
{
    if (!node)
    {
        return -1;
    }
    return 1 + max(calc_height(node->right), calc_height(node->left));
}

int calc_balance(Node *node)
{
    return calc_height(node->left) - calc_height(node->right);
}

int calc_num_nodes(Node *node)
{
    if (!node)
    {
        return 0;
    }
    return 1 + calc_num_nodes(node->right) + calc_num_nodes(node->left);
}

void recursive_print_balance(int k, Node *node)
{
    if (!node)
        return;
    int balance = calc_balance(node);
    cout << "balance on " << tuple_string(node->value) << ": " << balance << endl;
    recursive_print_balance(k, node->left);
    recursive_print_balance(k, node->right);
}

void print_tree(Node *node, string s)
{
    if (!node)
    {
        return;
    }

    cout << tuple_string(node->value) << s << ", ";
    print_tree(node->left, s + "L");
    print_tree(node->right, s + "R");
}

Node *left_rotate(Node *x)
{
    Node *y = x->right;
    Node *z = y->left;
    y->left = x;
    x->right = z;

    return y;
}

Node *right_rotate(Node *y)
{
    Node *x = y->left;
    Node *z = x->right;
    x->right = y;
    y->left = z;

    return x;
}

Node *recursive_insert(int k, Node *parent, Node *node)
{
    if (!parent)
    {
        return node;
    }

    // regular insert
    int comparison = compare_tuples(node->value, parent->value);
    if (comparison < 0)
    {
        parent->left = recursive_insert(k, parent->left, node);
    }
    else if (comparison > 0)
    {
        parent->right = recursive_insert(k, parent->right, node);
    }
    else
    {
        return parent;
    }

    // avl check
    int balance = calc_balance(parent);
    if (balance > k)
    {
        int left_comparison = compare_tuples(node->value, parent->left->value);
        if (left_comparison < 0)
        {
            return right_rotate(parent);
        }
        if (left_comparison > 0)
        {
            parent->left = left_rotate(parent->left);
            return right_rotate(parent);
        }
    }
    if (balance < -k)
    {
        int right_comparison = compare_tuples(node->value, parent->right->value);
        if (right_comparison > 0)
        {
            return left_rotate(parent);
        }
        if (right_comparison < 0)
        {
            parent->right = right_rotate(parent->right);
            return left_rotate(parent);
        }
    }

    return parent;
}

bool KAVL::insert(Tuple val)
{
    Node *node = new Node(val);
    int num_before = calc_num_nodes(root);
    root = recursive_insert(k, root, node);
    int num_after = calc_num_nodes(root);
    return (num_before != num_after);
}

Node *get_successor(Node *node)
{
    Node *current = node->right;

    while (current->left)
    {
        current = current->left;
    }

    return current;
}

Node *get_predeccessor(Node *node)
{
    Node *current = node->left;

    while (current->right)
    {
        current = current->right;
    }

    return current;
}

Node *recursive_remove(int k, Node *node, Tuple val)
{
    if (!node)
    {
        return node;
    }

    int comparison = compare_tuples(val, node->value);
    if (comparison < 0)
    {
        node->left = recursive_remove(k, node->left, val);
    }
    else if (comparison > 0)
    {
        node->right = recursive_remove(k, node->right, val);
    }
    else
    {
        if (!node->left && !node->right)
        {
            Node *temp = node;
            node = nullptr;
            delete temp;
        }
        else if (!node->right || !node->left)
        {
            Node *temp = node->left ? node->left : node->right;
            *node = *temp;
            delete temp;
        }
        else
        {
            Node *pred = get_predeccessor(node);
            node->value = pred->value;
            node->left = recursive_remove(k, node->left, pred->value);
        }
    }

    if (!node)
    {
        return node;
    }

    // avl check
    int balance = calc_balance(node);
    if (balance > k)
    {
        int left_balance = calc_balance(node->left);
        if (left_balance >= 0)
        {
            return right_rotate(node);
        }
        if (left_balance < 0)
        {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    }
    else if (balance < -k)
    {
        int right_balance = calc_balance(node->right);
        if (right_balance <= 0)
        {
            return left_rotate(node);
        }
        if (right_balance > 0)
        {

            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
    }

    return node;
}

bool KAVL::remove(Tuple val)
{
    if (!root)
    {
        return false;
    }

    int num_before = calc_num_nodes(root);
    root = recursive_remove(k, root, val);
    int num_after = calc_num_nodes(root);
    return ((num_after + 1) == num_before);
}

bool recursive_search(Node *node, Tuple val)
{
    if (!node)
    {
        return false;
    }

    int comparison = compare_tuples(val, node->value);
    if (comparison < 0)
    {
        return recursive_search(node->left, val);
    }
    else if (comparison > 0)
    {
        return recursive_search(node->right, val);
    }

    return true;
}

bool KAVL::search(Tuple val)
{
    return recursive_search(root, val);
}

Tuple *recursive_approximate_search(Node *node, Tuple val)
{
    int smallest_dist = abs(compare_tuples(val, node->value));
    Tuple *smallest_tuple = &(node->value);

    if (node->right)
    {
        Tuple *right = recursive_approximate_search(node->right, val);
        int right_comparison = compare_tuples(*right, val);
        int right_dist = right_comparison < 0 ? -1 * right_comparison : right_comparison;
        if (right_dist < smallest_dist || (right_dist <= smallest_dist && right_comparison < 0))
        {
            smallest_dist = right_dist;
            smallest_tuple = right;
        }
    }
    if (node->left)
    {
        Tuple *left = recursive_approximate_search(node->left, val);
        int left_comparison = compare_tuples(*left, val);;
        int left_dist = abs(left_comparison);
        if (left_dist < smallest_dist || (left_dist <= smallest_dist && left_comparison < 0))
        {
            smallest_dist = left_dist;
            smallest_tuple = left;
        }
    }

    return smallest_tuple;
}

Tuple *KAVL::approximate_search(Tuple val)
{
    if (!root)
    {
        return nullptr;
    }

    return recursive_approximate_search(root, val);
}

string recursive_print_in_order(Node *node)
{
    if (!node)
    {
        return "";
    }

    string out = "";
    out += recursive_print_in_order(node->left);
    out += tuple_string(node->value) + " ";
    out += recursive_print_in_order(node->right);
    return out;
}

void KAVL::print_in_order()
{
    if (!root)
    {
        return;
    }
    string out = recursive_print_in_order(root);
    out.erase(out.length() - 1, 1);
    cout << out << endl;
}

string recursive_print_pre_order(Node *node)
{
    if (!node)
    {
        return "";
    }

    string out = "";
    out += tuple_string(node->value) + " ";
    out += recursive_print_pre_order(node->left);
    out += recursive_print_pre_order(node->right);
    return out;
}

void KAVL::print_pre_order()
{
    if (!root)
    {
        return;
    }
    string out = recursive_print_pre_order(root);
    out.erase(out.length() - 1, 1);
    cout << out << endl;
}

void recursive_delete(Node *root, Node *node)
{
    if (node)
    {
        recursive_delete(root, node->left);
        recursive_delete(root, node->right);

        delete node;
    }
}

KAVL::~KAVL()
{
    recursive_delete(root, root);
}