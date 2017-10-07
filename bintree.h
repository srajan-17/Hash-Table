// Siddharth Rajan
// CSC 21200

// FILE: bintree.h
// PROVIDES: A template class for a node in a binary tree and functions for
// manipulating binary trees. The template parameter is the type of value in
// each node.
//
// TYPEDEF for the binary_tree_node<Item> template class:
//   Each node of the tree contains a key, value, and pointers to its
//   children. The type of the value (binary_tree_node<Item>::value_type) is
//   the Item type from the template parameter. The type may be any of the C++
//   built-in types (int, char, etc.), or a class with a default constructor,
//   and an assignment operator. The value of the key is size_t.
//
// CONSTRUCTOR for the binary_tree_node<Item> class:
//   binary_tree_node(
//                    size_t& init_key,
//                    const Item& init_value = Item( ),
//                    binary_tree_node* init_left = NULL,
//                    binary_tree_node* init_right = NULL
//                   )
//     Postcondition: The new node has its key equal to init_key, value equal to init_value,
//     and it's child pointers equal to init_left and init_right.
//
// MEMBER FUNCTIONS for the binary_tree_node<Item> class:
//   const size_t& key() const         <---- const version
//   and
//   size_t& key()                     <---- non-const version
//     Postcondition: The return value is a reference to the key from
//     this binary_tree_node.
//
//   const item& value( ) const      <----- const version
//   and
//   Item& value( )                  <----- non-const version
//     Postcondition: The return value is a reference to the value from
//     this binary_tree_node.
//
//   const binary_tree_node* left( ) const  <----- const version
//   and
//   binary_tree_node* left( )              <----- non-const version
//   and
//   const binary_tree_node* right( ) const <----- const version
//   and
//   binary_tree_node* right( )             <----- non-const version
//     Postcondition: The return value is a pointer to the left or right child
//     (which will be NULL if there is no child).
//
//   void set_key(const size_t& new_key)
//     Postcondition: The binary_tree_node now contains the specified new key.
//
//   void set_value(const Item& new_value)
//     Postcondition: The binary_tree_node now contains the specified new value.
//
//   void set_left(binary_tree_node* new_link)
//   and
//   void set_right(binary_tree_node* new_link)
//     Postcondition: The binary_tree_node now contains the specified new link
//     to a child.
//
//   bool is_leaf( )
//     Postcondition: The return value is true if the node is a leaf;
//     otherwise the return value is false.
//
// NON-MEMBER FUNCTIONS to maniplulate binary tree nodes:
//   template <class Item>
//   binary_tree_node<Item>* createBST(kv<Item> array[], int start, int end)
//     Postcondition: The return value is a pointer to a binary search tree that is created using the
//     elements in the sorted array that is provided to the function. The array must be of a type that
//     contains variables to store a key and value.
//
//   template <class Item>
//   void inorder_copy(const binary_tree_node<Item> *node_ptr, kv<Item> array[], int i)
//     Postcondition: The elements in the binary search tree pointed to by node_ptr are copied to array.
//     The array must be of a type that contains variables to store a key and value.
//
//   template <class Item>
//   void inorder_search(const binary_tree_node<Item> *node_ptr, size_t key, bool found)
//     Precondition: node_ptr is a pointer to a node in a binary tree (or node_ptr may be NULL to
//     indicate the empty tree).
//     Postcondition: If node_ptr is non-NULL, then the function checks every node in the binary tree
//     using the inorder method. If the key in a node is equal to the key provided in the function
//     parameter, then found is set to true. Otherwise, found is false.
//
//   template <class Item>
//   void inorder_value(const binary_tree_node<Item> *node_ptr, size_t key, Item& found);
//     Precondition: node_ptr is a pointer to a node in a binary tree (or
//     node_ptr may be NULL to indicate the empty tree).
//     Postcondition: If node_ptr is non-NULL, then the function checks every node in the binary tree
//     using the inorder method. If the key in a node is equal to the key provided in the function
//     parameter, then found is set to be equal to the value contained in that node. Otherwise, found may
//     be any garbage value.
//
//   template <class Item, class SizeType>
//   void print(const binary_tree_node<Item>* node_ptr, SizeType depth)
//     Precondition: node_ptr is a pointer to a node in a binary tree (or
//     node_ptr may be NULL to indicate the empty tree). If the pointer is
//     not NULL, then depth is the depth of the node pointed to by node_ptr.
//     Postcondition: If node_ptr is non-NULL, then the contents of *node_ptr
//     and all its descendants have been written to cout with the << operator,
//     using a backward in-order traversal. Each node is indented four times
//     its depth.
//
//   template <class Item>
//   void tree_clear(binary_tree_node<Item>*& root_ptr)
//     Precondition: root_ptr is the root pointer of a binary tree (which may
//     be NULL for the empty tree).
//     Postcondition: All nodes at the root or below have been returned to the
//     heap, and root_ptr has been set to NULL.
//
//   template <class Item>
//   binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr)
//     Precondition: root_ptr is the root pointer of a binary tree (which may
//     be NULL for the empty tree).
//     Postcondition: A copy of the binary tree has been made, and the return
//     value is a pointer to the root of this copy.
//
//   template <class Item>
//   size_t tree_size(const binary_tree_node<Item>* node_ptr)
//     Precondition: node_ptr is a pointer to a node in a binary tree (or
//     node_ptr may be NULL to indicate the empty tree).
//     Postcondition: The return value is the number of nodes in the tree.

