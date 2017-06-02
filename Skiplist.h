//
// Created by Blake Molina on 5/31/17.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include "SkiplistNode.h"
#include <stdlib.h>
#include <time.h>

/*****************************************************************************
 * CLASS Skiplist
 *
 * Represents a 'tree-like' structure that holds linked lists to skip list nodes.
 * (See SkiplistNode.h/.cpp).
 *
 * Data structure specs:
 * Algorithm    Average    Worst Case
 * Space        O(n)       O(nlog(n))
 * Search       O(log(n))  O(n)
 * Insert       O(log(n))  O(n)
 * Delete       O(log(n))  O(n)
 *****************************************************************************/
 template <class type>
class Skiplist {

private:
    SkiplistNode<type>*head;  // points to first sentinel node on skip list
    SkiplistNode<type>*front; // points to first non-sentinel element on skip list
    unsigned int level_count; // number of levels on skip list

    void AdjustHeight(unsigned int num_times_to_insert);
    void InsertIntoLinkedList(SkiplistNode<type>*&current, type data);
    int  FlipCoin();

public:
    Skiplist();
    ~Skiplist();

    void Insert(type data);
    void Remove(type data);
    bool IsEmpty() const;
    int  GetLevelCount() const;

    const SkiplistNode<type>* Find(type data) const;
    const SkiplistNode<type>* Head() const;
    const SkiplistNode<type>* Front() const;

};


#endif //SKIPLIST_SKIPLIST_H
