// this is my 2-3 tree cpp implemetation.

#include "tree.h"

// this is my recurisive print function inorder
void PokemonTree::print(){
        printTree(root);
}
void PokemonTree::printTree(two3node* current) {
    if (current) {
        if (current->n == 1) {
            printTree(current->left);
            current->k1->displayStats();
            printTree(current->middle);
        } else {
            printTree(current->left);
            current->k1->displayStats();
            printTree(current->middle);
            current->k1->displayStats();
            printTree(current->right);
        }
    }
}

// this is a helper function to compare to balance my tree
bool comparePokemon(Pokemon* a, Pokemon* b) {
    
    return a->getAttackPower() < b->getAttackPower(); 
}
// my destructor
PokemonTree::~PokemonTree(){
        destroyTree(root);
}

void PokemonTree::destroyTree(two3node* node) {
    if (!node) return; // Base case: null node
    destroyTree(node->left);
    destroyTree(node->middle);
    destroyTree(node->right);
    delete node; // Delete the current node
}

// this is my insert function ill explain this in detail becouse it took alot of logic to get it to work
bool PokemonTree::insert(Pokemon* d) {
    if (!root) {
        // Case 1: Empty Tree
        root = new two3node;
        root->k1 = d;
        root->n = 1;
        return true;
    }

    usefulData result = insertHelper(root, d, nullptr);

    // If root splitting occurs
    if (result.child != nullptr) {
        two3node* newRoot = new two3node;
        newRoot->k1 = result.midValue;
        newRoot->n = 1;
        newRoot->left = root;
        newRoot->middle = result.child;
        newRoot->right = nullptr;
        root = newRoot;
    }

    return true;
}
// i used this way due to getting alot of overflows and werent inserting correctly 
usefulData PokemonTree::insertHelper(two3node*& r, Pokemon* d, two3node* parent) {
    // Case 2: Leaf Node
    if (!r->left) {
        if (r->n == 1) {
            // Simple insertion into 2-node
            if (*d < *(r->k1)) {
                r->k2 = r->k1;
                r->k1 = d;
            } else {
                r->k2 = d;
            }
            r->n = 2;
            return usefulData(nullptr, nullptr);
        } else {
            // Overflow in 3-node
            int rotationCase = isRotationPossible(parent, r);
            if (rotationCase == 1)
                return rotateRight(parent, r, d, nullptr);
            else if (rotationCase == 2)
                return rotateLeft(parent, r, d, nullptr);
            else
                return split3node(r, d, nullptr);
        }
    }

    // Case 3: Non-Leaf Node
    usefulData result;
    if (r->n == 1) {
        // Current node is a 2-node
        if (*d < *(r->k1))
            result = insertHelper(r->left, d, r);
        else
            result = insertHelper(r->middle, d, r);

        // Handle result from child split
        if (result.child != nullptr) {
            r->k2 = r->k1;
            r->k1 = result.midValue;
            r->right = r->middle;
            r->middle = result.child;
            r->n = 2;
        }
    } else {
        // Current node is a 3-node
        if (*d < *(r->k1))
            result = insertHelper(r->left, d, r);
        else if (*d < *(r->k2))
            result = insertHelper(r->middle, d, r);
        else
            result = insertHelper(r->right, d, r);

        // Handle result from child split
        if (result.child != nullptr) {
            int rotationCase = isRotationPossible(parent, r);
            if (rotationCase == 1)
                return rotateRight(parent, r, result.midValue, result.child);
            else if (rotationCase == 2)
                return rotateLeft(parent, r, result.midValue, result.child);
            else
                return split3node(r, result.midValue, result.child);
        }
    }

    return usefulData(nullptr, nullptr);
}
// this is where i check if its poosible to rotate
int PokemonTree::isRotationPossible(two3node* parent, two3node* current) {
    if (parent != current) {
        // Check if the parent is a 2-node
        if (parent->n == 1) {
            if (current->n == 0) { // Underflow case
                // Deficiency occurred at left child
                if ((parent->left == current) && (parent->middle->n == 2)) 
                    return 2; // Anti-clockwise (left) rotation
                
                // Deficiency occurred at middle child
                else if ((parent->middle == current) && (parent->left->n == 2)) 
                    return 1; // Clockwise (right) rotation
            } 
            // Overflow case
            else {
                if (!((parent->left->n == 2) && (parent->middle->n == 2))) {
                    if (parent->left == current) 
                        return 1; // Clockwise (right) rotation
                    
                    else 
                        return 2; // Anti-clockwise (left) rotation
                }
            }
        }
        // Check if the parent is a 3-node
        else {
            if (current->n == 0) { // Underflow case
                // Deficiency occurred at left child
                if ((parent->left == current) && (parent->middle->n == 2)) 
                    return 2; // Anti-clockwise (left) rotation
                
                // Deficiency occurred at middle child
                else if (parent->middle == current) {
                    if (parent->left->n == 2) 
                        return 1; // Clockwise (right) rotation
                    else if (parent->right->n == 2) 
                        return 2; // Anti-clockwise (left) rotation
                }
                // Deficiency occurred at right child
                else if (parent->right == current) {
                    if (parent->middle->n == 2) 
                        return 1; // Clockwise (right) rotation
                }
            } 
            // Overflow case
            else {
                if ((parent->left == current) && (parent->middle->n == 1)) 
                    return 1; // Clockwise (right) rotation
                
                else if (parent->middle == current) {
                    if (parent->left->n == 1) 
                        return 2; // Anti-clockwise (left) rotation
                    else if (parent->right->n == 1) 
                        return 1; // Clockwise (right) rotation
                } 
                else if (parent->right == current) {
                    if (parent->middle->n == 1) 
                        return 2; // Anti-clockwise (left) rotation
                }
            }
        }
    }
    return 0; // No rotation needed
}

              


