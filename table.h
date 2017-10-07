/*
 Siddharth Rajan
 CSC 21200
 
 FILE: table.h
 TEMPLATE CLASS PROVIDED: table<ValueType> (a table of values with keys).
    This class is a container template class for a table of values.
    The template parameter, ValueType, is the data type of the values in the
    table. It may be any of the bulit-in C++ types (int, char, etc.), or a
    class with a default constructor and an assignment operator.


 CONSTRUCTOR for the table<ValueType> template class:
    table(size_t size = 20)
        Postcondition: The table has been initialized with the specified size. If no size is specified the default value of 20 will be used.

 MODIFICATION MEMBER FUNCTIONS for the table<ValueType> class:
    void put(size_t key, const ValueType& value)
        Precondition: key >= 0.
        Postcondition: The key is hashed to a specific index in the table, and the (key, value) pair is added to that index. If (key,value) pair(s) already exist at that index then the new pair is chained to the existing pairs using node pointers.
    void remove(size_t key)
        Postcondition: If a value was in the table with the specified key, then
            that (key, value) pair has been removed; otherwise the table is unchanged.

 CONSTANT MEMBER FUNCTIONS for the table<ValueType> class:
    ValueType get(size_t key) const
        Postcondition: If a value is found in the hash table that corresponds with key, then that value is returned. Otherwise, the return value is -300.
    size_t size( ) const
        Postcondition: Return value is the total number of indicies that have been used in the
        table.
 */

#ifndef table_h
#define table_h


#include <algorithm>
#include "bintree.h"

namespace sid_raj_hw5 {
    
    template <class ValueType>
    class table {
    public:
        // MEMBER CONSTANT
        static const size_t SIZE = 20;
        // CONSTRUCTOR AND DESTRUCTOR
        table(size_t size = 20);                                                   // NEEDED, IMPLEMENTED
        ~table();                                                                  // NEEDED, IMPLEMENTED
        // MODIFICATION MEMBER FUNCTIONS
        void put(size_t key, const ValueType& value);                              // NEEDED, IMPLEMENTED
        void remove(size_t key);                                                   // NEEDED, IMPLEMENTED
        // CONSTANT MEMBER FUNCTIONS
        ValueType get(size_t key) const;                                           // NEEDED, IMPLEMENTED
        size_t size() const { return total_records; }                              // NEEDED, IMPLEMENTED
    private:
        binary_tree_node<ValueType> *data[SIZE];                                   // NEEDED, IMPLEMENTED
        size_t table_size;                                                         // NEEDED, IMPLEMENTED
        size_t total_records;                                                      // NEEDED, IMPLEMENTED
        // HELPER MEMBER FUNCTIONS
        size_t hash(size_t key) const;                                             // NEEDED, IMPLEMENTED
        void rehash();                                                             // NEEDED, IMPLEMENTED
    };
    
    
}

/* 
 FILE: table.template
 TEMPLATE CLASS IMPLEMENTED: table (see table.h for documentation)
 INVARIANT for the table ADT:
    1. The number of records in the table is in the member variable total_records.
    2. The actual records of the table are stored in the array data, with
        a maximum of table_size entries. Each used spot in the array has a
        non-negative key.
 */

namespace sid_raj_hw5 {
    
    template <class T>
    void selectionsort(T data[], size_t n) {
        size_t i, j, index_of_largest;
        int largest;
        
        if (n == 0)
            return;
        
        for (i = n - 1; i > 0; --i) {
            largest = data[0].value;
            index_of_largest = 0;
            for (j = 1; j <= i; ++j) {
                if (data[j].value > largest) {
                    largest = data[j].value;
                    index_of_largest = j;
                }
            }
            size_t temp;
            int temp2;
            
            temp = data[i].key;
            data[i].key = data[index_of_largest].key;
            data[index_of_largest].key = temp;
            
            temp2 = data[i].value;
            data[i].value = data[index_of_largest].value;
            data[index_of_largest].value = temp2;
        }
    }
    
    template <class ValueType>
    table<ValueType>::table(size_t size) {
        table_size = size;
        total_records = 0;
        for (size_t i = 0; i < SIZE; ++i)
            data[i] = NULL;
        cout << "Table initialized with size " << table_size << "." << "\n\n";
    }
    
    template <class ValueType>
    table<ValueType>::~table() {
        for (size_t i = 0; i < SIZE; ++i)
            tree_clear(data[i]);
    }
    
