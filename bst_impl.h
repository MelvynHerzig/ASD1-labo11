//
// Created by Olivier Cuisenaire on 23.05.20.
//

#ifndef ASD1_LABS_2020_BST_IMPL_H
#define ASD1_LABS_2020_BST_IMPL_H

// fonctions récursives n'ayant pas à connaitre root

#include "bst.h"

template <typename Key>
void bst<Key>::insert(Node<Key>*& r, Key const& k)
{
   if (r == nullptr)
   {
      r = new Node<Key>{k, nullptr, nullptr};
   } else if (k == r->key)
   {
      // k already there : do nothing.
   } else if (k < r->key)
   {
      insert(r->left, k);
   } else
   { // k > r->key
      insert(r->right, k);
   }
}

template <typename Key>
void bst<Key>::to_stream(Node<Key>* r, std::ostream& s) noexcept
{
   if (r)
   {
      s << r->key;
      if (r->right or r->left)
      { // r has children
         s << "(";
         if (r->left)
         { to_stream(r->left, s); }
         else
         { s << "."; }

         s << ",";

         if (r->right)
         { to_stream(r->right, s); }
         else
         { s << "."; }

         s << ")";
      }
   }
}

template <typename Key>
void bst<Key>::destructNode(Node<Key>*& node)
{
   if (node == nullptr)
   { return; }

   if (node->left != nullptr)
   {
      destructNode(node->left);
   }

   if (node->right != nullptr)
   {
      destructNode(node->right);
   }
   delete node;
}

template <typename Key>
void bst<Key>::copyDescendant(Node<Key>*& parentDst, Node<Key>* const& parentSrc)
{
   if (parentSrc == nullptr)
   { return; }

   //Left child copy
   if (parentSrc->left != nullptr)
   {
      parentDst->left = new Node<Key>{parentSrc->left->key, nullptr, nullptr};
      copyDescendant(parentDst->left, parentSrc->left);
   }

   //Right child copy
   if (parentSrc->right != nullptr)
   {
      parentDst->right = new Node<Key>{parentSrc->right->key, nullptr, nullptr};
      copyDescendant(parentDst->right, parentSrc->right);
   }
}

template <typename Key>
bool bst<Key>::search(Node<Key>* const& node, Key const& k)
{
   if (node == nullptr)
   { return false; }
   else if (node->key == k)
   { return true; }
   else if (node->key > k)
   { return search(node->left, k); }
   else
   { return search(node->right, k); }
}

template <typename Key>
template <typename Fn>
void bst<Key>::symetricForEach(Node<Key>* const& r, Fn f)
{
   if (r == nullptr)
   { return; }
   symetricForEach(r->left, f);
   f(r->key);
   symetricForEach(r->right, f);
}

template <typename Key>
void bst<Key>::deleteMinRecursive(Node<Key>*& node)
{
   if (node->left != nullptr) {
      deleteMinRecursive(node->left);
   }
   else
   {
      Node<Key>* d = node->right;
      delete node;
      node = d;
   }
}

template <typename Key>
void bst<Key>::deleteMaxRecursive(Node<Key>*& node)
{
   if (node->right != nullptr) {
      deleteMaxRecursive(node->right);
   }
   else
   {
      // TODO
      /*
      Node<Key>* d = node->right;
      delete node;
      node = d;
       */
   }
}

// méthodes de la classe bst

template <typename Key>
bst<Key>::bst() : root(nullptr)
{}

template <typename Key>
bst<Key>::bst(bst const& other) : bst()
{
   if (other.root == nullptr)
   { return; }

   root = new Node<Key>{other.root->key, nullptr, nullptr};
   copyDescendant(root, other.root);
}

template <typename Key>
bst<Key>& bst<Key>::operator=(bst const& other)
{
   if (other.root == nullptr)
   { return *this; }

   bst<Key> temp = other;

   std::swap(temp.root, root);

   return *this;
}

template <typename Key>
bst<Key>::~bst()
{
   destructNode(root);
}

template <typename Key>
void bst<Key>::insert(Key const& k)
{
   insert(root, k);
}

template <typename Key>
bool bst<Key>::contains(Key const& k) const noexcept
{
   if (root == nullptr)
   { return false; }

   return search(root, k);
}

// TODO: Crausaz
// toutes les fonctions se référant à min ou max lèvent une std::exception si l'arbre est vide
template<typename Key>
Key const& bst<Key>::min() const
{
   if (root == nullptr) throw std::exception();

   Node<Key>* m = root;
   while (m->left != nullptr)
   {
      m = m->left;
   }
   return m->key;
}

template<typename Key>
Key const& bst<Key>::max() const
{
   if (root == nullptr) throw std::exception();

   Node<Key>* m = root;
   while (m->right != nullptr)
   {
      m = m->right;
   }
   return m->key;
}

template<typename Key>
void bst<Key>::erase_min()
{
   if (root == nullptr) throw std::exception();
   deleteMinRecursive(root);
};

template<typename Key>
void bst<Key>::erase_max()
{
   if (root == nullptr) throw std::exception();
   deleteMaxRecursive(root);
};

template<typename Key>
void bst<Key>::erase(Key const& k) noexcept {};

template<typename Key>
void bst<Key>::display_indented(std::ostream &s) const noexcept {
    s << "does not work yet obviously";
}

template <typename Key>
std::ostream& operator<<(std::ostream& s, bst<Key> const& t)
{
   bst<Key>::to_stream(t.root, s);
   return s;
}

template <typename Key>
template <typename Fn>
void bst<Key>::visit_in_order(Fn f) const
{
   symetricForEach(root, f);
}


#endif //ASD1_LABS_2020_BST_IMPL_H
