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

int c;

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
    c = next(file);
    root = Expression(root, file);
    return 0;
};

Node *Literal(Node *T, FILE *file)
{
    if (c == EOF)
    {
        return T;
    }
    else
    {
        T->data = c;
        T->left = nullptr;
        T->right = nullptr;
        // There is no error handling in this program, so assume that a correct expr is one that must reach
        // a literal (also required by grammar)
        c = next(file);
        return T;
    }
};

Node *Term(Node *T, FILE *file)
{
    if (c == '{')
    {
        c = next(file);
        Expression(T, file);
        c = next(file);
        return T;
    }
    else
    {
        return Literal(T, file);
    }
};

Node *Factor(Node *T, FILE *file)
{
    Node *termTree = new Node();
    termTree = Term(termTree, file);

    if (c == '+')
    {
        Node *factorTree = new Node();
        c = next(file);
        factorTree = Factor(factorTree, file);
        T->data = '+';
        T->left = termTree;
        T->right = factorTree;
        return T;
    }
    else if (c == '-')
    {
        Node *factorTree = new Node();
        c = next(file);
        factorTree = Factor(factorTree, file);
        T->data = '-';
        T->left = termTree;
        T->right = factorTree;
        return T;
    }
    else // <term> case
    {
        T = termTree;
        return T;
    }
};

Node *Expression(Node *T, FILE *file)
{
    Node *factorTree = new Node();
    factorTree = Factor(T, file); // Needs to be T as param, not factorTree

    if (c == '*')
    {
        Node *expressionTree = new Node();
        c = next(file);
        expressionTree = Expression(expressionTree, file);
        T->data = '*';
        T->left = factorTree;
        T->right = expressionTree;
        return T;
    }
    else if (c == '/')
    {
        Node *expressionTree = new Node();
        c = next(file);
        expressionTree = Expression(expressionTree, file);
        T->data = '/';
        T->left = factorTree;
        T->right = expressionTree;
        return T;
    }
    else // <factor> case
    {
        return factorTree;
    }
};

symbol next(FILE *file)
{
    return fgetc(file);
}