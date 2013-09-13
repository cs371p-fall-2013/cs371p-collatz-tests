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
    ASSERT_TRUE(i ==     1);
    ASSERT_TRUE(j ==    10);
    }
    
TEST(Collatz, read_edge) {
	std::istringstream r("1 999999\n");
    int i;
    int j;
    const bool read_success = collatz_read(r, i, j);
    ASSERT_TRUE(read_success == true);
    ASSERT_TRUE(i ==     1);
    ASSERT_TRUE(j ==999999);
    }
    
TEST(Collatz, read_middle) {
	std::istringstream r("510 1200\n");
    int i;
    int j;
    const bool read_success = collatz_read(r, i, j);
    ASSERT_TRUE(read_success == true);
    ASSERT_TRUE(i ==   510);
    ASSERT_TRUE(j ==  1200);
    }
    
TEST(Collatz, read_identical) {
	std::istringstream r("3 3\n");
    int i;
    int j;
    const bool read_success = collatz_read(r, i, j);
    ASSERT_TRUE(read_success == true);
    ASSERT_TRUE(i ==   3);
    ASSERT_TRUE(j ==   3);
    }

// ----
// eval
// ----

TEST(Collatz, eval_default1) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);
    }

TEST(Collatz, eval_default2) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);
    }

TEST(Collatz, eval_default3) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);
    }

TEST(Collatz, eval_default4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);
    }
    
TEST(Collatz, eval_identical1) {
	const int v = collatz_eval(5, 5);
	ASSERT_TRUE(v == 6);
	}
	
TEST(Collatz, eval_identical2) {
	const int v = collatz_eval(3, 3);
	ASSERT_TRUE(v == 8);
	}
	
TEST(Collatz, eval_backwards) {
	const int v = collatz_eval(200, 100);
	ASSERT_TRUE(v == 125);
	}
	

// -----
// print
// -----

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}
    
TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_TRUE(w.str() == "100 200 125\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 3, 3, 8);
    ASSERT_TRUE(w.str() == "3 3 8\n");}

// -----
// solve
// -----

TEST(Collatz, solve_default) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
    
TEST(Collatz, solve_backwards) {
    std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");}
    
TEST(Collatz, solve_identicals) { 
    std::istringstream r("1 1\n3 3\n5 5\n32 32\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n3 3 8\n5 5 6\n32 32 6\n");}