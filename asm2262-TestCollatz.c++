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
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

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
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read_2) {
   std::istringstream r("20 40\n");
   int i;
   int j;
   const bool b = collatz_read(r, i, j);
   ASSERT_TRUE(b == true);
   ASSERT_TRUE(i == 20);
   ASSERT_TRUE(j == 40);}

TEST(Collatz, read_3){
   std::istringstream r("100 50\n");
   int i;
   int j;
   const bool b = collatz_read(r, i, j);
   ASSERT_TRUE(b == true);
   ASSERT_TRUE(i == 100);
   ASSERT_TRUE(j == 50);}


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

TEST(Collatz, eval_5) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(76, 50);
    ASSERT_TRUE(v == 116);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(99, 9999);
    ASSERT_TRUE(v == 262);}



// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 9999, 99, 262);
    ASSERT_TRUE(w.str() == "9999 99 262\n");}


TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 10, 50, 112);
    ASSERT_TRUE(w.str() == "10 50 112\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("20 30\n40 30\n78 99\n1000 1818\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "20 30 112\n40 30 107\n78 99 119\n1000 1818 182\n");}



TEST(Collatz, solve_3) {
    std::istringstream r("9999 99999\n175 904\n8000 9000\n867 2\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "9999 99999 351\n175 904 179\n8000 9000 247\n867 2 171\n");}






