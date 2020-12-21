struct Tuple
{
    int whole;
    int fraction;
    Tuple(int whole, int fraction) : whole(whole), fraction(fraction){};
};

struct Node
{
    Tuple value;
    Node *left;
    Node *right;
    Node(Tuple value) : value(value), left(nullptr), right(nullptr){};
};

class KAVL
{
private:
    int k;
    Node *root;

public:
    KAVL(int k); // done
    bool insert(Tuple val); // done
    bool remove(Tuple val); // done
    bool search(Tuple val); // done
    Tuple* approximate_search(Tuple val); // done
    void print_in_order(); // done
    void print_pre_order(); // done
    ~KAVL(); // done
};