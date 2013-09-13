// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
% ls -al /usr/include/gtest/
...
gtest.h
...

% locate libgtest.a
/usr/lib/libgtest.a

% locate libpthread.a
/usr/lib/x86_64-linux-gnu/libpthread.a
/usr/lib32/libpthread.a

% locate libgtest_main.a
/usr/lib/libgtest_main.a

% g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

% valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(Collatz, read) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 10);}

TEST(Collatz, read1) {
    std::istringstream r("654 7563\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b ==true);
    ASSERT_TRUE(i == 654);
    ASSERT_TRUE(j == 7563);}

TEST(Collatz, read2) {
    std::istringstream r("99999 89756\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b ==true);
    ASSERT_TRUE(i == 99999);
    ASSERT_TRUE(j == 89756);}

TEST(Collatz, read3) {
    std::istringstream r("7562 789563\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b ==true);
    ASSERT_TRUE(i == 7562);
    ASSERT_TRUE(j == 789563);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval_5){
    const int v = collatz_eval(47853, 234);
    ASSERT_TRUE(v == 324);}

TEST(Collatz, eval_6){
   const int v = collatz_eval(5092,7918);
   ASSERT_TRUE(v == 262);}

TEST(Collatz, eval_7){
   const int v = collatz_eval(796, 3775);
   ASSERT_TRUE(v==238);}

TEST(Collatz, eval_8){
   const int v = collatz_eval(1932, 6543);
   ASSERT_TRUE(v==262);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 145450, 13455, 375);
    ASSERT_TRUE(w.str() == "145450 13455 375\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 50000, 326546, 443);
    ASSERT_TRUE(w.str() == "50000 326546 443\n");}

TEST(Collatz, print4) {
   std::ostringstream w;
   collatz_print(w, 56875, 54632, 322);
   ASSERT_TRUE(w.str() == "56875 54632 322\n");}



// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve2) {
    std::istringstream r("323 524\n");
    std::ostringstream w;
    collatz_solve(r,w);
    ASSERT_TRUE(w.str() == "323 524 144\n");}

TEST(Collatz, solve3) {
    std::istringstream r("50000 326546\n");
    std::ostringstream w;
    collatz_solve(r,w);
    ASSERT_TRUE(w.str() == "50000 326546 443\n");
}

TEST(Collatz, solve4) {
    std::istringstream r("1320 10\n145450 13455\n227642 294\n52236 325000\n");
    std::ostringstream w;
    collatz_solve(r,w);
    ASSERT_TRUE(w.str() == "1320 10 182\n145450 13455 375\n227642 294 386\n52236 325000 443\n");
}
