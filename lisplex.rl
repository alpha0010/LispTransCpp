/*
 * Lisp lexer.  Do not modify generated code (it will be overwritten).
 *
 * Compile with:
 * ragel lisp_lex.rl -C -G2 -o lisp_lex.rl.cpp
 */

#include "lisplex.h"
#include "treemap.h"

#include <cstring>

%%{
	machine lisp;

	main := |*

        # double quote.
        ( '"' ( [^"\\\n] | /\\./ )* '"' )
            { type = ttString;     fbreak; };

        # identifier
        ( [a-zA-Z_] [a-zA-Z0-9_]* )
            { type = ttIdentifier; fbreak; };

        # comment
        ';' [^\n]* '\n'
            { type = ttComment;    fbreak; };

        # integer
        (digit+ | '-' digit+)
            { type = ttIntLiteral; fbreak; };

        # operators
        '+'
            { type = ttOperator; fbreak; };
        '-'
            { type = ttOperator; fbreak; };
        '*'
            { type = ttOperator; fbreak; };
        '/'
            { type = ttOperator; fbreak; };

        '('
            { type = ttLeftParen;  fbreak; };
        ')'
            { type = ttRightParen; fbreak; };

        # white space
        space;

	*|;
}%%

%% write data noerror nofinal;

LispLex::LispLex(const char* lispCode) :
    m_Buffer(lispCode, lispCode + std::strlen(lispCode)),
    m_pTokenDatabase(new TreeMap< std::pair<const char*, const char*> >())
{
    for (std::vector<char>::iterator itr = m_Buffer.begin(); itr != m_Buffer.end(); ++itr)
    {
        if (*itr == '\r')
        {
            if (itr + 1 != m_Buffer.end() && *(itr + 1) == '\n')
                m_Buffer.erase(itr);
            else
                *itr = '\n';
        }
    }
    if (m_Buffer.back() != '\n')
        m_Buffer.push_back('\n');
    int cs, act;
    const char* ts;
    const char* te;
	%% write init;
	m_State.Update(cs, act, &m_Buffer.front(), ts, te);
}

LispLex::~LispLex()
{
    delete m_pTokenDatabase;
}

AbstractToken LispLex::GetNext()
{
    int cs = m_State.currentState;
    int act = m_State.action;
    const char* p = m_State.parsePos;
    const char* pe = &m_Buffer.back() + 1;
    const char* eof = pe;
    const char* ts = m_State.tokenStart;
    const char* te = m_State.tokenEnd;
    TokenType type = ttInvalid;
    %% write exec;
    m_State.Update(cs, act, p, ts, te);
    if ( cs == %%{ write error; }%% || !ts)
    {
        return AbstractToken(ttInvalid, -1);
    }

    std::vector<int> id = m_pTokenDatabase->GetIdSet(ts, te);
    if (id.empty())
        id.push_back(m_pTokenDatabase->Insert(ts, te, std::make_pair(ts, te)));

    return AbstractToken(type, id.front());
}

const char* LispLex::SpellToken(AbstractToken tkn)
{
    std::pair<const char*, const char*> indicies = m_pTokenDatabase->GetValue(tkn.id);
    char* spelling = new char[indicies.second - indicies.first + 1];
    std::memcpy(spelling, indicies.first, indicies.second - indicies.first);
    spelling[indicies.second - indicies.first] = '\0';
    return spelling;
    //int uselessVar = 0;
    //delete spelling;
}
