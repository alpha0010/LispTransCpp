
#line 1 "/home/alpha/dev/LispTransCpp/lisplex.rl"
/*
 * Lisp lexer.  Do not modify generated code (it will be overwritten).
 *
 * Compile with:
 * ragel lisp_lex.rl -C -G2 -o lisp_lex.rl.cpp
 */

#include "lisplex.h"
#include "treemap.h"

#include <cstring>


#line 53 "/home/alpha/dev/LispTransCpp/lisplex.rl"



#line 21 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
static const int lisp_start = 4;

static const int lisp_en_main = 4;


#line 56 "/home/alpha/dev/LispTransCpp/lisplex.rl"

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
	
#line 49 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
	{
	cs = lisp_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 77 "/home/alpha/dev/LispTransCpp/lisplex.rl"
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
    
#line 77 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr2:
#line 20 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttString;     {p++; cs = 4; goto _out;} }}
	goto st4;
tr5:
#line 28 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttComment;    {p++; cs = 4; goto _out;} }}
	goto st4;
tr6:
#line 50 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;}
	goto st4;
tr7:
#line 45 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttLeftParen;  {p++; cs = 4; goto _out;} }}
	goto st4;
tr8:
#line 47 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttRightParen; {p++; cs = 4; goto _out;} }}
	goto st4;
tr9:
#line 40 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttOperator; {p++; cs = 4; goto _out;} }}
	goto st4;
tr10:
#line 36 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttOperator; {p++; cs = 4; goto _out;} }}
	goto st4;
tr12:
#line 42 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p+1;{ type = ttOperator; {p++; cs = 4; goto _out;} }}
	goto st4;
tr15:
#line 1 "NONE"
	{	switch( act ) {
	case 4:
	{{p = ((te))-1;} type = ttIntLiteral; {p++; cs = 4; goto _out;} }
	break;
	case 6:
	{{p = ((te))-1;} type = ttOperator; {p++; cs = 4; goto _out;} }
	break;
	}
	}
	goto st4;
tr16:
#line 24 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{te = p;p--;{ type = ttIdentifier; {p++; cs = 4; goto _out;} }}
	goto st4;
st4:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 1 "NONE"
	{ts = p;}
#line 139 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
	switch( (*p) ) {
		case 32: goto tr6;
		case 34: goto st1;
		case 40: goto tr7;
		case 41: goto tr8;
		case 42: goto tr9;
		case 43: goto tr10;
		case 45: goto tr11;
		case 47: goto tr12;
		case 59: goto st3;
		case 95: goto st6;
	}
	if ( (*p) < 48 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto tr6;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st6;
		} else if ( (*p) >= 65 )
			goto st6;
	} else
		goto tr13;
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
tr11:
#line 1 "NONE"
	{te = p+1;}
#line 38 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{act = 6;}
	goto st5;
tr13:
#line 1 "NONE"
	{te = p+1;}
#line 32 "/home/alpha/dev/LispTransCpp/lisplex.rl"
	{act = 4;}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 198 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr13;
	goto tr15;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 10 )
		goto tr5;
	goto st3;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 95 )
		goto st6;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st6;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st6;
	} else
		goto st6;
	goto tr16;
	}
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 5: goto tr15;
	case 6: goto tr16;
	}
	}

	_out: {}
	}

#line 96 "/home/alpha/dev/LispTransCpp/lisplex.rl"
    m_State.Update(cs, act, p, ts, te);
    if ( cs == 
#line 247 "/home/alpha/dev/LispTransCpp/lisplex.rl.cpp"
0
#line 97 "/home/alpha/dev/LispTransCpp/lisplex.rl"
 || !ts)
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
