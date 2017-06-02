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
 * PARAMETERS (optional):
 *
 *
 *
 * Represents a 'tree-like' structure that holds linked lists to SkiplistNodes.
 * (See SkiplistNode.h/.cpp).
 *****************************************************************************/
 template <class type>
class Skiplist {

private:
    SkiplistNode<type>*head;
    SkiplistNode<type>*tail;
    unsigned int level_count;

    void AdjustHeight(unsigned int num_times_to_insert);
    void InsertIntoLinkedList(SkiplistNode<type>*&current, type data);
    int FlipCoin();

public:
    Skiplist();
    ~Skiplist();

    void Insert(type data);
    void Remove(type data);
    bool IsEmpty() const;
    int  GetLevelCount() const;
    SkiplistNode<type>* Find(type data);

};


#endif //SKIPLIST_SKIPLIST_H
