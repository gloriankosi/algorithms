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
 */

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
    return -1;
}

void Insert(struct Node *root, struct Node *temp, char *i)
{
    try
    {
        int val = stoi(i);
        while (temp != nullptr)
        {
            if (!temp->value)
            {
                temp->value = val;
                break;
            }
            if (val < temp->value)
            {
                if (temp->left == nullptr)
                {
                    Node *x = new Node();
                    x->value = val;
                    temp->left = x;
                    break;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else
            {
                if (temp->right == nullptr)
                {
                    Node *y = new Node();
                    y->value = val;
                    temp->right = y;
                    break;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
    }
    /**
     * @brief Ignore any input that isn't convertable to an integer
     * 
     */
    catch (invalid_argument)
    {
        ;
    }
}