    template <class ValueType>
    void table<ValueType>::put(size_t key, const ValueType& value) {
        
        // hash to index
        size_t h = hash(key);
        
        // find # of stuff in hashed index
        size_t count = tree_size(data[h]);
        
        // if this index is empty add one to total_records and add node this way
        if (count == 0) {
            ++total_records;
            data[h] = new binary_tree_node<ValueType>(key, value);
            
            // if total_records = 75% of table size call rehash function and return
            if (total_records == table_size * 0.75)
                rehash();
            return;
        }
        
        // if # of stuff in that index < 8 (linked list)
        if (count < 8) {
            // insert pair at end of linked list
            binary_tree_node<ValueType> *cursor;
            
            for (cursor = data[h]; cursor != NULL; cursor = cursor->left()) {
                if (cursor->left() == NULL)
                    break;
            }
            
            binary_tree_node<ValueType> *insert_ptr;
            insert_ptr = new binary_tree_node<ValueType>(key, value);
            cursor->set_left(insert_ptr);
            
            
            // if # of stuff in that index is now = 8 (it has to become a binary search tree)
            if (tree_size(data[h]) == 8) {
                
                // declare array, iterator variable and insert linked list contents to array
                kv<ValueType> temp[8];
                size_t i = 0;
                for (cursor = data[h]; cursor != NULL; cursor = cursor->left()) {
                    temp[i].key = cursor->key();
                    temp[i].value = cursor->value();
                    ++i;
                }
                
                // sort array
                selectionsort(temp, 8);
                
                // convert sorted array into binary search tree
                int start = 0;
                int end = 7;
                binary_tree_node<ValueType> *new_tree = createBST(temp, start, end);
                
                // replace linked list with tree in data[h]
                delete data[h];
                data[h] = new_tree;
            }
            return;
        }
        
        // if # of stuff in that index >= 8 (binary search tree)
        if (count >= 8) {
            // insert to tree
            binary_tree_node<ValueType> *cursor = data[h];
            tree_insert(cursor, key, value);
        }
    }
    
    template <class ValueType>
    void table<ValueType>::remove(size_t key) {
        
        // hash to index
        size_t h = hash(key);
        
        // find # of stuff in hashed index
        size_t count = tree_size(data[h]);
        
        // if index is empty return
        if (count == 0)
            return;
        
        // if # of stuff in that index < 6 (linked list)
        if (count < 6) {
            
            binary_tree_node<ValueType> *remove_ptr;
            binary_tree_node<ValueType> *cursor;
            
            // iterate through linked list, looking for key
            for (remove_ptr = data[h]; remove_ptr != NULL; remove_ptr = remove_ptr->left()) {
                if (remove_ptr->key() == key)
                    break;
            }
            // if key is not found return
            if (remove_ptr == NULL)
                return;
            
            // if node with key is found remove node with this key
            for (cursor = data[h]; cursor != NULL; cursor = cursor->left()) {
                if (cursor->left() == remove_ptr)
                    break;
            }
            
            if (data[h] == remove_ptr) {
                data[h] = NULL;
                delete remove_ptr;
            }
            else {
                cursor->set_left(remove_ptr->left());
                delete remove_ptr;
            }
        }
        
        
        // if # of stuff in index >= 6 (binary search tree)
        if (count >= 6) {
            
            // inorder search of tree looking for key
            binary_tree_node<ValueType> *cursor = data[h];
            bool found = false;
            inorder_search(cursor, key, found);
            
            // if key is not found
            if (found == false)
                return;
            // if key is found
            else {
                // copy tree keys,values into array
                kv<ValueType> temp[count];
                inorder_copy(cursor, temp, 0);    // <-- fills tree values in temp using inorder method
                
                size_t i;
                
                // iterate through array, stopping where the key is
                for (i = 0; i < count; ++i) {
                    if (temp[i].key == key)
                        break;
                }
                
                size_t j;
                
                // remove array element with key
                for (j = i; j < count; ++j) {
                    temp[j].key = temp[j + 1].key;
                    temp[j].value = temp[j + 1].value;
                }
                
                int used = int(count - 1);
                
                // if # of stuff in index > 6 (should still be a tree)
                if (used > 6) {
                    // convert array back into tree
                    binary_tree_node<ValueType> *new_tree = createBST(temp, 0, used);
                    delete data[h];
                    data[h] = new_tree;
                }
                else {
                    // else convert array into linked list
                    delete data[h];
                    data[h] = new binary_tree_node<ValueType>(temp[0].key, temp[0].value);
                    cursor = data[h];
                    binary_tree_node<ValueType> *insert;
                    for (i = 1; i < used; ++i) {
                        insert = new binary_tree_node<ValueType>(temp[i].key, temp[i].value);
                        cursor->set_left(insert);
                        cursor = cursor->left();
                    }
                }
            }
        }
    }
    
