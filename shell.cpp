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

        if(input[input.length()-1 ] == '.'){
        }
        else{
            while( input[input.length()-1 ] != '.'){
                std::cout << "|  " ;
                result_str  = result_str + input;
                //std::cout << result_str + "\n";
                getline(cin,input); 
            }
            result_str  = result_str + input;
        }
        
        Scanner s(result_str);
        Parser p(s);
        try {
            p.buildExpression();
            string result = "";

            if(! p.getExpressionTree()->evaluate() ) result = "false.";
            else result = p.getExpressionTree()->getEvaluateString() + "." ;
            if(result == "." ) result = "true.";

            std::cout << result <<"\n";

        } catch (std::string &msg) {
            std::cout <<  msg << "\n";
        }

        result_str = "";
        std::cout << "?-" ;
        getline(cin,input); 
        result_str  = result_str + input;
    }

    return 0 ;
}
