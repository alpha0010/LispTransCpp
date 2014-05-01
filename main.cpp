#include "cppprinter.h"
#include "lisplex.h"
#include "parsetree.h"
//#include "rational.h"

#include <iostream>

int main()
{
    const char* lispCode = //"(defun circleArea (radius)  502 -21 ; define a function 'circleArea' that takes one\n                             ; parameter 'radius'\n)";
"(defun sum (numA numB) (+ numA numB))";
/*
"(defun rectangleArea (width height) ; define a function 'rectangleArea' that takes one\n"
"                                    ; parameter 'radius'\n"
"  \"Compute the area of a circle, passed its radius.\" ; document this function\n"
"  (* width height))  ; compute (pi r^2)\n"
"\n"
"(defun rectangle_area(w h)\n"
" \"Compute the area of a circle, given its radius interactively.\" ; document\n"
"                                                                   ; this funct\n"
"  (interactive \"nWidth: \\nnHeight: \") ; state this function can be called interactively\n"
"  (setq area (rectangleArea w h)) ; assign the symbol 'area' the result of calling\n"
"                                  ; function 'rectangleArea' with arguments 'w' and 'h'\n"
"  (message \"The rectangle's area is %f.\" area)) ; output the computed area\n";
*/
    LispLex lexer(lispCode);
    ParseTree parser(lexer);
    parser.DumpTree();
    std::cout << std::endl;
    CppPrinter printer(lexer, parser);
    printer.PrintTo(std::cout);
    /*for (AbstractToken tkn = lexer.GetNext();
         tkn.type != ttInvalid; tkn = lexer.GetNext())
    {
        int doStuff = 0;
        ++doStuff;
        doStuff -= tkn.id;
        lexer.SpellToken(tkn);
    }*/
    /*Rational a(2, 5);
    Rational b = a;
    Rational c = a + b;
    c = -a;
    b = (a - c);
    c = Rational(15, 3);
    c = Rational(3, 15);
    b = c / a;
    c = b + 3;
    if (a < b)
        return 0;*/
    return 0;
}