usefulData PokemonTree::rotateRight(two3node* parent, two3node* current, Pokemon* k, two3node* child) {
    if (!parent || !current) {
        throw std::invalid_argument("Null node passed to rotateRight.");
    }

    // CASE 1: Underflow at current
    if (current->n == 0) {
        if (parent->n == 2 && parent->right == current) { 
            current->k1 = parent->k2; // Separator Key
            current->n = 1;

            parent->k2 = parent->middle->k2; // Promote middle key
            parent->middle->n = 1;

            // Update pointers
            current->left = parent->middle->right;
        } else { // Underflow at middle or left child
            current->k1 = parent->k1; // Separator Key
            current->n = 1;

            parent->k1 = parent->left->k2; // Promote left key
            parent->left->n = 1;

            // Update pointers
            current->left = parent->left->right;
        }
    }

    // CASE 2: Overflow at current
    else {
        if (parent->n == 2 && parent->middle == current) { 
            parent->right->k2 = parent->right->k1; // Right node becomes a 3-node
            parent->right->k1 = parent->k2;        // Separator Key

            if (comparePokemon(k, current->k1)) { // Assume `Pokemon` has a `compare` method
                parent->k2 = current->k2;
                current->k2 = current->k1;
                current->k1 = k;
            } else if (comparePokemon(k, current->k2)) {
                parent->k2 = current->k2;
                current->k2 = k;
            } else {
                parent->k2 = k;
            }

            // Update pointers
            parent->right->right = parent->right->middle;
            parent->right->middle = parent->right->left;
            parent->right->left = child;

            parent->right->n = 2;
        } else { // Overflow at left child
            parent->middle->k2 = parent->middle->k1; // Middle becomes a 3-node
            parent->middle->k1 = parent->k1;         // Separator Key

            if (comparePokemon(k, current->k1)) {
                parent->k1 = current->k2;
                current->k2 = current->k1;
                current->k1 = k;
            } else if (comparePokemon(k, current->k2)) {
                parent->k1 = current->k2;
                current->k2 = k;
            } else {
                parent->k1 = k;
            }

            // Update pointers
            parent->middle->right = parent->middle->middle;
            parent->middle->middle = parent->middle->left;
            parent->middle->left = child;

            parent->middle->n = 2;
        }
    }

    return usefulData(); // Return appropriate usefulData
}


usefulData PokemonTree::rotateLeft(two3node* parent, two3node* current, Pokemon* k, two3node* child) {
    if (!parent || !current) {
        throw std::invalid_argument("Null node passed to rotateLeft.");
    }

    // CASE 1: Underflow at current
    if (current->n == 0) {
        if (parent->n == 2 && parent->middle == current) { 
            current->k1 = parent->k2; // Separator Key
            current->n = 1;

            parent->k2 = parent->right->k1; // Promote right key
            parent->right->k1 = parent->right->k2;
            parent->right->n = 1;

            // Update pointers
            current->middle = parent->right->left;
            parent->right->left = parent->right->middle;
            parent->right->middle = parent->right->right;
        } else { // Underflow at left child
            current->k1 = parent->k1; // Separator Key
            current->n = 1;

            parent->k1 = parent->middle->k1; // Promote middle key
            parent->middle->k1 = parent->middle->k2;
            parent->middle->n = 1;

            // Update pointers
            current->middle = parent->middle->left;
            parent->middle->left = parent->middle->middle;
            parent->middle->middle = parent->middle->right;
        }
    }

    // CASE 2: Overflow at current
    else {
        if (parent->n == 2 && parent->right == current) { 
            parent->middle->k2 = parent->k2; // Separator Key

            if (comparePokemon(k, current->k1)) {
                parent->k2 = k;
            } else if (comparePokemon(k, current->k2)) {
                parent->k2 = current->k1;
                current->k1 = k;
            } else {
                parent->k2 = current->k1;
                current->k1 = current->k2;
                current->k2 = k;
            }

            // Update pointers
            parent->middle->right = parent->right->left;
            parent->right->left = parent->right->middle;
            parent->right->middle = parent->right->right;
            parent->right->right = child;

            parent->middle->n = 2;
        } else { // Overflow at middle child
            parent->left->k2 = parent->k1; // Separator Key

            if (comparePokemon(k, current->k1)) {
                parent->k1 = k;
            } else if (comparePokemon(k, current->k2)) {
                parent->k1 = current->k1;
                current->k1 = k;
            } else {
                parent->k1 = current->k1;
                current->k1 = current->k2;
                current->k2 = k;
            }

            // Update pointers
            parent->left->right = parent->middle->left;
            parent->middle->left = parent->middle->middle;
            parent->middle->middle = parent->middle->right;
            parent->middle->right = child;

            parent->left->n = 2;
        }
    }

    return usefulData(); // Return appropriate usefulData
}


usefulData PokemonTree::split3node(two3node* current, Pokemon* k, two3node* child) {
    Pokemon* mid;
    two3node* newChild = new two3node;
    newChild->n = 1;

    if (*k < *(current->k1)) {
        mid = current->k1;
        newChild->k1 = current->k2;
        current->k1 = k;

        if (current->left != nullptr) {
            newChild->left = current->middle;
            newChild->middle = current->right;
            current->middle = child;
        }
    } else if (*k < *(current->k2)) {
        mid = k;
        newChild->k1 = current->k2;

        if (current->left != nullptr) {
            newChild->left = child;
            newChild->middle = current->right;
        }
    } else {
        mid = current->k2;
        newChild->k1 = k;

        if (current->left != nullptr) {
            newChild->left = current->right;
            newChild->middle = child;
        }
    }

    current->right = nullptr;
    current->n = 1;

    return usefulData(newChild, mid);
}
