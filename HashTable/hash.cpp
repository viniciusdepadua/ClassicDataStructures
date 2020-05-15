#include "hash.h"


Hash::Hash(int tablesize, int (*hf) (std::string) ) {
    _table.resize (tablesize);
    _hash_func = hf; 
}

int Hash::add(std::string str, int &collisions) { 
    
   bool contain = Hash::contains(str, collisions);
   if(!contain)
   {
       ( _table[ Hash::hash (str) ] ) . push_front (str);
   }
    return !contain;
    
}

int Hash::remove(std::string str, int &collisions) { 
    
    bool contain = Hash::contains(str, collisions);
    int index=Hash::hash(str);
    if(contain)
    {
        _table[index].remove(str);
    }   
    return contain;
    
}


int Hash::hash(std::string str) { 
    int hash = (*_hash_func)(str);
    return hash;
}
    
int Hash::contains(std::string str, int &collisions) { 
    collisions=0;
    int index = Hash::hash(str);
    bool contain = false;
    if(!(_table[index].empty()))
    {   
    
        for (auto i = _table[index].begin(); i != _table[index].end()&&!contain; i++)
        {
            if (*i == str)
            {
                contain = true;
            }
                collisions++;

         }
    }
    return contain;
}


int Hash::worst_case() {

    int largest = -1;
    for(int i = 0; i < _table.size(); i++)
    {
        int size=0;
        for( auto j = _table [i].begin() ; j != _table[i].end() ; j++) 
        {
            size++;
        } 
        if(size>largest)
        {
            largest = size;
        }
    }
    return largest;
    
}

int Hash::size() {
    int size=0;
    for(int i = 0; i < _table.size(); i++)
    {
        for( auto j = _table [i].begin() ; j != _table[i].end() ; j++) 
        {
            size++;
        } 
    }
    return size;
}

