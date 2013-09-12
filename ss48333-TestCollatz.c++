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

TEST(Collatz, read_1) {
    std::istringstream r("\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);
}

TEST(Collatz, read_2) {
    std::istringstream r("1 100000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 100000);
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
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(1, 1000000);
    ASSERT_TRUE(v == 525);}


// ----
// collatz_alg
// ----

TEST(Collatz, alg_1) {
    const int c = collatz_alg(22);
    ASSERT_TRUE(c == 16);
}

TEST(Collatz, alg_2) {
    const int c = collatz_alg(1);
    ASSERT_TRUE(c == 1);
}
TEST (Collatz, alg_3) {
    const int c = collatz_alg(2);
    ASSERT_TRUE(c == 2);
}
TEST (Collatz, alg_4) {
    const int c = collatz_alg(1000000);
    ASSERT_TRUE(c == 153);
}


// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 0, 0, 0);
    ASSERT_TRUE(w.str() == "0 0 0\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}


TEST(Collatz, solve_1) {
    std::istringstream r("60126 44831\n9245 11910\n56419 99638\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "60126 44831 340\n9245 11910 268\n56419 99638 351\n");
}

TEST(Collatz, solve_2) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n");
}

TEST(Collatz, solve_3) {
    std::istringstream r("\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "");
}
