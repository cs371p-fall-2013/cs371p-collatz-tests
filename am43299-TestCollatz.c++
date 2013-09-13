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
#include <iterator> // istream_iterator
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // make_pair, pair

#include "gtest/gtest.h"

#include "Collatz2.h"

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(Collatz, read) {
    std::istringstream         r("1 10\n");
    std::istream_iterator<int> q(r);
    const std::pair<int, int>  p = collatz_read(q);
    ASSERT_TRUE(p.first  ==  1);
    ASSERT_TRUE(p.second == 10);}

TEST(Collatz, read) {  //my unit test for read: 1st
    std::istringstream         r("1 1\n");
    std::istream_iterator<int> q(r);
    const std::pair<int, int>  p = collatz_read(q);
    ASSERT_TRUE(p.first  ==  1);
    ASSERT_TRUE(p.second == 1);}
    
TEST(Collatz, read) {  //my unit test for read: 2nd
    std::istringstream         r("9 100\n");
    std::istream_iterator<int> q(r);
    const std::pair<int, int>  p = collatz_read(q);
    ASSERT_TRUE(p.first  ==  9);
    ASSERT_TRUE(p.second == 100);}
    
TEST(Collatz, read) {  //my unit test for read: 3rd
    std::istringstream         r("15 31\n");
    std::istream_iterator<int> q(r);
    const std::pair<int, int>  p = collatz_read(q);
    ASSERT_TRUE(p.first  ==  15);
    ASSERT_TRUE(p.second == 31);}
    
// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(std::make_pair(1, 10));
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(std::make_pair(100, 200));
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(std::make_pair(201, 210));
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(std::make_pair(900, 1000));
    ASSERT_TRUE(v == 174);}

  
  
TEST(Collatz, eval_5) { //my unit test for eval: 1st
    const int v = collatz_eval(std::make_pair(9, 9));
    ASSERT_TRUE(v == 20);  	//  9 - 28 - 14 - 7 - 22 - 11 - 34 - 17 - 52 - 26 - 13 - 40 - 20 - 10 - 5 - 16 - 8 - 4 - 2 - 1
}

TEST(Collatz, eval_6) { //my unit test for eval: 2nd
    const int v = collatz_eval(std::make_pair(8, 9));
    ASSERT_TRUE(v == 20);
}

TEST(Collatz, eval_6) { //my unit test for eval: 3rd
    const int v = collatz_eval(std::make_pair(9,11));
    ASSERT_TRUE(v == 20);
}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, std::make_pair(1, 10), 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print) { //my unit test for print: 1st
    std::ostringstream w;
    collatz_print(w, std::make_pair(8, 9), 20);
    ASSERT_TRUE(w.str() == "8 9 20\n");}

TEST(Collatz, print) { //my unit test for print: 2nd
    std::ostringstream w;
    collatz_print(w, std::make_pair(100, 200), 89);
    ASSERT_TRUE(w.str() == "100 200 89\n");}
    
TEST(Collatz, print) { //my unit test for print: 3rd
    std::ostringstream w;
    collatz_print(w, std::make_pair(9, 9), 20);
    ASSERT_TRUE(w.str() == "9 9 20\n");}
    
// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve) { //my unit test for solve: 1st 
    std::istringstream r("8 9\n9 10\n9 13\n10 13\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "8 9 20\n9 10 20\n9 13 20\n10 13 15\n");}
    
TEST(Collatz, solve) { //my unit test for solve: 2nd
    std::istringstream r("1 1\n10 10\n2 3\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n10 10 7\n2 3 8\n");}
    
TEST(Collatz, solve) { //my unit test for solve: 3rd
    std::istringstream r("100 210\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "100 210 125\n");}