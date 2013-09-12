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

TEST(Collatz, read_1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read_2){
    std::istringstream r("100 200\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    100);
    ASSERT_TRUE(j ==   200);} 
TEST(Collatz, read_3){
    std::istringstream r("201 210\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    201);
    ASSERT_TRUE(j ==   210);} 
TEST(Collatz, read_4){
    std::istringstream r("900 1000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    900);
    ASSERT_TRUE(j ==   1000);}
TEST(Collatz, read_5){
    std::istringstream r("1 2\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   2);} 
           



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
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(200, 201);
    ASSERT_TRUE(v == 27);}

TEST(Collatz, eval_8) {
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
    collatz_print(w, 1, 100, 300);
    ASSERT_TRUE(w.str() == "1 100 300\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 3, 2, 2);
    ASSERT_TRUE(w.str() == "3 2 2\n");}

TEST(Collatz, print_5){
    std::ostringstream w;
    collatz_print(w, 5, 5, 5);
    ASSERT_TRUE(w.str() == "5 5 5\n");
}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
TEST(Collatz, solve_2) {
    std::istringstream r("1 6\n500 250\n555 5583\n555 555\n12345 54321\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 6 9\n500 250 144\n555 5583 238\n555 555 31\n12345 54321 340\n");}
TEST(Collatz, solve_3) {
    std::istringstream r("54321 12345\n11111 55555\n98765 56789\n10000 50000\n3 300000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "54321 12345 340\n11111 55555 340\n98765 56789 351\n10000 50000 324\n3 300000 443\n");}    

//-----------
//cycleLength
//-----------
TEST(Collatz, collatzCycle){
    long v = 5;
    long a = collatzCycle(v);
    ASSERT_TRUE(a == 6);
}
TEST(Collatz, collatzCycle_2){
    long v = 55;
    long a = collatzCycle(v);
    ASSERT_TRUE(a == 113);
}
TEST(Collatz, collatzCycle_3){
    long v = 555;
    long a = collatzCycle(v);
    ASSERT_TRUE(a == 31);
}
TEST(Collatz, collatzCycle_4){
    long v = 8746;
    long a = collatzCycle(v);
    ASSERT_TRUE(a == 35);
}
TEST(Collatz, collatzCycle_5){
    long v = 64568;
    long a = collatzCycle(v);
    ASSERT_TRUE(a == 74);
}