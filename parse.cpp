//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab2
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include <iostream>
#include "lex.h"
#include "tokens.h"
#include "parse.h"
#include "utils.h"

#define print(str) std::cout << str << std::endl;

bool FindChar(const char * c)
{
//    print("Find Char")
    if(PeekToken() == c[0]){
        AdvanceToken();
        return true;
    }else{
        return false;
    }
}

bool FindTIMESOP()
{
//    print("Find TIMESOP")
    if(FindChar("*") || FindChar("/")){
        
        return true;
    }
    return false;
}

bool FindPLUSOP()
{
//    print("Find PLUSOP")
    if(FindChar("+") || FindChar("-"))
    {
        return true;
    }
    return false;
}

bool FindTERM_P()
{
//    print("Find TERM_P")
    if(FindTIMESOP()){
        if(FindChar("[")){
            if(!FindEXPR()) return false;
            
            if(FindChar("]")){
                return FindTERM_P();
            }else{
                Error("]");
                return false;
            }
        }else{
            Error("[");
            return false;
        }
    }
    return true;
}

bool FindTERM()
{
//    print("Find TERM")
    if(FindChar("[")){
        if(!FindEXPR()) return false;
        if(FindChar("]")){
            if(FindTERM_P()) return true;
        }else{
            Error("]");
        }
    }

    else if(PeekToken() == INT_VAL){
        AdvanceToken();
        return true;
    }
    
    return false;
}
         
bool FindEXPR_P()
{
//    print("Find EXPR_P")
    if(FindPLUSOP()){
        if(FindChar("(")){
            if(!FindEXPR()) return false;
            
            if(FindChar(")")){
                return FindEXPR_P();
            }else{
                Error(")");
                return false;
            }
        }else{
            Error("(");
            return false;
        }
        
        
    }
    return true;
}
         
bool FindEXPR()
{
//    print("Find EXPR")
    
    if(FindChar("(")){
        
        if(!FindEXPR()) return false;
        
        if(FindChar(")")){
            
            if(FindEXPR_P()) return true;
            
        }else{
            Error(")");
        }

    }else if(FindTERM())
        return true;
    
    return false;
}
     
bool FindSTMT()
{
//    print("Find STMT")
    bool foundExpr = FindEXPR();
    
    if(PeekToken() == END){
        return false;
    }
    else if(PeekToken() != ';'){
        if(foundExpr) Error(";");
        while(PeekToken() != ';') AdvanceToken();
    }
    else{
        print("Found a statement");
    }
    AdvanceToken();
    return true;
}
     
bool FindSTMTS()
{

    while(FindSTMT());
    return true;
}


//*******************************************
// Find a PROG non-terminal
bool FindPROG()
{
    if(!FindSTMTS()) return false;
    
    if(PeekToken() == END)
        return true;
    
    Error("end");
    return false;
}
/*******************************************
bool FindExample()
{
    if (!FindPART1()) return false;
    
    int token = PeekToken();
    if (token != '+') return false;
    AdvanceToken();         // past '+'

    if (!FindPART2()) return false;

    return true;
}
*/

