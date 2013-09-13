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

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    //std::cout << "\n GOT: " << v << "EXPECTED: 20\n";
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    //std::cout << "\n GOT: " << v << "EXPECTED: 125\n";
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    //std::cout << "\n GOT: " << v << "EXPECTED: 89\n";
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    //std::cout << "\n GOT: " << v << "EXPECTED: 174\n";
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval_backwards1) {
    const int v = collatz_eval(1000, 900);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval_backwards2) {
    const int v = collatz_eval(210, 201);
    //std::cout << "\n GOT: " << v << "EXPECTED: 89\n";
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_backwards3) {
    const int v = collatz_eval(200, 100);
    //std::cout << "\n GOT: " << v << "EXPECTED: 89\n";
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_zero) {
    const int v = collatz_eval(0, 0);
    //std::cout << "\n GOT: " << v << "EXPECTED: 89\n";
    ASSERT_TRUE(v == 0);}

TEST(Collatz, eval_negative1) {
    const int v = collatz_eval(1, -1);
    //std::cout << "\n GOT: " << v << "EXPECTED: 89\n";
    ASSERT_TRUE(v == 0);}

TEST(Collatz, eval_negative2) {
    const int v = collatz_eval(-1, 1);
    //std::cout << "\n GOT: " << v << "EXPECTED: 89\n";
    ASSERT_TRUE(v == 0);}

TEST(Collatz, eval_1range) {
    const int v = collatz_eval(1, 1);
    //std::cout << "\n GOT: " << v << "EXPECTED: 89\n";
    ASSERT_TRUE(v == 1);}


// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 10, 10, 10);
    ASSERT_TRUE(w.str() == "10 10 10\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 11, 11, 11);
    ASSERT_TRUE(w.str() == "11 11 11\n");}

TEST(Collatz, print4) {
    std::ostringstream w;
    collatz_print(w, 1, -1, 1);
    ASSERT_TRUE(w.str() == "1 -1 1\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_lownumbers) {
    std::istringstream r("1 2\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 2 2\n");}

TEST(Collatz, solve_zerorange) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

TEST(Collatz, solve_1_range_higher_nums) {
    std::istringstream r("100 101\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "100 101 26\n");}