    template <class ValueType>
    ValueType table<ValueType>::get(size_t key) const {
        
        // hash to index
        size_t h = hash(key);
        
        // find # of stuff in hashed index
        size_t count = tree_size(data[h]);
        
        // declare found to store value that is found with key
        ValueType found = 0;
        
        // if index is empty return found with -300
        if (count == 0) {
            found = -300;
            return found;
        }
        
        // inorder traversal of tree/linked list, finding value in found
        binary_tree_node<ValueType> *cursor = data[h];
        inorder_value(cursor, key, found);
        
        // if key is not found return found with -300
        if (found == 0) {
            found = -300;
            return found;
        }
        
        // if key is found return found with value
        return found;
    }
    
    template <class ValueType>
    void table<ValueType>::rehash() {
        
        // convert all trees to linked lists before continuing and find total number of nodes
        size_t i;
        size_t total_nodes = 0;
        size_t count;
        binary_tree_node<ValueType> *cursor;
        for (i = 0; i < SIZE; ++i) {
            count = tree_size(data[i]);
            total_nodes += count;
            if (count >= 6) {
                // copy tree keys,values into array
                cursor = data[i];
                kv<ValueType> temp[count];
                inorder_copy(cursor, temp, 0);    // <-- fills tree values in temp using inorder method
                // put array elements into linked list
                delete data[i];
                data[i] = new binary_tree_node<ValueType>(temp[0].key, temp[0].value);
                cursor = data[i];
                binary_tree_node<ValueType> *insert;
                size_t k;
                for (k = 1; k < count; ++k) {
                    insert = new binary_tree_node<ValueType>(temp[i].key, temp[i].value);
                    cursor->set_left(insert);
                    cursor = cursor->left();
                }
            }
        }
        
        // declare array to store all nodes
        kv<ValueType> all_nodes[total_nodes];
        
        // declare variables to iterate through array
        size_t j = 0;
        
        // put all linked list values in array
        for (i = 0; i < SIZE; ++i) {
            for (cursor = data[i]; cursor != NULL; cursor = cursor->left()) {
                all_nodes[j].key = cursor->key();
                all_nodes[j].value = cursor->value();
                ++j;
            }
        }
        
        // clear hash table
        for (i = 0; i < SIZE; ++i) {
            tree_clear(data[i]);
        }
        
        // increase table size
        table_size = table_size * 2;
        
        // reset array iterator variable and rehash all keys to insert into new hash table
        binary_tree_node<ValueType> *insert_ptr;
        j = 0;
        for (i = 0; i < total_nodes; ++i) {
            size_t nh = hash(all_nodes[j].key);
            for (cursor = data[nh]; cursor != NULL; cursor = cursor->left()) {
                if (cursor->left() == NULL)
                    break;
            }
            insert_ptr = new binary_tree_node<ValueType>(all_nodes[j].key, all_nodes[j].value);
            cursor->set_left(insert_ptr);
            ++j;
        }
        
        // convert linked lists back into binary search trees if necessary
        for (i = 0; i < SIZE; ++i) {
            size_t count2 = tree_size(data[i]);
            if (count2 >= 8) {
                kv<ValueType> temp[count2];
                size_t i = 0;
                for (cursor = data[i]; cursor != NULL; cursor = cursor->left()) {
                    temp[i].key = cursor->key();
                    temp[i].value = cursor->value();
                }
                
                // sort array
                selectionsort(temp, count2);
                
                // convert sorted array into binary search tree
                int start = 0;
                int end = int(count2 - 1);
                binary_tree_node<ValueType> *new_tree = createBST(temp, start, end);
                
                // replace linked list with tree in data[h]
                delete data[i];
                data[i] = new_tree;
            }
        }
    }
    
    template <class ValueType>
    size_t table<ValueType>::hash(size_t key) const {
        return (key % table_size);
    }
    
}

#endif /* table_h */
