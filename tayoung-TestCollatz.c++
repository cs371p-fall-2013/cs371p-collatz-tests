// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// Modified by Tyler A. Young
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

TEST(Collatz, read_1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read_2) {
    std::istringstream r("233 13025\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==  233);
    ASSERT_TRUE(j == 13025);}

TEST(Collatz, read_3) {
    std::istringstream r("19328 8003\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 19328);
    ASSERT_TRUE(j == 8003);}

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

TEST(Collatz, eval_5) {
    const int v = collatz_eval(2188, 7663);
    ASSERT_TRUE(v == 262);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(12353, 3901);
    ASSERT_TRUE(v == 268);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(4785, 7885);
    ASSERT_TRUE(v == 262);}

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 27392, 22207, 308);
    ASSERT_TRUE(w.str() == "27392 22207 308\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 5966, 964, 238);
    ASSERT_TRUE(w.str() == "5966 964 238\n");}

TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 19204, 21306, 274);
    ASSERT_TRUE(w.str() == "19204 21306 274\n");}

// -----
// solve
// -----

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("22739 20390\n20565 20095\n1100 32569\n29776 15425\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "22739 20390 269\n20565 20095 243\n1100 32569 308\n29776 15425 308\n");}

TEST(Collatz, solve_3) {
    std::istringstream r("3377 6872\n22612 11040\n30202 14760\n13962 31893\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "3377 6872 262\n22612 11040 279\n30202 14760 308\n13962 31893 308\n");}

TEST(Collatz, solve_4) {
    std::istringstream r("22773 6506\n30339 6856\n11754 21817\n9557 11455\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "22773 6506 279\n30339 6856 308\n11754 21817 279\n9557 11455 268\n");}
