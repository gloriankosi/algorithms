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

void Expression(Node *&, FILE *);
void Factor(Node *&, FILE *);
void Term(Node *&, FILE *);
void Literal(Node *&, FILE *);

void next(FILE *, symbol &);

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

    next(file, c);

    Expression(root, file);
    cout << (char)root->data << "\n";
    cout << (char)root->left->data << "\n";
    cout << (char)root->right->data << "\n";
    cout << (char)root->right->left->data << "\n";
    cout << (char)root->right->right->data << "\n";
    return 0;
};

void Literal(Node *&T, FILE *file)
{
    T->data = c;
    T->left = nullptr;
    T->right = nullptr;
    next(file, c);
};

void Term(Node *&T, FILE *file)
{
    if (c == '{')
    {
        next(file, c);
        Expression(T, file);
        next(file, c);
    }
    else
    {
        Literal(T, file);
    }
};

void Factor(Node *&T, FILE *file)
{
    Node *termTree = new Node();
    Term(termTree, file);

    if (c == '+')
    {
        Node *factorTree = new Node();
        next(file, c);
        Factor(factorTree, file);
        T->data = '+';
        T->left = termTree;
        T->right = factorTree;
    }
    else if (c == '-')
    {
        Node *factorTree = new Node();
        next(file, c);
        Factor(factorTree, file);
        T->data = '-';
        T->left = termTree;
        T->right = factorTree;
    }
    else // <term> case
    {
        T = termTree;
    }
};

void Expression(Node *&T, FILE *file)
{
    Node *factorTree = new Node();
    Factor(factorTree, file);

    if (c == '*')
    {
        Node *expressionTree = new Node();
        next(file, c);
        Expression(expressionTree, file);
        T->data = '*';
        T->left = factorTree;
        T->right = expressionTree;
    }
    else if (c == '/')
    {
        Node *expressionTree = new Node();
        next(file, c);
        Expression(expressionTree, file);
        T->data = '/';
        T->left = factorTree;
        T->right = expressionTree;
    }
    else // <factor> case
    {
        T = factorTree;
    }
};

void next(FILE *file, symbol &c)
{
    c = fgetc(file);
}