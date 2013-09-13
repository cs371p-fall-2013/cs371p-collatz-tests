// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Kevin Tran
// CS371p Fall 2013
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

TEST(Collatz, read1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(1, i);
    ASSERT_EQ(10, j);}


TEST(Collatz, read2) {
	std::istringstream r("3 1");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b);
	ASSERT_EQ(3, i);
	ASSERT_EQ(1, j);
	}

TEST(Collatz, read3) {
	std::istringstream r("10 1000000\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b);
	ASSERT_EQ(10, i);
	ASSERT_EQ(1000000, j);
	}

TEST(Collatz, read4) {
	std::istringstream r("");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	ASSERT_FALSE(b);
	}


// ----
// eval
// ----

TEST(Collatz, eval1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(Collatz, eval2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(Collatz, eval3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(Collatz, eval4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

TEST(Collatz, eval5) {
    const int v = collatz_eval(1,1);
    ASSERT_EQ(1, v);}

TEST(Collatz, eval6) {
    const int v = collatz_eval(1,3);
    ASSERT_EQ(8, v);}

TEST(Collatz, eval7) {
    const int v = collatz_eval(1,9);
    ASSERT_EQ(20, v);}


// -----
// print
// -----

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str() );}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 1, 3000, 3);
    ASSERT_EQ("1 3000 3\n", w.str() );}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 10, 1, 10);
    ASSERT_EQ("10 1 10\n", w.str() );}

TEST(Collatz, print4) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_EQ("1 1 1\n", w.str() );}


// -----
// solve
// -----

TEST(Collatz, solve1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str() );}

TEST(Collatz, solve2) {
    std::istringstream r("3 3\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("3 3 8\n", w.str() );}

TEST(Collatz, solve3) {
    std::istringstream r("1 1\n1 1\n1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n1 1 1\n1 1 1\n", w.str() );}

TEST(Collatz, solve4) {
    std::istringstream r("1 9\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 9 20\n", w.str() );}

