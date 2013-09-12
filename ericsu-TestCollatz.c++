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

TEST(Collatz, read_same) {
	std::istringstream r("3 3\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 3);
	ASSERT_TRUE(j == 3);
}

TEST(Collatz, read_descending) {
	std::istringstream r("100 99\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 100);
	ASSERT_TRUE(j == 99);
}

TEST(Collatz, read_large) {
	std::istringstream r("65535 65536\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 65535);
	ASSERT_TRUE(j == 65536);
}

TEST(Collatz, read_oneone) {
	std::istringstream r("1 1\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 1);
	ASSERT_TRUE(j == 1);
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

TEST(Collatz, eval_large) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval_same_numbers) {
	const int v = collatz_eval(1, 1);
	ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_diff_of_one) {
	const int v = collatz_eval(1, 2);
	ASSERT_TRUE(v == 2);}

TEST(Collatz, eval_reverse) {
	const int v = collatz_eval(10, 1);
	ASSERT_TRUE(v == 20);}

// ----
// swap
// ----

TEST(Collatz, swap_typical) {
    int i = 10;
    int j = 1;
    collatz_swap(i, j);
    ASSERT_TRUE(i == 1 && j == 10);}

TEST(Collatz, swap_same_numbers) {
    int i = 1;
    int j = 1;
    collatz_swap(i, j);
    ASSERT_TRUE(i == 1 && j == 1);}

TEST(Collatz, swap_large_and_small) {
    int i = 99999;
    int j = 1;
    collatz_swap(i, j);
    ASSERT_TRUE(i == 1 && j == 99999);}

// ---------
// algorithm
// ---------

TEST(Collatz, algorithm_reverse) {
    int v = collatz_algorithm(10, 1);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, algorithm_same_numbers) {
    int v = collatz_algorithm(9, 9);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, algorithm_small_and_large) {
    int v = collatz_algorithm(1, 10000);
    ASSERT_TRUE(v == 262);}

// --------
// find_max
// --------

TEST(Collatz, find_max_same) {
    int v = collatz_find_max(1,1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, find_max_small_and_large) {
    int v = collatz_find_max(1,99999);
    ASSERT_TRUE(v == 99999);}

TEST(Collatz, find_max_large_and_small) {
    int v = collatz_find_max(99999, 1);
    ASSERT_TRUE(v == 99999);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_small) {
	std::ostringstream w;
	collatz_print(w, 10, 10, 10);
	ASSERT_TRUE(w.str() == "10 10 10\n");}

TEST(Collatz, print_large) {
	std::ostringstream w;
	collatz_print(w, 999999, 999999, 999999);
	ASSERT_TRUE(w.str() == "999999 999999 999999\n");}

TEST(Collatz, print_typical) {
	std::ostringstream w;
	collatz_print(w, 1, 2, 3);
	ASSERT_TRUE(w.str() == "1 2 3\n");}

// -----
// solve
// -----

TEST(Collatz, solve_typical) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
}

TEST(Collatz, solve_blank) {
    std::istringstream r("");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "");
}

TEST(Collatz, solve_same_numbers) {
    std::istringstream r("10 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 10 7\n");
}

TEST(Collatz, solve_several_same_numbers) {
    std::istringstream r("100 200\n100 200\n100 200\n100 200\n100 200\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "100 200 125\n100 200 125\n100 200 125\n100 200 125\n100 200 125\n");
}
