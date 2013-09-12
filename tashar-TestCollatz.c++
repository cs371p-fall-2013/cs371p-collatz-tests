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
	
// Check for invalid negative numbers
TEST(Collatz, read_2) {
    std::istringstream r("-1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}
	
// Check for invalid negative numbers
TEST(Collatz, read_3) {
    std::istringstream r("1 -10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}
	
// Check for 0
TEST(Collatz, read_4) {
    std::istringstream r("0 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}
	
// Check for 0
TEST(Collatz, read_5) {
    std::istringstream r("10 0\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(200, 100);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}
	
TEST(Collatz, eval_5) {
    const int v = collatz_eval(200, 201);
    ASSERT_TRUE(v == 27);}
	
TEST(Collatz, eval_6) {
    const int v = collatz_eval(99, 9999);
    ASSERT_TRUE(v == 262);}
	
TEST(Collatz, eval_7) {
    const int v = collatz_eval(5, 6);
    ASSERT_TRUE(v == 9);}
	
TEST(Collatz, eval_8) {
    const int v = collatz_eval(10, 10);
    ASSERT_TRUE(v == 7);}

TEST(Collatz, eval_9) {
    const int v = collatz_eval(1, 999999);
    ASSERT_TRUE(v == 525);}
// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}
	
TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 900, 1000, 174);
    ASSERT_TRUE(w.str() == "900 1000 174\n");}
	
TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 45, 50, 104);
    ASSERT_TRUE(w.str() == "45 50 104\n");}
	
TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");}


// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

//reversed	
TEST(Collatz, solve_2) {
    std::istringstream r("10 1\n20 10\n210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n20 10 21\n210 201 89\n1000 900 174\n");}
	
//single line
TEST(Collatz, solve_3){
    std::istringstream r("40 50\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "40 50 110\n");}
    
//variety of possible failure conditions on each line
TEST(Collatz, solve_4) {
    std::istringstream r("434 343\n400 400\n27 72\n1 1\n210 201\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "434 343 134\n400 400 28\n27 72 113\n1 1 1\n210 201 89\n");}
