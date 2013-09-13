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

TEST(Collatz, read_1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);
}

TEST(Collatz, read_2) {
    std::istringstream r("1 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 1);
}

TEST(Collatz, read_3) {
    std::istringstream r("100 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
}

/*
 * cycle_length
 *
 */
TEST(Collatz, cycle_length_1) {
    int n = 1;
    const int c = collatz_cycle_length(n);
    ASSERT_TRUE(c == 1);
}
TEST(Collatz, cycle_length_2) {
    int n = 10;
    const int c = collatz_cycle_length(n);
    ASSERT_TRUE(c == 7);
}
TEST(Collatz, cycle_length_4) {
    int n = 20;
    const int c = collatz_cycle_length(n);
    ASSERT_TRUE(c == 8);
}
TEST(Collatz, cycle_length_3) {
    int n = 1000;
    const int c = collatz_cycle_length(n);
    ASSERT_TRUE(c == 112);
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
    const int v = collatz_eval(100000, 1);
    ASSERT_TRUE(v == 351);
}
TEST(Collatz, eval_6) {
    const int v = collatz_eval(100000, 100000);
    ASSERT_TRUE(v == 129);
}
TEST(Collatz, eval_7) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);
}
TEST(Collatz, eval_8) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);
}
TEST(Collatz, eval_9) {
    const int v = collatz_eval(200, 100);
    ASSERT_TRUE(v == 125);
}
// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");
}
TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");
}
TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 1000000, 1000000, 129);
    ASSERT_TRUE(w.str() == "1000000 1000000 129\n");
}

// -----
// solve
// -----

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
}
TEST(Collatz, solve_2) {
    std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");
}
TEST(Collatz, solve_3) {
    std::istringstream r("289384 930887\n692778 636916\n747794 238336\n885387 760493\n516650 641422\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "289384 930887 476\n692778 636916 442\n747794 238336 470\n885387 760493 468\n516650 641422 452\n");
}


