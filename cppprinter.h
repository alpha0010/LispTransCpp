#ifndef CPPPRINTER_H
#define CPPPRINTER_H

#include <iosfwd>

class LispLex;
class ParseTree;


class CppPrinter
{
    public:
        CppPrinter(LispLex& lexer, ParseTree& parser);

        void PrintTo(std::ostream& out);

    private:
        void PrintDataType(int id, std::ostream& out);

        LispLex& m_Lexer;
        ParseTree& m_Parser;
};

#endif // CPPPRINTER_H
