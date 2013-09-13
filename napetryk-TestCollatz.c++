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
    ASSERT_TRUE(j ==   10);}
TEST(Collatz, read_2) {
    std::istringstream r("5 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    5);
    ASSERT_TRUE(j ==    1);}
TEST(Collatz, read_3) {
    std::istringstream r("100000 999999\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 100000);
    ASSERT_TRUE(j == 999999);}

// ----
// eval
// ----


TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);
    const int v_rev = collatz_eval(10, 1);
    ASSERT_TRUE(v_rev == 20);
}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);
    const int v_rev = collatz_eval(200, 100);
    ASSERT_TRUE(v_rev == 125);
}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);
    const int v_rev = collatz_eval(210, 201);
    ASSERT_TRUE(v_rev == 89);
}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);
    const int v_rev = collatz_eval(1000, 900);
    ASSERT_TRUE(v_rev == 174);
}

TEST(Collatz, acceptance_fail_630527) {
    // these overflow 32bits and should thus fail
    const int v = collatz_eval(630527, 630528);
    ASSERT_TRUE(v != 240);
}

TEST(Collatz, acceptance_fail_810814) {
    // these overflow 32bits and should thus fail
    const int v = collatz_eval(810814, 810815);
    ASSERT_TRUE(v != 406);
}

// ----
// cache_value & cached_value
// ----

TEST(Collatz, cache_value_good) {
    cache_value(999999, 10);
    ASSERT_TRUE(cached_value(999999) == 10);
}

TEST(Collatz, cache_value_bad) {
    ASSERT_TRUE(cached_value(999998) == 0);
}

TEST(Collatz, cache_value_invalid) {
    cache_value(1000000, 1);
    ASSERT_TRUE(cached_value(1000000) == 0);
}

// ----
// eval_one
// ----

TEST(Collatz, eval_one_amilli) {
    const int v = collatz_eval_one(1000000);
    ASSERT_TRUE(v == 153);}

TEST(Collatz, eval_one_one) {
    const int v = collatz_eval_one(1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_one_500k) {
    const int v = collatz_eval_one(500000);
    ASSERT_TRUE(v == 152);}

// ----
// optimize_range
// ----

TEST(Collatz, hi_lo_to_lo_hi_1) {
  int i = 2, j = 1;
  collatz_optimize_range(i, j);
  ASSERT_TRUE(i == 1);
  ASSERT_TRUE(j == 2);
}

TEST(Collatz, removes_lower_portion_and_reverses) {
  int i = 1, j = 10;
  collatz_optimize_range(i, j);
  ASSERT_TRUE(i == 5);
  ASSERT_TRUE(j == 10);
}

TEST(Collatz, removes_lower_portion) {
  int i = 10, j = 1;
  collatz_optimize_range(i, j);
  ASSERT_TRUE(i == 5);
  ASSERT_TRUE(j == 10);
}

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 999, 999, 99999);
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "999 999 99999\n1 1 1\n");}

TEST(Collatz, print_3) {
    // dumb
    std::ostringstream w;
    ASSERT_TRUE(w.str() == "");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
