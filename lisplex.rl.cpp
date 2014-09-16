
#line 1 "/home/alpha/dev/LispTransCpp/lisplex.rl"
/*
 * Lisp lexer.  Do not modify generated code (it will be overwritten).
 *
 * Compile with:
 * ragel lisp_lex.rl -C -G2 -o lisp_lex.rl.cpp
 */

#include "lisplex.h"
#include "nullptrdef.h"
#include "treemap.h"

#include <cstring>


#line 58 "/home/alpha/dev/LispTransCpp/lisplex.rl"



#line 22 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
static const int lisp_start = 5;

static const int lisp_en_main = 5;


#line 61 "/home/alpha/dev/LispTransCpp/lisplex.rl"

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

#line 50 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
	{
	cs = lisp_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 82 "/home/alpha/dev/LispTransCpp/lisplex.rl"
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

#line 78 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr2:
#line 21 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttString;     {p++; cs = 5; goto _out;} }}
	goto st5;
tr4:
#line 33 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{{p = ((te))-1;}{ type = ttInteger;    {p++; cs = 5; goto _out;} }}
	goto st5;
tr7:
#line 29 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttComment;    {p++; cs = 5; goto _out;} }}
	goto st5;
tr8:
#line 55 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;}
	goto st5;
tr9:
#line 50 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttLeftParen;  {p++; cs = 5; goto _out;} }}
	goto st5;
tr10:
#line 52 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttRightParen; {p++; cs = 5; goto _out;} }}
	goto st5;
tr11:
#line 45 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttOperator; {p++; cs = 5; goto _out;} }}
	goto st5;
tr12:
#line 41 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttOperator; {p++; cs = 5; goto _out;} }}
	goto st5;
tr14:
#line 47 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttOperator; {p++; cs = 5; goto _out;} }}
	goto st5;
tr17:
#line 43 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p;p--;{ type = ttOperator; {p++; cs = 5; goto _out;} }}
	goto st5;
tr18:
#line 33 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p;p--;{ type = ttInteger;    {p++; cs = 5; goto _out;} }}
	goto st5;
tr20:
#line 37 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p;p--;{ type = ttFloat;      {p++; cs = 5; goto _out;} }}
	goto st5;
tr21:
#line 25 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p;p--;{ type = ttIdentifier; {p++; cs = 5; goto _out;} }}
	goto st5;
st5:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 1 "NONE"
	{ts = p;}
#line 144 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
	switch( (*p) ) {
		case 32: goto tr8;
		case 34: goto st1;
		case 40: goto tr9;
		case 41: goto tr10;
		case 42: goto tr11;
		case 43: goto tr12;
		case 45: goto st6;
		case 47: goto tr14;
		case 59: goto st4;
		case 95: goto st9;
	}
	if ( (*p) < 48 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto tr8;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st9;
		} else if ( (*p) >= 65 )
			goto st9;
	} else
		goto tr15;
	goto st0;
st0:
cs = 0;
	goto _out;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 10: goto st0;
		case 34: goto tr2;
		case 92: goto st2;
	}
	goto st1;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	goto st1;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr15;
	goto tr17;
tr15:
#line 1 "NONE"
	{te = p+1;}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 202 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
	if ( (*p) == 46 )
		goto st3;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr15;
	goto tr18;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st8;
	goto tr4;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st8;
	goto tr20;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 10 )
		goto tr7;
	goto st4;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 95 )
		goto st9;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st9;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st9;
	} else
		goto st9;
	goto tr21;
	}
	_test_eof5: cs = 5; goto _test_eof;
	_test_eof1: cs = 1; goto _test_eof;
	_test_eof2: cs = 2; goto _test_eof;
	_test_eof6: cs = 6; goto _test_eof;
	_test_eof7: cs = 7; goto _test_eof;
	_test_eof3: cs = 3; goto _test_eof;
	_test_eof8: cs = 8; goto _test_eof;
	_test_eof4: cs = 4; goto _test_eof;
	_test_eof9: cs = 9; goto _test_eof;

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 6: goto tr17;
	case 7: goto tr18;
	case 3: goto tr4;
	case 8: goto tr20;
	case 9: goto tr21;
	}
	}

	_out: {}
	}

#line 101 "/home/alpha/dev/LispTransCpp/lisplex.rl"
    m_State.Update(cs, act, p, ts, te);
    if ( cs ==
#line 273 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
0
#line 102 "/home/alpha/dev/LispTransCpp/lisplex.rl"
 || !ts)
    {
        return AbstractToken(ttInvalid, -1);
    }

    if (type == ttString) // strip quotes
    {
        ++ts;
        --te;
    }

    std::vector<int> id = m_pTokenDatabase->GetIdSet(ts, te);
    if (id.empty())
        id.push_back(m_pTokenDatabase->Insert(ts, te, std::make_pair(ts, te)));

    return AbstractToken(type, id.front());
}

int LispLex::GetIdForString(const char* str)
{
    const char* strEnd = str + std::strlen(str);
    std::vector<int> id = m_pTokenDatabase->GetIdSet(str, strEnd);
    if (id.empty()) // force creation
        return m_pTokenDatabase->Insert(str, strEnd, std::make_pair<const char*, const char*>(nullptr, nullptr));
    return id.front();
}

void LispLex::SpellToken(AbstractToken tkn, std::vector<char>& str)
{
    std::pair<const char*, const char*> indicies = m_pTokenDatabase->GetValue(tkn.id);
    str.assign(indicies.second - indicies.first + 1, '\0');
    std::memcpy(&str.front(), indicies.first, indicies.second - indicies.first);
}
