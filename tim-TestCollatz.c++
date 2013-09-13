//// --------------------------------
//// projects/collatz/TestCollatz.c++
//// Copyright (C) 2013
//// Glenn P. Downing
//// --------------------------------
//
///*
//To test the program:
//    % ls -al /usr/include/gtest/
//    ...
//    gtest.h
//    ...
//
//    % locate libgtest.a
//    /usr/lib/libgtest.a
//
//    % locate libpthread.a
//    /usr/lib/x86_64-linux-gnu/libpthread.a
//    /usr/lib32/libpthread.a
//
//    % locate libgtest_main.a
//    /usr/lib/libgtest_main.a
//
//    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main
//
//    % valgrind TestCollatz > TestCollatz.out
//*/
//
//// --------
//// includes
//// --------
//
//#include <iostream> // cout, endl
//#include <sstream>  // istringtstream, ostringstream
//#include <string>   // ==

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
    ASSERT_TRUE(b);
    ASSERT_EQ(1,  i);
    ASSERT_EQ(10, j);}

TEST(Collatz, read_empty){
    std::istringstream r("\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_FALSE(b);
}

TEST(Collatz, read_identical_input) {
    std::istringstream r("1 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 1);}

TEST(Collatz, read_line) {
    std::istringstream r("1 10 20\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(1,  i);
    ASSERT_EQ(10, j);}

TEST(Collatz, read_backwards) {
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(10,  i);
    ASSERT_EQ(1, j);}

TEST(Collatz, read_extremes) {
    std::istringstream r("1 999999\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 999999);}

// ----
// eval
// ----

TEST(Collatz, eval_reverse_input) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_identical) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}
    
TEST(Collatz, print_extremes) {
    std::ostringstream w;
    collatz_print(w, 1, 999999, 525);
    ASSERT_TRUE(w.str() == "1 999999 525\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("1 1\n210 201\n100 200\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n210 201 89\n100 200 125\n1000 900 174\n");}
    
TEST(Collatz, solve_3) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n");}
