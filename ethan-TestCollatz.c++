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

TEST(CollatzRead, SimpleIn) {
    std::istringstream input_stream("1 10\n");
    int first;
    int second;
    const bool read_success = collatz_read(input_stream, first, second);

    ASSERT_TRUE(read_success == true);
    ASSERT_TRUE(first ==    1);
    ASSERT_TRUE(second ==   10);}

TEST(CollatzRead, SameIn) {
    std::istringstream input_stream("1 1\n");
    int first;
    int second;
    const bool read_success = collatz_read(input_stream, first, second);

    ASSERT_TRUE(read_success);
    ASSERT_TRUE(1 == first);
    ASSERT_TRUE(1 == second);
    ASSERT_TRUE(first == second);}

TEST(CollatzRead, SpaceIn) {
    std::istringstream input_stream("\n \n \n \n 1 \n \n 10 \n \n \n");
    int first;
    int second;
    const bool read_success = collatz_read(input_stream, first, second);

    ASSERT_TRUE(read_success);
    ASSERT_TRUE(first == 1);
    ASSERT_TRUE(second == 10);}

TEST(CollatzRead, NoIn) {
    std::istringstream input_stream("\n");
    int first;
    int second;
    const bool read_success = collatz_read(input_stream, first, second);

    ASSERT_TRUE(read_success == false);}


// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int max_cycles = collatz_eval(1, 10);
    ASSERT_TRUE(max_cycles == 20);}

TEST(Collatz, eval_2) {
    const int max_cycles = collatz_eval(100, 200);
    ASSERT_TRUE(max_cycles == 125);}

TEST(Collatz, eval_3) {
    const int max_cycles = collatz_eval(201, 210);
    ASSERT_TRUE(max_cycles == 89);}

TEST(Collatz, eval_4) {
    const int max_cycles = collatz_eval(900, 1000);
    ASSERT_TRUE(max_cycles == 174);}

TEST(Collatz, eval_lowbound) {
    const int max_cycles = collatz_eval(1, 1);
    ASSERT_TRUE(max_cycles == 1);}

TEST(Collatz, eval_highbound) {
    const int max_cycles = collatz_eval(999999, 999999);
    ASSERT_TRUE(max_cycles == 259);}


// -----
// print
// -----

TEST(Collatz, print_basic) {
    std::ostringstream output_stream;
    collatz_print(output_stream, 1, 10, 20);
    ASSERT_TRUE(output_stream.str() == "1 10 20\n");}

TEST(Collatz, print_lowbound) {
    std::ostringstream output_stream;
    collatz_print(output_stream, 1, 1, 1);
    ASSERT_TRUE(output_stream.str() == "1 1 1\n");}

TEST(Collatz, print_highbound) {
    std::ostringstream output_stream;
    collatz_print(output_stream, 999999, 999999, 259);
    ASSERT_TRUE(output_stream.str() == "999999 999999 259\n");}

TEST(Collatzprint, bigNumbers) {
    std::ostringstream w;
    collatz_print(w, 12345, 98765, 43210);
    ASSERT_TRUE(w.str() == "12345 98765 43210\n");}

// -----
// solve
// -----

TEST(Collatz, solve_basic) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}


TEST(Collatz, solve_empty) {
    std::istringstream r("");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "");}

TEST(Collatz, solve_single) {
    std::istringstream r("27 27\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "27 27 112\n");}