#ifndef BINTREE_H
#define BINTREE_H
#include <cstdlib>  // Provides NULL and size_t
using std::size_t;

namespace sid_raj_hw5
{
    
    template <class Item>
    class binary_tree_node
    {
    public:
        // TYPEDEF
        typedef Item value_type;
        // CONSTRUCTOR
        binary_tree_node(
                         size_t& init_key,
                         const Item& init_value = Item( ),
                         binary_tree_node* init_left = NULL,
                         binary_tree_node* init_right = NULL
                         )
        {
            key_field = init_key;
            value_field = init_value;
            left_field = init_left;
            right_field = init_right;
        }
        // MODIFICATION MEMBER FUNCTIONS
        size_t& key() { return key_field; }
        Item& value( ) { return value_field; }
        binary_tree_node* left( ) { return left_field; }
        binary_tree_node* right( ) { return right_field; }
        void set_key(const size_t& new_key) { key_field = new_key; }
        void set_value(const Item& new_value) { value_field = new_value; }
        void set_left(binary_tree_node* new_left) { left_field = new_left; }
        void set_right(binary_tree_node* new_right) { right_field = new_right; }
        // CONST MEMBER FUNCTIONS
        const size_t& key() const { return key_field; }
        const Item& value( ) const { return value_field; }
        const binary_tree_node* left( ) const { return left_field; }
        const binary_tree_node* right( ) const { return right_field; }
        bool is_leaf( ) const
        { return (left_field == NULL) && (right_field == NULL); }
    private:
        Item value_field;
        size_t key_field;
        binary_tree_node *left_field;
        binary_tree_node *right_field;
    };
    
    template <class Item>                                          // <-- array to store key, value pairs
    struct kv {
        size_t key;
        Item value;
    };
    
    // NON-MEMBER FUNCTIONS for the binary_tree_node<Item>:
    template <class Item>
    binary_tree_node<Item>* createBST(kv<Item> array[], int start, int end);
    
    template <class Item>
    void inorder_copy(const binary_tree_node<Item> *node_ptr, kv<Item> array[], int i);
    
    template <class Item>
    void inorder_search(const binary_tree_node<Item> *node_ptr, size_t key, bool found);
    
    template <class Item>
    void inorder_value(const binary_tree_node<Item> *node_ptr, size_t key, Item& found);
    
    template <class Item, class SizeType>
    void print(binary_tree_node<Item>* node_ptr, SizeType depth);
    
    template <class Item>
    void tree_clear(binary_tree_node<Item>*& root_ptr);
    
    template <class Item>
    binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr);
    
    template <class Item>
    size_t tree_size(const binary_tree_node<Item>* node_ptr);
    
    template <class Item>
    void tree_insert(binary_tree_node<Item>* insert_ptr);
}

