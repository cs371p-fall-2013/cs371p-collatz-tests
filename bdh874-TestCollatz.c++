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
    ASSERT_TRUE(collatz_read(r, i, j));
    ASSERT_EQ(1, i);
    ASSERT_EQ(10, j);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    ASSERT_EQ(20, collatz_eval(1, 10));}

TEST(Collatz, eval_2) {
    ASSERT_EQ(125, collatz_eval(100, 200));}

TEST(Collatz, eval_3) {
    ASSERT_EQ(89, collatz_eval(201, 210));}

TEST(Collatz, eval_4) {
    ASSERT_EQ(174, collatz_eval(900, 1000));}

TEST(Collatz, eval_5) {
    ASSERT_EQ(354, collatz_eval(53890, 108693));}

TEST(Collatz, eval_6) {
    ASSERT_EQ(351, collatz_eval(57820, 90336));}

TEST(Collatz, eval_7) {
    ASSERT_EQ(262, collatz_eval(2541, 6923));}

TEST(Collatz, eval_8) {
    ASSERT_EQ(396, collatz_eval(997824, 999166));}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

// ------------
// cycle_length
// ------------

TEST(Collatz, cycle_length_1) {
  ASSERT_EQ(37, collatz_cycle_length(971));
}

TEST(Collatz, cycle_length_2) {
  ASSERT_EQ(32, collatz_cycle_length(173));
}

TEST(Collatz, cycle_length_3) {
  ASSERT_EQ(93, collatz_cycle_length(549));
}

TEST(Collatz, cycle_length_4) {
  ASSERT_EQ(34, collatz_cycle_length(769));
}

TEST(Collatz, cycle_length_5) {
  ASSERT_EQ(1, collatz_cycle_length(1));
}

TEST(Collatz, cycle_length_6) {
  ASSERT_EQ(2, collatz_cycle_length(2));
}

TEST(Collatz, cycle_length_7) {
  ASSERT_EQ(259, collatz_cycle_length(999999));
}

TEST(Collatz, cycle_length_8) {
  ASSERT_EQ(6, collatz_cycle_length(32));
}

TEST(Collatz, cycle_length_9) {
  ASSERT_EQ(80, collatz_cycle_length(108693));
}
