#ifndef UTTERM_H
#define UTTERM_H

#include "number.h"
#include "atom.h"
#include "variable.h"

//test Number.value()
TEST (Number,ctor) {
    Number first(6);
    ASSERT_EQ(first.value(), "6");
}
//test Number.symbol()
TEST (Number, symbol) {
    Number first(5);
    EXPECT_EQ(first.symbol(), "Number");
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number first(25);
    EXPECT_TRUE(first.match(25));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number first(25);
    EXPECT_FALSE(first.match(0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number first(25);
    Atom tom("tom");
    EXPECT_FALSE(first.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number first(25);
    Variable X("X");
    EXPECT_TRUE(first.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom tom("tom");
    Number first(25);
    EXPECT_FALSE(tom.match(first));

}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom tom("tom");
    Variable X("X");
    tom.match(X);
    ASSERT_EQ(X.value(), "tom");
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {

    Atom tom("tom");
    Variable X("X");
    X.match(tom);
    tom.match(X);

    ASSERT_EQ(X.value(), "tom");
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Atom jerry("jerry");
    Variable X("X");
    EXPECT_TRUE(jerry.match(X));
    Atom tom("tom");
    EXPECT_FALSE(jerry.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
     Variable X("X");
     Number five(5);
     EXPECT_TRUE(X.match(five));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
  Variable X("X");
  Number five(5);
  EXPECT_TRUE(X.match(five));
  Number sec(100);
  EXPECT_FALSE(X.match(sec));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
  Variable X("X");
  Atom tom("tom");
  X.match(tom);
  Number first(25);

  EXPECT_FALSE(X.match(first));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
  Atom tom("tom");
  Variable X("X");
  tom.match(X);
  Number first(25);
  EXPECT_FALSE(first.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
  Variable X("X");
  Atom tom("tom");
  X.match(tom);
  X.match(tom);
  ASSERT_EQ(X.value(), "tom");
}
#endif
