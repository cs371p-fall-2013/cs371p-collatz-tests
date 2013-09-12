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

//tests reverse input
TEST(Collatz, rev_input) {
	std::istringstream r("10 1\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i ==   10);
	ASSERT_TRUE(j ==   1);}

//tests equal input
TEST(Collatz, equal_inputs) {
	std::istringstream r("1 1\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 1);
	ASSERT_TRUE(j == 1); }

//tests 1 - 1000000
TEST(Collatz, high_input){ 
	std::istringstream r("1 1000000\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 1);
	ASSERT_TRUE(j == 1000000);}

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

//tests extreme cases
TEST(Collatz, eval_upper) {
	const int v = collatz_eval(1, 999999);
	ASSERT_TRUE(v == 525);}

//tests reverse input in the extreme case
TEST(Collatz, rev_eval_upper) {
	const int v = collatz_eval(999999, 1);
	ASSERT_TRUE(v == 525);}

//test same input
TEST(Collatz, same_input) {
	const int v = collatz_eval(10, 10);
	ASSERT_TRUE(v == 7);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print2) {
	std::ostringstream w;
	collatz_print(w, 100, 200, 125);
	ASSERT_TRUE(w.str() == "100 200 125\n");}

TEST(Collatz, print3) {
	std::ostringstream w;
	collatz_print(w, 201, 210, 89);
	ASSERT_TRUE(w.str() == "201 210 89\n");}

TEST(Collatz, print4) {
	std::ostringstream w;
	collatz_print(w, 900, 1000, 174);
	ASSERT_TRUE(w.str() == "900 1000 174\n");}
//test lower and upper bound inputs
TEST(Collatz, upper_bound) {
	std::ostringstream w;
	collatz_print(w, 1, 999999, 525);
	ASSERT_TRUE(w.str() == "1 999999 525\n");}

//tests i > j for extreme cases
TEST(Collatz, rev_upper_bound) {
	std::ostringstream w;
	collatz_print(w, 999999, 1, 525);
	ASSERT_TRUE(w.str() == "999999 1 525\n");}

//tests if equal input correctly outputs
TEST(Collatz, equal_input) {
	std::ostringstream w;
	collatz_print(w, 10, 10, 7);
	ASSERT_TRUE(w.str() == "10 10 7\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

//tests to see if the reverse outputs correctly
TEST(Collatz, solve_reverse) {
    std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");}

//tests the extreme cases, lower bound through upper bound
TEST(Collatz, extreme_cases) {
	std::istringstream r("1 999999\n999999 1\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "1 999999 525\n999999 1 525\n");}

//tests empty
TEST(Collatz, empty) {
	std::istringstream r("");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "");}
