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

TEST(Collatz, read_1) 
{
  std::istringstream r("1 10\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i ==    1);
  ASSERT_TRUE(j ==   10);
}

TEST(Collatz, read_2)
{
  std::istringstream r("10 1\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i ==    10);
  ASSERT_TRUE(j ==   1);
}

TEST(Collatz, read_3)
{
  std::istringstream r("9999 9999\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i ==    9999);
  ASSERT_TRUE(j ==   9999);
}

TEST(Collatz, read_4)
{
  std::istringstream r("1000000 1000000\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i ==    1000000);
  ASSERT_TRUE(j ==   1000000);
}

// ----
// eval
// ----

TEST(Collatz, eval_1)
{
  const int v = collatz_eval(1, 10);
  ASSERT_TRUE(v == 20);
}

TEST(Collatz, eval_2)
{
  const int v = collatz_eval(100, 200);
  ASSERT_TRUE(v == 125);
}

TEST(Collatz, eval_3)
{
  const int v = collatz_eval(201, 210);
  ASSERT_TRUE(v == 89);
}

TEST(Collatz, eval_4)
{
  const int v = collatz_eval(900, 1000);
  ASSERT_TRUE(v == 174);
}

// -----
// print
// -----

TEST(Collatz, print_1)
{
  std::ostringstream w;
  collatz_print(w, 1, 10, 20);
  ASSERT_TRUE(w.str() == "1 10 20\n");
}

TEST(Collatz, print_2)
{
  std::ostringstream w;
  collatz_print(w, 900, -10, 120);
  ASSERT_TRUE(w.str() == "900 -10 120\n");
}

TEST(Collatz, print_3)
{
  std::ostringstream w;
  collatz_print(w, 0, 0, 1000);
  ASSERT_TRUE(w.str() == "0 0 1000\n");
}

TEST(Collatz, print_4)
{
  std::ostringstream w;
  collatz_print(w, 10000, 10000000, 1000);
  ASSERT_TRUE(w.str() == "10000 10000000 1000\n");
}

// -----
// solve
// -----

TEST(Collatz, solve_1)
{
  std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
}

TEST(Collatz, solve_2)
{
  std::istringstream r("455318 920747\n523979 809807\n153614 299067\n749919 923439\n535995 572045\n630802 904449\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "455318 920747 525\n523979 809807 509\n153614 299067 443\n749919 923439 525\n535995 572045 452\n630802 904449 525\n");
}


TEST(Collatz, solve_3)
{
  std::istringstream r("60279 571724\n31365 529311\n285837 724316\n80123 594689\n279280 491126\n96426 295136\n85986 634619\n599683 658656\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "60279 571724 470\n31365 529311 470\n285837 724316 509\n80123 594689 470\n279280 491126 449\n96426 295136 443\n85986 634619 509\n599683 658656 509\n");
}



TEST (Collatz, len_1)
{
  int cache [1000000] = {};
  const int v = getLength (10, cache);
  ASSERT_TRUE (v == 7);
}
TEST (Collatz, len_2)
{
  int cache [1000000] = {};
  const int v = getLength (30000, cache);
  ASSERT_TRUE (v == 179);
}

TEST (Collatz, len_3)
{
  int cache [1000000] = {};
  const int v = getLength (1, cache);
  ASSERT_TRUE (v == 1);
}

TEST (Collatz, len_4)
{
  int cache [1000000] = {};
  const int v = getLength (1000000, cache);
  ASSERT_TRUE (v == 153);
}


TEST (Collatz, maxlen_1)
{
  const int v = getMaxLength (1, 10);
  ASSERT_TRUE (v == 20);
}

TEST (Collatz, maxlen_2)
{
  const int v = getMaxLength (2, 10);
  ASSERT_TRUE (v == 20);
}


TEST (Collatz, maxlen_3)
{
  const int v = getMaxLength (1, 10000);
  ASSERT_TRUE (v == 262);
}

TEST (Collatz, maxlen_4)
{
  const int v = getMaxLength (900, 10000);
  ASSERT_TRUE (v == 262);
}






