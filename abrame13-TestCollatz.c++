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
    std::istringstream r("27 123\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 27);
    ASSERT_TRUE(j == 123);}

TEST(Collatz, read_3) {
    std::istringstream r("5555 6666\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 5555);
    ASSERT_TRUE(j == 6666);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10, false);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(1000, 2000, false);
    ASSERT_TRUE(v == 182);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(12345, 123456, false);
    ASSERT_TRUE(v == 354);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(1, 999999, false);
    ASSERT_TRUE(v == 525);}

TEST(Collatz, eval_5) {
    const int v = collatz_eval(10, 10, false);
    ASSERT_TRUE(v == 7);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(100, 1, false);
    ASSERT_TRUE(v == 119);}

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 1000, 2000, 182);
    ASSERT_TRUE(w.str() == "1000 2000 182\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 12345, 123456, 354);
    ASSERT_TRUE(w.str() == "12345 123456 354\n");}

TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 1, 999999, 525);
    ASSERT_TRUE(w.str() == "1 999999 525\n");}

TEST(Collatz, print_5) {
    std::ostringstream w;
    collatz_print(w, 10, 10, 7);
    ASSERT_TRUE(w.str() == "10 10 7\n");}

TEST(Collatz, print_6) {
    std::ostringstream w;
    collatz_print(w, 100, 1, 119);
    ASSERT_TRUE(w.str() == "100 1 119\n");}

// -----
// solve
// -----

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("1000 2000\n150 250\n111 333\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1000 2000 182\n150 250 128\n111 333 144\n");}

TEST(Collatz, solve_3) {
    std::istringstream r("12345 123456\n1 999999\n10 10\n100 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "12345 123456 354\n1 999999 525\n10 10 7\n100 1 119\n");}
    
// ------
// length
// ------

TEST(Collatz, length_1) {
    int len = collatz_length(5);
    ASSERT_TRUE(len == 6);}

TEST(Collatz, length_2) {
    int len = collatz_length(999999);
    ASSERT_TRUE(len == 259);}

TEST(Collatz, length_3) {
    int len = collatz_length(100);
    ASSERT_TRUE(len == 26);}

TEST(Collatz, length_4) {
    int len = collatz_length(12345);
    ASSERT_TRUE(len == 51);}

TEST(Collatz, length_5) {
    int len = collatz_length(10);
    ASSERT_TRUE(len == 7);}

TEST(Collatz, length_6) {
    int len = collatz_length(20);
    ASSERT_TRUE(len == 8);}
    
// ------
// max_length
// ------

TEST(Collatz, max_length_1) {
    int len = collatz_max_length(10, 10, false);
    ASSERT_TRUE(len == 7);}

TEST(Collatz, max_length_2) {
    int len = collatz_max_length(20, 20, false);
    ASSERT_TRUE(len == 8);}

TEST(Collatz, max_length_3) {
    int len = collatz_max_length(1, 20, false);
    ASSERT_TRUE(len == 21);}

TEST(Collatz, max_length_4) {
    int len = collatz_max_length(1, 999999, false);
    ASSERT_TRUE(len == 525);}

TEST(Collatz, max_length_5) {
    int len = collatz_max_length(1000, 10000, false);
    ASSERT_TRUE(len == 262);}

TEST(Collatz, max_length_6) {
    int len = collatz_max_length(50, 250, false);
    ASSERT_TRUE(len == 128);}