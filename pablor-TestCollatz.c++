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


TEST(Collatz, read_reverse) {
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   10);
    ASSERT_TRUE(j ==   1);}

TEST(Collatz, read_equal) {
    std::istringstream r("3 3\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   3);
    ASSERT_TRUE(j ==   3);}

TEST(Collatz, read_high) {
    std::istringstream r("50000 50000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   50000);
    ASSERT_TRUE(j ==   50000);}


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
    const int v = collatz_eval(1, 3);
    ASSERT_TRUE(v == 8);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(1, 3);
    ASSERT_TRUE(v == 8);}




// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}


TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 3, 3, 8);
    ASSERT_TRUE(w.str() == "3 3 8\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 1, -1, 300);
    ASSERT_TRUE(w.str() == "1 -1 300\n");}    

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_small) {
    std::istringstream r("1 3\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 3 8\n");}


TEST(Collatz, solve_medium) {
    std::istringstream r("100 101\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "100 101 26\n");}

TEST(Collatz, solve_empty) {
    std::istringstream r("");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "");}