// FILE: bintree.template
// IMPLEMENTS: The binary_tree node class (see bintree.h for documentation).
#include <cassert>    // Provides assert
#include <iomanip>    // Provides std::setw
#include <iostream>   // Provides std::cout
using std::cout;
using std::endl;

namespace sid_raj_hw5
{
    
    template <class Item>
    binary_tree_node<Item>* createBST(kv<Item> array[], int start, int end) {
        
        if (start > end)
            return NULL;
        
        int mid = (start + end) / 2;
        
        binary_tree_node<Item>* root = new binary_tree_node<Item>(array[mid].key, array[mid].value);
        
        root->set_left(createBST(array, start, mid - 1));
        root->set_right(createBST(array, mid + 1, end));
        
        return root;
        
    }
    
    template <class Item>
    void inorder_copy(const binary_tree_node<Item> *node_ptr, kv<Item> array[], int i) {
        if (node_ptr != NULL) {
            inorder_copy(node_ptr->left(), array, i + 1);
            array[i].key = node_ptr->key();
            array[i].value = node_ptr->value();
            inorder_copy(node_ptr->right(), array, i + 1);
        }
    }
    
    template <class Item>
    void inorder_search(const binary_tree_node<Item> *node_ptr, size_t key, bool found) {
        if (node_ptr != NULL) {
            inorder_search(node_ptr->left(), key, found);
            if (node_ptr->key() == key)
                found = true;
            inorder_search(node_ptr->right(), key, found);
        }
    }
    
    
    template <class Item>
    void inorder_value(const binary_tree_node<Item> *node_ptr, size_t key, Item& found)
    // Library facilities used: cstdlib
    {
        if (node_ptr != NULL)
        {
            inorder_value(node_ptr->left( ), key, found);
            if (node_ptr->key() == key)
                found = node_ptr->value();
            inorder_value(node_ptr->right( ), key, found);
        }
    }
    
    template <class Item, class SizeType>
    void print(binary_tree_node<Item>* node_ptr, SizeType depth)
    // Library facilities used: iomanip, iostream, stdlib
    {
        if (node_ptr != NULL)
        {
            print(node_ptr->right( ), depth+1);
            std::cout << std::setw(4*depth) << ""; // Indent 4*depth spaces.
            std::cout << node_ptr->value( ) << std::endl;
            print(node_ptr->left( ),  depth+1);
        }
    }
    
    template <class Item>
    void tree_clear(binary_tree_node<Item>*& root_ptr)
    // Library facilities used: cstdlib
    {
        binary_tree_node<Item>* child;
        if (root_ptr != NULL)
        {
            child = root_ptr->left( );
            tree_clear( child );
            child = root_ptr->right( );
            tree_clear( child );
            delete root_ptr;
            root_ptr = NULL;
        }
    }
    
    template <class Item>
    binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr)
    // Library facilities used: cstdlib
    {
        binary_tree_node<Item> *l_ptr;
        binary_tree_node<Item> *r_ptr;
        
        if (root_ptr == NULL)
            return NULL;
        else
        {
            l_ptr = tree_copy( root_ptr->left( ) );
            r_ptr = tree_copy( root_ptr->right( ) );
            return
            new binary_tree_node<Item>( root_ptr->value( ), l_ptr, r_ptr);
        }
    }
    
    template <class Item>
    size_t tree_size(const binary_tree_node<Item>* node_ptr)
    // Library facilities used: cstdlib
    {
        if (node_ptr == NULL)
            return 0;
        else 
            return 
            1 + tree_size(node_ptr->left( )) + tree_size(node_ptr->right( ));
    }
    
    template <class Item>
    void tree_insert(binary_tree_node<Item>* root, size_t key, Item value) {
        
        binary_tree_node<Item>* left = root->left();
        binary_tree_node<Item>* right = root->right();
        
        if (left == NULL) {
            if (value < root->value())
                left = new binary_tree_node<Item>(key, value);
        }
        
        if (right == NULL) {
            if (value > root->value())
                right = new binary_tree_node<Item>(key, value);
        }
        
        if (value < root->value())
            tree_insert(left, key, value);
        else if (value > root->value())
            tree_insert(right, key, value);
        
    }
    
}

#endif
