#include <gtest/gtest.h>
#include "atom.h"
#include "variable.h"
#include "exp.h"
#include "parser.h"

using namespace std;

int main( int argc , char **argv )
{
    std::cout << "Welcome to SWI-Prolog." << "\n";

    string input = "";
    string result_str = "";
    std::cout << "?-" ;
    getline(cin,input); 
    result_str  = result_str + input;
    while(input != "halt."){

        while( input[input.length()-1 ] != '.'){
            std::cout << "|  " ;
            if(result_str.length()!= 0)result_str  = result_str + input;
            //std::cout << result_str + "\n";
            getline(cin,input); 
        }
        std::cout << "*****\n";
        Scanner s(result_str);

        Parser p(s);
std::cout << "*1\n";
std::cout << result_str +  "*****\n";
        p.buildExpression();
        p.getExpressionTree()->evaluate();
        string result = p.getExpressionTree()->getEvaluateString() + "." ;
std::cout << "**2***\n";
        std::cout << result + "\n";
        result_str = "";
        std::cout << "?-" ;
        getline(cin,input); 
        result_str  = result_str + input;
    }

    return 0 ;
}
