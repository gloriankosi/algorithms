/**
 * @file bnf-recursive-desc.cc
 * @author Glorian Kosi
 * @brief 
 * 
 * 
----Grammar used:
<expression>  ::=  <factor>  * <expression>   |   <factor>  /  <expression>   |   <factor>
<factor>  :==  <term> + <factor>  |  <term> - <factor>  |  <term>
<term>  ::=  {  <expression>  }  |  <literal>
<literal>  ::=  0|1|2|3|4|5|6|7|8|9
----
 * 
 */

#include <iostream>

using std::cin;
using std::cout;

typedef int symbol;

struct Node
{
    symbol data;
    Node *left = nullptr;
    Node *right = nullptr;
};

Node *Expression(Node *, FILE *);
Node *Factor(Node *, FILE *);
Node *Term(Node *, FILE *);
Node *Literal(Node *, FILE *);

symbol next(FILE *);

int main(int argc, char *argv[])
{
    Node *root = new Node();
    FILE *file;
    try
    {
        file = fopen(argv[1], "r");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
};

Node *Factor(Node *Tree, FILE *file){

};

Node *Expression(Node *Tree, FILE *file)
{
    symbol c;
    Node *factorTree = Factor(factorTree, file);
    if ((c = fgetc(file)) == '*')
    {
        Node *expressionTree = Expression(expressionTree, file);
        Tree->data = '*';
        Tree->left = factorTree;
        Tree->right = expressionTree;
        return Tree;
    }
    else if ((c = fgetc(file)) == '/')
    {
        Node *expressionTree = Expression(expressionTree, file);
        Tree->data = '/';
        Tree->left = factorTree;
        Tree->right = expressionTree;
        return Tree;
    }
    else // <factor> case
    {
        Tree = factorTree;
        return Tree;
    }
};

symbol next(FILE *file)
{
    return fgetc(file);
}