#ifndef UTVARIABLE_H
#define UTVARIABLE_H

#include "variable.h"
#include "number.h"
#include "atom.h"
#include "struct.h"



TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X.value());
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

TEST(Variable , atom_to_varX){
  
  Atom tom("tom");
  Variable X("X");
  ASSERT_TRUE(tom.match(X));
  
}


TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182 !!!!
TEST(Variable , numE_to_varX){
  
  Variable X("X");
  Number e(2.7182);
  
  ASSERT_TRUE(e.match(X));
  
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Number first(1);
  X.match(Y);
  X.match(first);
  ASSERT_EQ( Y.value(), "1");
}
  
// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
  Variable X("X");
  Variable Y("Y");
  Number first(1);
  X.match(Y);
  Y.match(first);
  ASSERT_EQ(X.value(), "1");
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
  Variable X("X");
  Number first(1);
  X.match(X);
  
  ASSERT_TRUE(X.match(first));
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
  Variable X("X");
  Variable Y("Y");
  Number first(1);
  Y.match(first);
  ASSERT_TRUE(X.match(first));


}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
  
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number first(1);
  X.match(Y);
  Y.match(Z);
  Z.match(first);
  EXPECT_EQ(X.value(), "1");
  EXPECT_EQ(Y.value(), "1");
  EXPECT_EQ(Z.value(), "1");
  
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
  
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number first(1);
  X.match(Y);
  X.match(Z);
  Z.match(first);
  EXPECT_EQ(X.value(), "1");
  EXPECT_EQ(Y.value(), "1");
  EXPECT_EQ(Z.value(), "1");
  
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {

  Atom s("s");
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct hobby(s, v);
  Variable Y("Y");
  Y.match(hobby);
  ASSERT_EQ("s(X)",Y.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {

  Atom s("s");
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct hobby(s, v);
  
  Variable Y("Y");
  Atom teddy("teddy");
  X.match(teddy);

  Y.match(hobby);

  ASSERT_EQ("s(teddy)",Y.value());
  
}

#endif