#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {

  List l;
  EXPECT_EQ("[]", l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {

  Number num(8128);
  Number num1(496);
  
  vector<Term *> args = {&num, &num1};
  List l(args);

  EXPECT_EQ("[8128, 496]", l.symbol());
  
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom t("terence_tao");
  Atom a("alan_mathison_turing");
  vector<Term *> args = {&t, &a};
  List l(args);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  vector<Term *> args = {&X, &Y};
  List l(args);
  EXPECT_EQ("[X, Y]", l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  
  Atom tom("tom");
  Number num(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&num, &X, &t};
  List l(args);
  EXPECT_FALSE(tom.match(l));
  
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number num1(8128);
  Number num(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&num, &X, &t};
  List l(args);
  EXPECT_FALSE(num1.match(l));

}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Number num1(8128);
  Number num(496);
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Atom t("terence_tao");
  vector<Term *> args = {&num, &X, &t};
  List l(args);
  EXPECT_FALSE(s.match(l));

}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {

  Variable Y("Y");

  Number num(496);
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Atom t("terence_tao");
  vector<Term *> args = {&num, &X, &t};
  List l(args);
  EXPECT_TRUE(Y.match(l));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  
  Number num(496);
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Atom t("terence_tao");
  vector<Term *> args = {&num, &X, &t};
  List l(args);
  EXPECT_FALSE(X.match(l));
  
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number num(496);
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Atom t("terence_tao");
  vector<Term *> args = {&num, &X, &t};
  List l(args);
  EXPECT_TRUE(l.match(l));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {

  Number num(496);
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Atom t("terence_tao");
  vector<Term *> args = {&num, &X, &t};
  vector<Term *> args1 = {&num, &Y, &t};
  List l(args);
  List l1(args1);
  EXPECT_TRUE(l1.match(l));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.error
TEST(List, matchToVarToAtominListShouldSucceed) {

  Number num(496);
  Variable X("X");
  Number num1(8128);
  Atom t("terence_tao");
  vector<Term *> args = {&num, &X, &t};
  vector<Term *> args1 = {&num, &num1, &t};
  List l(args);
  List l1(args1);
  EXPECT_TRUE(l1.match(l));
  EXPECT_EQ("8128",X.value());
  
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Number num(496);
  Variable X("X");
  Variable Y("Y");
  Atom t("terence_tao");
  Atom t1("alan_mathison_turing");
  vector<Term *> args = {&num, &X, &t};
  List l(args);
  Y.match(l);
  X.match(t1);
  EXPECT_EQ(Y.value(), "[496, alan_mathison_turing, terence_tao]");
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {

  Atom f("first");
  Atom s("second");
  Atom t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ("first", l.head()->symbol());
  EXPECT_EQ("[second, third]", l.tail()->value());
  
}


// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  
  Atom f("first");
  Atom s("second");
  Atom t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
  
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first");
  vector<Term *> args1 = {&f};
  List l1(args1);


  Atom s("second");
  Atom t("third");
  vector<Term *> args = {&l1, &s, &t};
  List l(args);

  EXPECT_EQ(string("[first]"), l.head()->value());

  EXPECT_EQ(string("[second, third]"), l.tail()->value());
  
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first");
  Atom s("second");
  Atom t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ("third", l.tail()->tail()->head()->value());
  EXPECT_EQ("[]", l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  vector<Term *> args = {};
  List l(args);
  //l.head()->value();
  //EXPECT_THROW(l.head()->value(), "Accessing head in an empty list");
  //l.head()->value();
  /*
  try
  {
    l.head()->value();
  }
  catch( std::out_of_range const & err )
  {
    // check exception
    ASSERT_EQ( "Accessing head in an empty list", err.what() );
  }
  */
  //EXPECT_EQ(string("Accessing head in an empty list"), l.head()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  Atom f("first");
  Atom s("second");
  Atom t("third");
  vector<Term *> args = {};
  List l(args);
  //EXPECT_THROW(l.tail()->value(), "Accessing tail in an empty list");
  /*
  try
  {
    l.tail()->value();
  }
  catch( std::out_of_range const & err )
  {
    // check exception
    ASSERT_EQ( "Accessing tail in an empty list", err.what() );
  }
  */
  
}
#endif