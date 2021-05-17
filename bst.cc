/**
 * @file bst.cc
 * @author Glorian Kosi
 * -------Must be using at least C++20---------
 * To compile, example:
 * g++ -std=c++2a bst.cc -o bst
 * 
 * To run:
 * ./bst [some-integers]
 * 
 * Left subtree < Root
 * Right subtree >= Root
 */

// TODO: Add delete and search functions

#include <iostream>
#include <optional>
using std::cout;
using std::invalid_argument;
using std::optional;
using std::stoi;

/**
 * @brief Node struct
 * 
 * 
 */
struct Node
{
    optional<int> value;
    Node *left = nullptr;  // Pointer to left subtree
    Node *right = nullptr; // Pointer to right subtree
};

/**
 * @brief 
 * 
 * @param root Pointer to root node
 * @param temp Pointer to node that traverses the tree during insertion
 * @param i Command-line argument 
 */
void Insert(struct Node *root, struct Node *temp, char *i);

/**
 * @brief Standard main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    Node *root = new Node(); // Root of the BST
    Node *temp = root;       // Pointer that traverses tree during insertion
    for (char **i = argv; i != argv + argc; i++)
    {
        Insert(root, temp, *i);
    }
    /**
     * @brief Enter testing expressions below or above this comment block
     * 
     * Example using stdout to get value of first node in the left subtree of the root:
     * cout<<*root->left->value<<"\n";
     * 
     * Likewise for first node in the right subtree of root:
     * cout<<*root->right->value<<"\n"
     * 
     * Or, 
     * root=root->left; Move root to the first node on left, same expressions as before to print values
     */
    return -1;
}

void Insert(struct Node *root, struct Node *temp, char *i)
{
    try
    {
        int val = stoi(i); // Attempt conversion from char to int

        if (!temp->value) // Needed because no initial value in root->value
        {
            temp->value = val;
        }

        while (temp != nullptr)
        {
            if (val < temp->value) // If current value from command-line is less than the node we're sitting on
            {
                // Check if the left subtree for the node we're sitting on is empty,
                // if empty, make a new Node x, set x->value to the current value from command-line, and
                // set it to the left subtree of the temp node
                if (temp->left == nullptr)
                {
                    Node *x = new Node();
                    x->value = val;
                    temp->left = x;
                    break;
                }
                // If temp->left is NOT null, then go onto the next node in the left subtree
                else
                {
                    temp = temp->left;
                }
            }
            else // Else the current value from command-line is >= to temp->value (node we're sitting on)
            {
                // Same procedure as left subtree, but we use right subtree instead
                if (temp->right == nullptr)
                {
                    Node *y = new Node();
                    y->value = val;
                    temp->right = y;
                    break;
                }
                // Same procedure as left subtree, but we go to the next node in the right subtree instead.s
                else
                {
                    temp = temp->right;
                }
            }
        }
    }
    /**
     * @brief Ignore any input that isn't convertable to an integer
     */
    catch (invalid_argument)
    {
        ;
    }
}