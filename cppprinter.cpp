/*
node0 <__root__>
├─node1 0<'('>
│ ├─node2 1<'defun'>
│ ├─node2 2<'rectangleArea'>
│ ├─node1 0<'('>
│ │ ├─node2 3<'width'>
│ │ └─node2 4<'height'>
│ ├─node2 8<'"Compute the area of a circle, passed its radius."'>
│ └─node1 0<'('>
│   ├─node2 10<'*'>
│   ├─node2 3<'width'>
│   └─node2 4<'height'>
└─node1 0<'('>
  ├─node2 1<'defun'>
  ├─node2 12<'rectangle_area'>
  ├─node1 0<'('>
  │ ├─node2 13<'w'>
  │ └─node2 14<'h'>
  ├─node2 15<'"Compute the area of a circle, given its radius interactively."'>
  ├─node1 0<'('>
  │ ├─node2 18<'interactive'>
  │ └─node2 19<'"nWidth: \nnHeight: "'>
  ├─node1 0<'('>
  │ ├─node2 21<'setq'>
  │ ├─node2 22<'area'>
  │ └─node1 0<'('>
  │   ├─node2 2<'rectangleArea'>
  │   ├─node2 13<'w'>
  │   └─node2 14<'h'>
  └─node1 0<'('>
    ├─node2 25<'message'>
    ├─node2 26<'"The rectangle's area is %f."'>
    └─node2 22<'area'>
*/

#include "cppprinter.h"

#include "lisplex.h"
#include "parsetree.h"

#include <ostream>

static int kw_defun;

CppPrinter::CppPrinter(LispLex& lexer, ParseTree& parser) :
    m_Lexer(lexer), m_Parser(parser)
{
    kw_defun = m_Lexer.GetIdForString("defun");
}

enum DataType
{
    dtUnknown,
    dtInt,
    dtFloat,
    dtString
};

struct VariableDef
{
    VariableDef(AbstractToken identifier) : type(dtUnknown), name(identifier) {}

    DataType type;
    AbstractToken name;
};

struct StatementDef
{
    // todo?
};

struct FunctionDef
{
    FunctionDef(AbstractToken identifier) : returnType(dtUnknown), name(identifier) {}

    DataType returnType;
    AbstractToken name;
    std::vector<VariableDef> parameters;
    std::vector<StatementDef> body;
};

#if 0
struct CppTranslator
{
    int lastDepth;
    enum TranslatorState
    {
        tsNone,
        tsFuncId,
        tsAppendParam,
        tsBeginBody
    };
    TranslatorState state;

    CppTranslator() : lastDepth(0), state(tsNone) {}

    ParseVisitorAction operator()(AbstractToken* curToken, int depth, ParseNode* curNode);
};

ParseVisitorAction CppTranslator::operator(AbstractToken* curToken, int depth, ParseNode* curNode)
{
    switch (state)
    {
        default:
        case tsNone:
            if (curToken->id == kw_defun)
                state = tsFuncId;
            break;

        case tsFuncId:
            if (curToken->type != ttIdentifier)
                return pvaAbort; // error
            functions.push_back(FunctionDef(*curToken));
            state = tsAppendParam;
            break;

        case tsAppendParam:
            m_Parser.WalkTree(XXX, curNode);
            return pvaContinue;
    }
    lastDepth = depth;
    return pvaRecurse;
}
#endif // 0

struct ParamScanner
{
    FunctionDef& m_Func;

    ParamScanner(FunctionDef& func) :
        m_Func(func)
    {
    }

    ParseVisitorAction operator()(AbstractToken* curToken, int depth, ParseNode* curNode)
    {
        if (curToken->type != ttIdentifier)
            return pvaAbort;
        m_Func.parameters.push_back(VariableDef(*curToken));
        return pvaContinue;
    }
};

struct StatementScanner
{
    ParseVisitorAction operator()(AbstractToken* curToken, int depth, ParseNode* curNode)
    {
        return pvaContinue; // TODO
    }
};

struct FuncScanner
{
    ParseTree& m_Parser;
    std::vector<FunctionDef>& m_Funcs;
    enum FSState
    {
        fsBegin,
        fsIdentify,
        fsParams,
        fsDoc,
        fsBody
    } m_State;

    FuncScanner(ParseTree& parser, std::vector<FunctionDef>& funcs) :
        m_Parser(parser), m_Funcs(funcs), m_State(fsBegin)
    {
    }

    ParseVisitorAction operator()(AbstractToken* curToken, int depth, ParseNode* curNode)
    {
        switch (m_State)
        {
            default:
                return pvaAbort;

            case fsBegin:
                if (curToken->id != kw_defun)
                    return pvaAbort;
                m_State = fsIdentify;
                break;

            case fsIdentify:
                if (curToken->type != ttIdentifier)
                    return pvaAbort;
                m_Funcs.push_back(FunctionDef(*curToken));
                m_State = fsParams;
                break;

            case fsParams:
                if (curToken->type != ttLeftParen)
                    return pvaAbort;
                m_Parser.WalkTree(ParamScanner(m_Funcs.back()), curNode);
                m_State = fsDoc;
                break;

            case fsDoc:
                m_State = fsBody;
                if (curToken->type == ttString)
                    break; // eat doc string (TODO: store?)
                // fall through
            case fsBody:
                m_Parser.WalkTree(StatementScanner(), curNode); // TODO!!!
                break;
        }
        return pvaContinue;
    }
};

struct CppTranslator
{
    ParseTree& m_Parser;
    std::vector<FunctionDef>& m_Funcs;

    CppTranslator(ParseTree& parser, std::vector<FunctionDef>& funcs) :
        m_Parser(parser), m_Funcs(funcs)
    {
    }

    ParseVisitorAction operator()(AbstractToken* curToken, int depth, ParseNode* curNode)
    {
        m_Parser.WalkTree(FuncScanner(m_Parser, m_Funcs), curNode);
        return pvaContinue;
    }
};

void CppPrinter::PrintTo(std::ostream& out)
{
    std::vector<FunctionDef> functions;
    m_Parser.WalkTree(CppTranslator(m_Parser, functions));
    for (std::vector<FunctionDef>::const_iterator fItr = functions.begin();
         fItr != functions.end(); ++fItr)
    {
        PrintDataType(fItr->returnType, out);
        std::vector<char> tknStr;
        m_Lexer.SpellToken(fItr->name, tknStr);
        out << ' ' << &tknStr.front() << '(';
        for (std::vector<VariableDef>::const_iterator pItr = fItr->parameters.begin();
             pItr != fItr->parameters.end(); ++pItr)
        {
            if (pItr != fItr->parameters.begin())
                out << ", ";
            PrintDataType(pItr->type, out);
            m_Lexer.SpellToken(pItr->name, tknStr);
            out << ' ' << &tknStr.front();
        }
        out << ")\n{";
        // TODO
        out << '}';
    }
}

void CppPrinter::PrintDataType(int id, std::ostream& out)
{
    switch (id)
    {
        default:
        case dtUnknown:
            out << "<dtUnknown>";
            break;

        case dtInt:
            out << "int";
            break;

        case dtFloat:
            out << "double";
            break;

        case dtString:
            out << "std::string";
            break;
    }
}
