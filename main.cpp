//
// Created by Olivier Cuisenaire on 23.05.20.
//

#include <iostream>
#include "bst.h"


//TODO Crausaz
// - Valider les tests, en écrire de nouveaux si nécessaire
// - Key const& min() const ;
// - Key const& max() const ;
// - void erase_min() ;
// - void erase_max() ;
// - void erase(Key const& k) noexcept ;

//TODO Forestier
// - Valider les tests, en écrire de nouveaux si nécessaire
// - template<typename Fn> void visit_in_order(Fn f) const;
// - void display_indented(std::ostream &s) const noexcept ;
// -  void linearize() noexcept ;
// -  void balance() noexcept ;

//TODO Herzig
// - bst(bst const &other);
// - bst &operator=(bst const &other);
// - ~bst();
// - bool contains(Key const& k) const noexcept ; // recherche de l'élément

//TODO Tout le monde
// - Refactor le code

using namespace std;

int main() {

    bst<int> t{};

    for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
        t.insert(i);

    cout << t << endl;
}