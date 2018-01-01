#ifndef PARSER_H
#define PARSER_H
#include <sstream>

#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>

using std::stack;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void buildExpression(){
    // createTerm();
    disjunctionMatch();
    restDisjunctionMatch();
          // std::cout << _scanner.currentChar() << "\n" ;
    if (createTerm() != nullptr || _currentToken == EOS){
      throw string("Missing token '.'");
    }
    else if( _currentToken != '.'){
      std::stringstream ss;
      string s;
      char c = _currentToken;
      ss << c; 
      ss >> s;
      throw string("Unexpected '"+ s +"' before '.'");
    }
  }

  void restDisjunctionMatch() {
    if (_scanner.currentChar() == ';') {
      createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
    if (_scanner.currentChar() == ',') {
      createTerm();
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    if (_scanner.currentChar() == '.') {
      std::stringstream ss;
      string s;
      char c = _currentToken;
      ss << c; 
      ss >> s;
      throw string("Unexpected '" +  s + "' before '.'");
    }
    Term * left = createTerm();

    

    if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      _expStack.push(new MatchExp(left, right));
    }
    else if (_currentToken == '.') {
      throw string(left->symbol() + " does never get assignment"); 
    }
    else {
      std::stringstream ss;
      string s;
      char c = _currentToken;
      ss << c; 
      ss >> s;
      throw string("Unexpected '" +  s + "' before '.'");
  
    }
  
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }

  string result(){
    Exp* root = _expStack.top();
    if(_expStack.top()->evaluate() == false)
      return "false.";
    else{
      Variable *var = dynamic_cast<Variable*>(root->_left);
      std::cout << var << "\n";
      if(var){
        Term *term = dynamic_cast<Term*>(root->_right);
        std::cout << var->symbol() << "\n";
        rel = var->symbol() + " = " + term->symbol();
      
      // while(!dynamic_cast<MatchExp*>(root->_right)){
      //   root = root->_right ;
      }
      return rel;
    }
    return ".";
    
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  FRIEND_TEST(ParserTest, createTerms);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  std::string rel = "";
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  //MatchExp* _root;
  stack<Exp*> _expStack;
};
#endif
