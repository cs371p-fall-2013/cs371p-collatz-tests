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

TEST(Collatz, read_reverse_order) {
	std::istringstream r("10 1\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 10);
	ASSERT_TRUE(j == 1);}

TEST(Collatz, read_large_values) {
	std::istringstream r("490320943 548549343\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 490320943);
	ASSERT_TRUE(j == 548549343);}

TEST(Collatz, read_multiple) {
	std::istringstream r("1 1\n2 2\n");
	int i, j;
	bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 1 && j == 1);
	b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 2 && j == 2);}

// ------------
// cycle_length
// ------------

TEST(Collatz, cycle_length) {
	const int l = collatz_cycle_length(1);
	ASSERT_TRUE(l == 1);}

TEST(Collatz, cycle_length_2) {
	const int l = collatz_cycle_length(22);
	ASSERT_TRUE(l == 16);}

TEST(Collatz, cycle_length_3) {
	const int l = collatz_cycle_length(8);
	ASSERT_TRUE(l == 4);}

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

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_multiple) {
	std::ostringstream w;
	collatz_print(w, 1, 10, 20);
	collatz_print(w, 1, 2, 1);
	ASSERT_TRUE(w.str() == "1 10 20\n1 2 1\n");}

TEST(Collatz, print_large) {
	std::ostringstream w;
	collatz_print(w, 490320943, 548549343, 548549343);
	ASSERT_TRUE(w.str() == "490320943 548549343 548549343\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_reverse_input) {
	std::istringstream r("10 1\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "10 1 20\n");}

TEST(Collatz, solve_same_enpoints) {
	std::istringstream r("1 1\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "1 1 1\n");}
