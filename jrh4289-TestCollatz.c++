/*To test the program:
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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

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
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 10);}

TEST(Collatz, read1)
{
  std::istringstream r("20 20\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i == 20);
  ASSERT_TRUE(j == 20);
}

TEST(Collatz, read2)
{
  std::istringstream r("500 600\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i == 500);
  ASSERT_TRUE(j == 600);
}
 
TEST(Collatz, read3)
{
  std::istringstream r("800 500\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i == 800);
  ASSERT_TRUE(j == 500);
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

TEST(Collatz, eval_5) 
{
  const int v = collatz_eval(500, 10);
  ASSERT_TRUE(v == 144); 
}

TEST(Collatz, eval_6) 
{
  const int v = collatz_eval(800, 805);
  ASSERT_TRUE(v == 60); 
}

TEST(Collatz, eval_7) 
{
  const int v = collatz_eval(500, 600);
  ASSERT_TRUE(v == 137); 
}
// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 4, 15, 26);
    ASSERT_TRUE(w.str() == "4 15 26\n");}

TEST(Collatz, print1) 
{
  std::ostringstream w;
  collatz_print(w, 41, 340, 240);
  ASSERT_TRUE(w.str() == "41 340 240\n");
}

TEST(Collatz, print2) 
{
  std::ostringstream w;
  collatz_print(w, 47, 827, 736);
  ASSERT_TRUE(w.str() == "47 827 736\n");
}

TEST(Collatz, print3) 
{
  std::ostringstream w;
  collatz_print(w, 130, 74, 56);
  ASSERT_TRUE(w.str() == "130 74 56\n");
}


// -----
// solve
// -----

TEST(Collatz, solve) 
{
  std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
}

TEST(Collatz, solve1) 
{
  std::istringstream r("1 10\n100 200\n201 210\n900 1000\n500 10\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n500 10 144\n");
}

TEST(Collatz, solve2) 
{
  std::istringstream r("1 10\n100 200\n201 210\n900 1000\n10 500\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n10 500 144\n");
}

TEST(Collatz, solve3) 
{
  std::istringstream r("1 10\n100 200\n201 210\n900 1000\n500 600\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n500 600 137\n");
}

