//
// Created by Olivier Cuisenaire on 23.05.20.
//

#include <iostream>
#include "bst.h"


//TODO Crausaz

//TODO Forestier
// - Valider les tests, en écrire de nouveaux si nécessaire
// - void display_indented(std::ostream &s) const noexcept ;
// - void linearize() noexcept ;
// - void balance() noexcept ;

//TODO Herzig

//TODO Tout le monde
// - Refactor le code

using namespace std;

int main() {

    bst<int> t{};

    for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
        t.insert(i);

    t.balance();
    cout << t << endl;
}