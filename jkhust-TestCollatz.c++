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

TEST(Collatz, read_1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 10);}

TEST(Collatz, read_2) {
    std::istringstream r("99 5\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 99);
    ASSERT_TRUE(j == 5);}
    
TEST(Collatz, read_3) {
    std::istringstream r("1 144\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 144);}

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

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 0, 1, 2);
    ASSERT_TRUE(w.str() == "0 1 2\n");}
    
TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 10, 2, 5);
    ASSERT_TRUE(w.str() == "10 2 5\n");}


// -----
// solve
// -----
/* Collatz cycles used for testing found here:
  http://csw373.wordpress.com/2013/06/09/list-of-collatz-cycles/
*/

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("108 199\n8009 9541\n6671 8681\n150 1816\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "108 199 125\n8009 9541 260\n6671 8681 257\n150 1816 182\n");}
    
TEST(Collatz, solve_3) {
    std::istringstream r("870 4350\n7422 8196\n633 2022\n620 4474\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "870 4350 238\n7422 8196 252\n633 2022 182\n620 4474 238\n");}