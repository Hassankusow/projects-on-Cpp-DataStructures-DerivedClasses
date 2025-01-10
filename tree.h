#ifndef PokemonTree_H
#define PokemonTree_H

#include <iostream>
#include "poke.h" 

class two3node {
public:
    Pokemon* k1;             // First key
    Pokemon* k2;             // Second key (only valid for 3-nodes)
    int n;                   // Number of keys (1 for 2-node, 2 for 3-node)
    two3node* left;          // Left child
    two3node* middle;        // Middle child
    two3node* right;         // Right child

    // Constructor
    two3node() : k1(nullptr), k2(nullptr), n(0), left(nullptr), middle(nullptr), right(nullptr) {}
};

class usefulData {
public:
    two3node* child;         // New child created during split
    Pokemon* midValue;       // Middle value to propagate upward

    usefulData(two3node* c = nullptr, Pokemon* m = nullptr) : child(c), midValue(m) {}
};

class PokemonTree {
private:
    two3node* root;          // Root of the tree

    // Recursive helper for insertion
    usefulData insertHelper(two3node*& r, Pokemon* d, two3node* parent);

    // Splitting a 3-node
    usefulData split3node(two3node* current, Pokemon* k, two3node* child);

    // Rotation methods
    usefulData rotateLeft(two3node* parent, two3node* current, Pokemon* k, two3node* child);
    usefulData rotateRight(two3node* parent, two3node* current, Pokemon* k, two3node* child);

    // Determine if rotation is possible
    int isRotationPossible(two3node* parent, two3node* current);

    // Recursive tree traversal helpers
    void printTree(two3node* root);
    void destroyTree(two3node* root);

public:
    // Constructor
    PokemonTree() : root(nullptr) {}

    // Destructor
    ~PokemonTree();

    // Public insertion method
    bool insert(Pokemon* d);

    // Traversal methods
    void print();
};

#endif // PokemonTree_H

