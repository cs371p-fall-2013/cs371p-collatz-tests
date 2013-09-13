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

TEST(Collatz, read_small_input) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}
	
	TEST(Collatz, read_same_input) {
    std::istringstream r("2 2\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    2);
    ASSERT_TRUE(j ==   2);}
	
	TEST(Collatz, read_double_input) {
    std::istringstream r("60 5\n12 9\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    60);
    ASSERT_TRUE(j ==   5);
	const bool c = collatz_read(r, i, j);
	ASSERT_TRUE(c == true);
    ASSERT_TRUE(i ==    12);
    ASSERT_TRUE(j ==   9);}
	
TEST(Collatz, read_max_input) {
    std::istringstream r("999999 999999\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    999999);
    ASSERT_TRUE(j ==   999999);}
	
TEST(Collatz, read_no_input) {
    std::istringstream r("\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}
	
TEST(Collatz, read_backwards_input) {
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    10);
    ASSERT_TRUE(j ==   1);}

// ----
// eval
// ----

TEST(Collatz, eval_tiny_input) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_small_input) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_medium_input) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_larger_input) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval_backwards_input) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);}
	
TEST(Collatz, eval_same_input) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}
	
TEST(Collatz, eval_max_input) {
    const int v = collatz_eval(999999, 999999);
    ASSERT_TRUE(v == 259);}	
	
TEST(Collatz, eval_big_backwards_input) {
    const int v = collatz_eval(1000, 900);
    ASSERT_TRUE(v == 174);}

// ----
// eval_single
// ----

TEST(Collatz, eval_single_min) {
    const int v = collatz_eval_single(1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_single_even) {
    const int v = collatz_eval_single(10);
    ASSERT_TRUE(v == 7);}
	
TEST(Collatz, eval_single_odd) {
    const int v = collatz_eval_single(11);
    ASSERT_TRUE(v == 15);}

TEST(Collatz, eval_single_higher) {
    const int v = collatz_eval_single(4567);
    ASSERT_TRUE(v == 60);}
	
TEST(Collatz, eval_single_max) {
    const int v = collatz_eval_single(999999);
    ASSERT_TRUE(v == 259);}
	
// -----
// print
// -----

TEST(Collatz, print_normal_output) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_same_output) {
    std::ostringstream w;
    collatz_print(w, 10, 10, 10);
    ASSERT_TRUE(w.str() == "10 10 10\n");}
	
TEST(Collatz, print_bigger_output) {
    std::ostringstream w;
    collatz_print(w, 100, 3, 55);
    ASSERT_TRUE(w.str() == "100 3 55\n");}
	
TEST(Collatz, print_max_output) {
    std::ostringstream w;
    collatz_print(w, 999999, 999999, 999999);
    ASSERT_TRUE(w.str() == "999999 999999 999999\n");}
	
// -----
// solve
// -----

TEST(Collatz, solve_normal) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
	
	TEST(Collatz, solve_small) {
    std::istringstream r("1 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n");}
	
	TEST(Collatz, solve_different_order) {
    std::istringstream r("900 1000\n1 10\n100 200\n201 210\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "900 1000 174\n1 10 20\n100 200 125\n201 210 89\n");}
	
	TEST(Collatz, solve_min) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

TEST(Collatz, solve_max) {
    std::istringstream r("999999 999999\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "999999 999999 259\n");}
	
TEST(Collatz, solve_backwards) {
    std::istringstream r("10 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n");}
	