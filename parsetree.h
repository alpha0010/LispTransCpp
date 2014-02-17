#ifndef PARSETREE_H
#define PARSETREE_H

#include "nullptrdef.h"

class LispLex;
struct ParseNode;

class ParseTree
{
    public:
        ParseTree(LispLex& lexer);
        ~ParseTree();

        void Parse();

        void DumpTree(ParseNode* node = nullptr, int depth = 0, int activeMask = 0xfffffff);

    private:
        void HandleNode(ParseNode* node, bool nodeIsFirst);

        LispLex& m_Lexer;
        ParseNode* m_pRoot;
};

#endif // PARSETREE_H
