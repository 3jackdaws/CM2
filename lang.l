%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include "tokens.h"

#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
period          ['.']
whitespace      [\n\r\t ]
%%

    // token definitions go here. "if" is an example.

[/]{2}.*                    {/* inline comment */}
"/*"([\n\r\t ]|.)*"*/"      {/* multiline comments */}
{whitespace}+               {/* count line */}

"end"                       DO_RETURN(END);
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');

"["                         DO_RETURN('[');
"]"                         DO_RETURN(']');
";"                         DO_RETURN(';');


[0-9]+                      DO_RETURN(INT_VAL);

"+"                         DO_RETURN('+');
"-"                         DO_RETURN('-');
"/"                         DO_RETURN('/');
"*"                         DO_RETURN('*');
[a-z]+                      {   /*pass*/   }
[%]+                        DO_RETURN(JUNK_TOKEN);





%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

