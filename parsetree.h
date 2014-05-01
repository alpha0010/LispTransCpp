#ifndef PARSETREE_H
#define PARSETREE_H

#include "nullptrdef.h"

class LispLex;
struct AbstractToken;
struct ParseNode;

enum ParseVisitorAction
{
    pvaAbort,
    pvaContinue,
    pvaRecurse
};

class ParseTree
{
    public:
        ParseTree(LispLex& lexer);
        ~ParseTree();

        // ParseVisitorAction VisitFunctor::operator()(AbstractToken* curToken, int depth, ParseNode* curNode);
        // the parameter curNode can be passed to WalkTree() to start a new traversal from there
        template<typename VisitFunctor>
        void WalkTree(VisitFunctor Visit, ParseNode* parent = nullptr)
        {
            DoWalkTree(Visit, parent, 0);
        }

        void DumpTree();

    private:
        void Parse();

        void HandleNode(ParseNode* node, bool nodeIsFirst);
        bool VisitChildren(ParseNode** node, AbstractToken** curToken);

        template<typename VisitFunctor>
        void DoWalkTree(VisitFunctor& Visit, ParseNode* parent, int depth)
        {
            AbstractToken* curToken = nullptr;
            ParseNode* node = parent;
            while (VisitChildren(&node, &curToken))
            {
                switch (Visit(curToken, depth, node))
                {
                    default:
                    case pvaAbort:
                        return;

                    case pvaContinue:
                        break;

                    case pvaRecurse:
                        DoWalkTree(Visit, node, depth + 1);
                        break;
                }
            }
        }

        LispLex& m_Lexer;
        ParseNode* m_pRoot;
};

#endif // PARSETREE_H
