#ifndef LAB1_HASH_H
#define LAB1_HASH_H


#include <vector>
#include <forward_list>
#include <string>
#include <cassert>
#include <iostream>


class Hash {
    
public:
    
 
    Hash(int tablesize,int (*hf) (std::string) ) ;
    
    
    /**
     * \brief return the hash of a string (a integer from 0 to tablesize-1)
     * \par THIS FUNCTION COULD BE PRIVATE, BUT WE WANT IT TO BE TRANSPARENT
     */
    int hash(std::string str) ;
    
    /**
     * \brief checks if hashtable contains a string 
     * \par collisions: how many strings were acessed to determine if the string was aready in the hashtable
     * \return 1 if hashtable contains str, 0 otherwise.
     */
    int contains(std::string str, int &collisions);
    
    /**
     * \brief adds a string to the hashtable (repetitions are not allowed)
     * \par collisions: how many strings were acessed to determine if the string was aready in the hashtable
     * \returns 1 if string was not found and added; 0 if string was found and therefore nothing new was added.
     */
    int add(std::string str, int &collisions) ;
    
    /**
     * \brief the size of the largest list in the hashtable, i.e, the worst case for a search.
     * \par this is obviously O(n), as it has to check every list. This method is not usual, it is here  only for didactical purposes.
     */
    int worst_case();
    
    /**
     * \returns the total number of strings contained in the hash table.
     */
    int size();
    
    /**
     * \brief removes a string from the hashtable (repetitions are not allowed, so there is no need of searching for duplicates)
     * \par str: the string to be removed
     * \par collisions: how many strings were acessed to determine if the string was aready in the hashtable
     * \returns 1 if string was found and removed; 0 if string was not found
     */
    int remove(std::string str, int &collisions) ;
    

private:
    
    // note that I named the class attibutes with a '_' prefix (just a naming convention)
    
    int (*_hash_func) (std::string); /// function pointer
    
    /// nice teacher already tells you which stl classes to use
    std::vector<std::forward_list<std::string>> _table; /// vector of [single linked lists of [strings]]
    // and std::string is a specialized std::vector for char (it is not just std::vector<char>, it is a specialized subclass with specific string operations).
    // but it still could be said that _table is: 
    // vector of [single linked lists of [vector of char] ]
    

};//class



#endif
