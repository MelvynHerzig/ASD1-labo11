#include "catch.hpp"
#include "../bst.h"

#include <sstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace std;

template<typename T>
string to_string(T const& t) {
    ostringstream oss;
    oss << t;
    return oss.str();
}

template <typename Key>
void displayPlusOne(const Key& key)
{
   std::cout << key + 1 << " ";
}

TEST_CASE( "operator<<", "[bst]") {

    bst<int> tree;

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);
        REQUIRE( to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION( "Empty tree" ) {
        REQUIRE( to_string(tree) == "" );
    }
}

TEST_CASE( "insert", "[bst]") {

    bst<int> tree;

    SECTION( "Insert 42" ) {
        tree.insert(42);
        REQUIRE( to_string(tree) == "42" );
    }

    SECTION( "Insert smaller to the left" ) {
        tree.insert(3);
        tree.insert(2);
        REQUIRE( to_string(tree) == "3(2,.)" );
    }

    SECTION( "Insert larger to the right" ) {
        tree.insert(3);
        tree.insert(4);
        REQUIRE( to_string(tree) == "3(.,4)" );
    }

    SECTION( "Insert twice has no effect" ) {
        tree.insert(3);
        tree.insert(4);
        tree.insert(4);
        REQUIRE( to_string(tree) == "3(.,4)" );
    }
}

TEST_CASE("display_indented", "[bst]") {
    bst<int> tree;

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str() == "8\n"
                              "|_ 4\n"
                              "|  |_ 1\n"
                              "|  |  |_ .\n"
                              "|  |  |_ 2\n"
                              "|  |     |_ .\n"
                              "|  |     |_ 3\n"
                              "|  |_ 6\n"
                              "|     |_ 5\n"
                              "|     |_ 7\n"
                              "|_ 11\n"
                              "   |_ 10\n"
                              "   |_ 12\n" );
    }
}

TEST_CASE("Copy constructor", "[bst]")
{

   SECTION( "Copied tree from ASD1 slides" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      bst<int> treeCopied = {tree};

      REQUIRE(to_string(treeCopied) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))");
   }

   SECTION( "Copied empty tree" ) {

      bst<int> tree;
      bst<int> treeCopied = {tree};
      REQUIRE( to_string(treeCopied) == "" );
   }
}

TEST_CASE("operator =", "[bst]")
{

   SECTION( "Affected from tree from ASD1 slides" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      bst<int> treeAffected;
      for (int i : {5 , 4, 8, 2, 1})
         treeAffected.insert(i);

      treeAffected = tree;

      REQUIRE(to_string(treeAffected) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))");
   }

   SECTION( "Affected from empty tree" ) {

      bst<int> tree;

      bst<int> treeAffected;
      for (int i : {5 , 4, 8, 2, 1})

      treeAffected = tree;
      REQUIRE( to_string(treeAffected) == "" );
   }
}

TEST_CASE("min()", "[bst]")
{

   SECTION( "Min of tree from ASD1 slides" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      REQUIRE(tree.min() == 1);
   }

   SECTION( "Min of empty tree" ) {

      bst<int> tree;

      CHECK_THROWS_AS(tree.min(), std::exception);
   }
}

TEST_CASE("max()", "[bst]")
{

   SECTION( "max of tree from ASD1 slides" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      REQUIRE(tree.max() == 12);
   }

   SECTION( "max of empty tree" ) {

      bst<int> tree;

      CHECK_THROWS_AS(tree.max(), std::exception);
   }
}

TEST_CASE("erase_min()", "[bst]")
{

   SECTION( "erase min of tree from ASD1 slides" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      tree.erase_min();

      REQUIRE(to_string(tree) == "8(4(2(.,3),6(5,7)),11(10,12))");
   }

   SECTION( "erase min on one node tree " )
   {
      bst<int> tree;

      tree.insert(1);

      tree.erase_min();

      REQUIRE(to_string(tree) == "");
   }

   SECTION( "erase min of empty tree" ) {

      bst<int> tree;

      CHECK_THROWS_AS(tree.erase_min(), std::exception);
   }
}

TEST_CASE("erase_max()", "[bst]")
{

   SECTION( "erase max of tree from ASD1 slides" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      tree.erase_max();

      REQUIRE(to_string(tree) == "10(4(1(.,2(.,3)),6(5,7)),11(10,12))");
   }

   SECTION( "erase max on one node tree " )
   {
      bst<int> tree;

      tree.insert(1);

      tree.erase_max();

      REQUIRE(to_string(tree) == "");
   }

   SECTION( "max of empty tree" ) {

      bst<int> tree;

      CHECK_THROWS_AS(tree.erase_min(), std::exception);
   }
}

TEST_CASE("erase()", "[bst]")
{

   SECTION( "erase existing key of tree from ASD1 slides" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      tree.erase(6);

      REQUIRE(to_string(tree) == "8(4(1(.,2(.,3)),7(5,.)),11(10,12))");
   }

   SECTION( "erase non existing key of tree from ASD1 slides" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      CHECK_NOTHROW(tree.erase(22));
      REQUIRE( to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
   }

   SECTION( "erase the only key " )
   {
      bst<int> tree;

      tree.insert(1);

      tree.erase(1);

      REQUIRE(to_string(tree) == "");
   }

   SECTION( "erase on empty tree" ) {

      bst<int> tree;

      CHECK_THROWS_AS(tree.erase(5), std::exception);
   }
}

TEST_CASE("visit_in_order()", "[bst]")
{

   SECTION( "Display and add 1 to key" )
   {
      bst<int> tree;

      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      std::ostringstream oss;
      std::streambuf* p_cout_streambuf = std::cout.rdbuf();
      std::cout.rdbuf(oss.rdbuf());

      tree.visit_in_order(displayPlusOne<int>);

      std::cout.rdbuf(p_cout_streambuf); // restore

      // test your oss content...
      std::cout << "Recu " << oss.str() << std::endl;
      std::cout << "Attendu " << "2 3 4 5 6 7 8 9 11 12 13 " << std::endl;
      REQUIRE(oss.str() == "2 3 4 5 6 7 8 9 11 12 13 ");
   }

   SECTION( "Doing nothing on empty tree" )
   {
      bst<int> tree;

      CHECK_NOTHROW(tree.visit_in_order(displayPlusOne<int>));
   }
}
