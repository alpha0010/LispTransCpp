/*
 * Lisp lexer
 */

#ifndef LISPLEX_H
#define LISPLEX_H

#include <vector>

template<typename _Tp> class TreeMap;

enum TokenType
{
    ttIdentifier,
    ttString,
    ttInteger,
    ttFloat,
    ttOperator,
    ttLeftParen,
    ttRightParen,
    ttComment,
    ttInvalid
};

struct AbstractToken
{
    AbstractToken(TokenType _type, int _id) :
        type(_type), id(_id)
    {
    }

    TokenType type;
    int id;
};


class LispLex
{
    public:
        LispLex(const char* lispCode);
        ~LispLex();

        AbstractToken GetNext();

        int GetIdForString(const char* str); // do not call until lexical analysis is complete
        void SpellToken(AbstractToken tkn, std::vector<char>& str);

    private:
        std::vector<char> m_Buffer;
        TreeMap< std::pair<const char*, const char*> >* m_pTokenDatabase;

        struct State
        {
            void Update(int cs, int act, const char* p, const char* ts, const char* te)
            {
                currentState = cs;
                action = act;
                parsePos = p;
                tokenStart = ts;
                tokenEnd = te;
            }

            int currentState;
            int action;
            const char* parsePos;
            const char* tokenStart;
            const char* tokenEnd;
        } m_State;
};

#endif // LISPLEX_H
