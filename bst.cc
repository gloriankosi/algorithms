/**
 * @file bst.cc
 * @author Glorian Kosi
 * 
 * -------Must be using at least C++20---------
 * To compile, example:
 * g++ -std=c++2a bst.cc -o bst
 * 
 * To run:
 * ./bst [some-integers]
 * 
 * Left subtree < Root
 * Right subtree >= Root
 * 
 * Uses inorder successor for deletion of a node with 2 children
 * 
 */

// TODO: Add search functions

#include <iostream>
#include <optional>
#include <string>

using std::cout;
using std::invalid_argument;
using std::optional;
using std::stoi;
using std::string;

/**
 * @brief Node struct
 */
struct Node
{
    optional<int> value;
    Node *left = nullptr;  // Pointer to left subtree
    Node *right = nullptr; // Pointer to right subtree
    Node() {}
    Node(int value) : value(value) {}
};

/**
 * @brief Insert node into a tree
 * 
 * @param root 
 * @param temp 
 * @param i 
 */
void Insert(struct Node *&, struct Node *, char *);

/**
 * @brief Delete a node from a tree
 * 
 * @param root
 * @param i 
 * @return struct Node* 
 */
struct Node *Delete(struct Node *root, int i);
/**
 * @brief Find minimum value in a tree
 * 
 * @param root 
 * @return struct Node* 
 */
struct Node *Min(struct Node *root);
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
    root = Delete(root, 10);
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
    cout << *root->value << "\n";
    return -1;
}

void Insert(struct Node *&root, struct Node *temp, char *i)
{
    try
    {
        int val = stoi(i); // Attempt conversion from char to int
        /**
         * @brief 
         * Needed because no initial value in root->value, return from here after
         * root value is set or it will end up in the right sub-tree.
         */
        if (!temp->value)
        {
            temp->value = val;
            return;
        }

        while (temp != nullptr)
        {
            if (val < temp->value) // If current value from command-line is less than the node we're sitting on
            {
                // Check if the left subtree for the node we're sitting on is empty,
                // if empty, make a new Node x and set value to the current value from command-line, and
                // set it to the left subtree of the temp node
                if (temp->left == nullptr)
                {
                    temp->left = new Node(val);
                    return;
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
                    temp->right = new Node(val);
                    return;
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

struct Node *Delete(struct Node *root, int i)
{
    if (i < root->value) // If i is less than the current node value, then traverse left subtree
    {
        root->left = Delete(root->left, i);
    }

    if (i > root->value) // If value of the i is greater than the current node value, then traverse right subtree
    {
        root->right = Delete(root->right, i);
    }
    if (i == root->value)
    {
        if (root->left == nullptr)
        {
            struct Node *x = root->right;
            delete root;
            return x;
        }
        if (root->right == nullptr)
        {
            struct Node *y = root->left;
            delete root;
            return y;
        }
        struct Node *z = Min(root->right);
        root->value = z->value;
        root->right = Delete(root->right, root->value.value());
    }
    return root;
}

struct Node *Min(struct Node *root)
{
    Node *xy = root;
    while (xy && xy->left != nullptr)
    {
        xy = xy->left;
    }
    return xy;
}