#include "parsetree.h"

#include "lisplex.h"

#include <iostream>

enum PNodeType
{
    pntRoot,
    pntGroup,
    pntLiteral
};

struct ParseNode
{
    ParseNode(PNodeType tp, AbstractToken tkn) :
        type(tp),
        token(tkn),
        firstChild(nullptr),
        nextSibling(nullptr)
    {
    }

    ~ParseNode()
    {
        if (firstChild)
            delete firstChild;
        if (nextSibling)
            delete nextSibling;
    }

    PNodeType type;
    AbstractToken token;
    ParseNode* firstChild;
    ParseNode* nextSibling;
};


ParseTree::ParseTree(LispLex& lexer) :
    m_Lexer(lexer), m_pRoot(new ParseNode(pntRoot, AbstractToken(ttInvalid, -1)))
{
}

ParseTree::~ParseTree()
{
    delete m_pRoot;
}

void ParseTree::Parse()
{
    ParseNode* node = m_pRoot;
    for (AbstractToken tkn = m_Lexer.GetNext();
         tkn.type != ttInvalid; tkn = m_Lexer.GetNext())
    {
        if (tkn.type == ttComment)
            continue;
        if (tkn.type == ttLeftParen)
        {
            if (node == m_pRoot)
                node = node->firstChild = new ParseNode(pntGroup, tkn);
            else
                node = node->nextSibling = new ParseNode(pntGroup, tkn);
            HandleNode(node, true);
        }
        else
        {
            std::cerr << "Error in ParseTree::Parse()\n";
            return; // error
        }
    }
    DumpTree();
}

void ParseTree::DumpTree(ParseNode* node, int depth, int activeMask)
{
    if (!node)
        node = m_pRoot;
    while (node)
    {
        for (int i = 0; i < depth - 1; ++i)
        {
            if (((1 << i) & activeMask) != 0)
                std::cout << "│ ";
            else
                std::cout << "  ";
        }
        if (depth != 0)
        {
            if (node->nextSibling)
            {
                std::cout << "├─";
                activeMask |= (1 << (depth - 1));
            }
            else
            {
                std::cout << "└─";
                activeMask &= ~(1 << (depth - 1));
            }
        }
        std::cout << "node" << node->type << "\n";
        if (node->firstChild)
            DumpTree(node->firstChild, depth + 1, activeMask);
        node = node->nextSibling;
    }
}

void ParseTree::HandleNode(ParseNode* node, bool nodeIsFirst)
{
    AbstractToken tkn = m_Lexer.GetNext();
    while (tkn.type == ttComment)
        tkn = m_Lexer.GetNext();
    PNodeType nodeType = pntRoot;
    switch (tkn.type)
    {
        case ttLeftParen:
            nodeType = pntGroup;
            break;

        case ttIdentifier:
        case ttString:
        case ttIntLiteral:
        case ttOperator:
            nodeType = pntLiteral;
            break;

        case ttRightParen:
            return; // fall back to parent scope

        case ttInvalid:
        default:
            std::cerr << "Error in ParseTree::HandleNode()\n";
            return; // error! fall back to parent scope
    }
    if (nodeIsFirst)
        node = node->firstChild = new ParseNode(nodeType, tkn);
    else
        node = node->nextSibling = new ParseNode(nodeType, tkn);

    if (nodeType == pntGroup)
        HandleNode(node, true); // process sub-nodes

    HandleNode(node, false); // process next nodes
}
