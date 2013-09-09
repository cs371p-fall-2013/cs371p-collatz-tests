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

TEST(Collatz, read_1){
    std::istringstream r("2 3");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    2);
    ASSERT_TRUE(j ==    3);

}

TEST(Collatz, read_2){
    std::istringstream r("1 \n \n 10000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10000);
}

TEST(Collatz, read_3){
    std::istringstream r("100 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   100);
    ASSERT_TRUE(j ==   10);
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

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval_5) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);} 

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_1){
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");
}

TEST(Collatz, print_2){
    std::ostringstream w;
    collatz_print(w, 20, 10000, 1333);
    ASSERT_TRUE(w.str() == "20 10000 1333\n");
}

TEST(Collatz, print_3){
    std::ostringstream w;
    collatz_print(w, 11, 1111, 111);
    ASSERT_TRUE(w.str() == "11 1111 111\n");
}



// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_1) {
    std::istringstream r("8 9\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "8 9 20\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("1 1\n8 8\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n8 8 4\n");}

TEST(Collatz, solve_3) {
    std::istringstream r("1 10\n11 20\n1 20\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n11 20 21\n1 20 21\n");}

