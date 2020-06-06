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
   }
   else if (k == r->key)
   {
      // k already there : do nothing.
   }
   else if (k < r->key)
   {
      insert(r->left, k);
   }
   else
   {
      // k > r->key
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
   if (node == nullptr) return;

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
   if (parentSrc == nullptr) return;

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
   {
      return false;
   }
   else if (node->key == k)
   {
      return true;
   }
   else if (node->key > k)
   {
      return search(node->left, k);
   }
   else
   {
      return search(node->right, k);
   }
}

template <typename Key>
template <typename Fn>
void bst<Key>::symetricForEach(Node<Key>* const& r, Fn f)
{
   if (r == nullptr) return;
   symetricForEach(r->left, f);
   f(r->key);
   symetricForEach(r->right, f);
}

template <typename Key>
void bst<Key>::creationDisplayIndented(std::ostream& s, Node<Key>* const& r, std::string prefix) noexcept
{
   if (r == nullptr)
   {
      s << ".\n";
      return;
   }

   s << r->key << "\n";

   if (r->left == nullptr && r->right == nullptr)
   { return; }

   s << prefix << "|_ ";
   creationDisplayIndented(s, r->left, prefix + "|  ");

   s << prefix << "|_ ";
   creationDisplayIndented(s, r->right, prefix + "   ");
}

template <typename Key>
void bst<Key>::linearizeRecursive(Node<Key>* r, Node<Key>*& L, size_t& n) noexcept
{
   if (r == nullptr) return;

   linearizeRecursive(r->right, L, n);
   r->right = L;
   L = r;
   ++n;
   linearizeRecursive(r->left, L, n);
   r->left = nullptr;
}

template <typename Key>
Node<Key>* bst<Key>::arborizeRecursive(Node<Key>*& L, size_t n) noexcept
{
   if (n == 0) return nullptr;

   Node<Key>* rg = arborizeRecursive(L, (n-1)/2);
   Node<Key>* r = L;
   r->left = rg;
   L = L->right;
   r->right =  arborizeRecursive(L, n/2);
   return r;
}

template <typename Key>
void bst<Key>::deleteKey(Node<Key>*& node, const Key& k)
{
   if (node == nullptr) return;

   if (k < node->key) {
      deleteKey(node->left, k);
   }
   else if (k > node->key)
   {
      deleteKey(node->right, k);
   }
   else
   {
      Node<Key>* tmp = node;
      if (node->left == nullptr)
      {
         node = node->right;
      }
      else if (node->right == nullptr)
      {
         node = node->left;
      }
      else
      {
         tmp = exitMin(node->right);
         tmp->right = node->right;
         tmp->left = node->left;
         node = tmp;
      }
      delete tmp;
   }
}

template <typename Key>
Node<Key>* bst<Key>::exitMin(Node<Key>*& node)
{
   if (node->left != nullptr)
   {
      return exitMin(node->left);
   }

   Node<Key>* tmp = node;
   node = node->right;
   return tmp;
}

// méthodes de la classe bst

template <typename Key>
bst<Key>::bst() : root(nullptr)
{}

template <typename Key>
bst<Key>::bst(bst const& other) : bst()
{
   if (other.root == nullptr) return;

   root = new Node<Key>{other.root->key, nullptr, nullptr};
   copyDescendant(root, other.root);
}

template <typename Key>
bst<Key>& bst<Key>::operator=(bst const& other)
{
   if (other.root == nullptr) return *this;

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
   if (root == nullptr) return false;

   return search(root, k);
}

template <typename Key>
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

template <typename Key>
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
   deleteKey(root, min());
}

template<typename Key>
void bst<Key>::erase_max()
{
   if (root == nullptr) throw std::exception();
   deleteKey(root, max());
}

template<typename Key>
void bst<Key>::erase(Key const& k) noexcept
{
   if (root == nullptr) return;
   deleteKey(root, k);
}

template <typename Key>
void bst<Key>::display_indented(std::ostream& s) const noexcept
{
   creationDisplayIndented(s, root, "");
}

template <typename Key>
void bst<Key>::linearize() noexcept
{
   if (root == nullptr) return;

   Node<Key>* L = nullptr;
   size_t compteur = 0;
   linearizeRecursive(root, L, compteur);
   root = L;
}

template <typename Key>
void bst<Key>::balance() noexcept
{
   if (root == nullptr) return;

   Node<Key>* L = nullptr;
   size_t compteur = 0;
   linearizeRecursive(root, L, compteur);
   root = arborizeRecursive(L, compteur);
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
