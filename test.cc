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
Node *Literal(Node *, FILE *, symbol c);

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
    root = Expression(root, file);
    cout << (char)root->data << "\n";
    cout << (char)root->left->data << "\n";
    cout << (char)root->right->data << "\n";
    return 0;
};

Node *Literal(Node *T, FILE *file, symbol c)
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
        return T;
    }
};

Node *Term(Node *T, FILE *file)
{
    symbol c = fgetc(file);

    if (c == '{')
    {
        Expression(T, file);
        fgetc(file);
        return T;
    }
    else
    {
        Node *literalTree = new Node();
        literalTree = Literal(T, file, c);
        T = literalTree;
        return T;
    }
};

Node *Factor(Node *T, FILE *file)
{

    Node *termTree = new Node();
    termTree = Term(termTree, file);
    symbol c = fgetc(file);

    if (c == '+')
    {

        Node *factorTree = new Node();
        factorTree = Factor(T, file);
        T->data = '+';
        T->left = termTree;
        T->right = factorTree;
        return T;
    }
    else if (c == '-')
    {
        Node *factorTree = new Node();
        factorTree = Factor(T, file);
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
    factorTree = Factor(factorTree, file);
    symbol c = fgetc(file);

    if ((c = fgetc(file)) == '*')
    {
        Node *expressionTree = new Node();
        expressionTree = Expression(T, file);
        T->data = '*';
        T->left = factorTree;
        T->right = expressionTree;
        return T;
    }
    else if (c == '/')
    {
        Node *expressionTree = new Node();
        expressionTree = Expression(T, file);
        T->data = '/';
        T->left = factorTree;
        T->right = expressionTree;
        return T;
    }
    else // <factor> case
    {
        T = factorTree;
        return T;
    }
};

symbol next(FILE *file)
{
    return fgetc(file);
}