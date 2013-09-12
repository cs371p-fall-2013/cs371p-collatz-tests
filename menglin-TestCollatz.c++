// --------------------------------
// Project by: Mitch Stephan
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

TEST(Collatz, read_1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read_2) {
    std::istringstream r("2 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 2);
    ASSERT_TRUE(j == 1);}

TEST(Collatz, read_3) {
    std::istringstream r("1000 10000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1000);
    ASSERT_TRUE(j == 10000);}

TEST(Collatz, read_4) {
    std::istringstream r("\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}

TEST(CollatzRead, initialTEst) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 10);}

TEST(CollatzRead, switchedInput) {
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 10);
    ASSERT_TRUE(j == 1);}
TEST(CollatzRead, sameInput) {
    std::istringstream r("5 5\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 5);
    ASSERT_TRUE(j == 5);
    ASSERT_TRUE(i == j);}
TEST(CollatzRead, biggerInput) {
    std::istringstream r("5000 10000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 5000);
    ASSERT_TRUE(j == 10000);
    }

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
    const int v = collatz_eval(63, 162);
    ASSERT_TRUE(v == 122);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(66, 226);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(16, 150);
    ASSERT_TRUE(v == 122);}


// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 2, 12, 200);
    ASSERT_TRUE(w.str() == "2 12 200\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 10, 100, 200);
    ASSERT_TRUE(w.str() == "10 100 200\n");}

TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 5, 50, 52);
    ASSERT_TRUE(w.str() == "5 50 52\n");}

TEST(Collatzprint, defaultprint) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatzprint, simpleprint) {
    std::ostringstream w;
    collatz_print(w, 1, 2, 3);
    ASSERT_TRUE(w.str() == "1 2 3\n");}

TEST(Collatzprint, reversedSimpleprint) {
    std::ostringstream w;
    collatz_print(w, 3, 2, 1);
    ASSERT_TRUE(w.str() == "3 2 1\n");}

TEST(Collatzprint, bigNumbers) {
    std::ostringstream w;
    collatz_print(w, 12345, 98765, 43210);
    ASSERT_TRUE(w.str() == "12345 98765 43210\n");}

// -----
// solve
// -----

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("1 10\n100 200\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n");}

TEST(Collatz, solve_3) {
    std::istringstream r("201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_4) {
    std::istringstream r("16 150\n169 154\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "16 150 122\n169 154 112\n");}

TEST(Collatz, solve_5) {
    std::istringstream r("3 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "3 10 20\n");}

TEST(Collatz, solve_6) {
    std::istringstream r("8239 2971\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "8239 2971 262\n");}
    
TEST(Collatz, solve_7) {
    std::istringstream r("7639 11696\n3427 1280\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "7639 11696 268\n3427 1280 217\n");}
