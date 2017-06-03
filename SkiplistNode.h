//
// Created by Blake Molina on 5/31/17.
//

#ifndef SKIPLIST_SKIPLISTNODE_H
#define SKIPLIST_SKIPLISTNODE_H

/*************************************************************************
 * CLASS SkiplistNode
 *
 * PARAMETERS (optional):
 *
 *  SkiplistNode<type> *next   - a pointer to the right node
 *  SkiplistNode<type> *prev   - a pointer to the left node
 *  SkiplistNode<type> *down   - a pointer to the below node
 *  type data                  - Data element held by node
 *
 * Represents a single node in a Skip-List data structure. This class
 * provides functionality to access each nodes pointers to other nodes.
 ************************************************************************/
template <class type>
class SkiplistNode{
private:
    SkiplistNode<type> *next, *down, *prev;
    type data;
public:
    SkiplistNode();
    ~SkiplistNode();

    void SetNextLink(SkiplistNode<type> *next);
    void SetDownLink(SkiplistNode<type> *down);
    void SetPrevLink(SkiplistNode<type> *prev);
    void SetData(type data);
    SkiplistNode<type> *GetNext() const;
    SkiplistNode<type> *GetDown() const;
    SkiplistNode<type> *GetPrev() const;
    type GetData()                const;
};

// Class Implementation
template <class type>
SkiplistNode<type>::SkiplistNode() {
    this->next = nullptr;
    this->down = nullptr;
}

template <class type>
SkiplistNode<type>::~SkiplistNode() { }

template <class type>
void SkiplistNode<type>::SetNextLink(SkiplistNode *next){ this->next = next; }

template <class type>
void SkiplistNode<type>::SetDownLink(SkiplistNode *down){ this->down = down; }

template <class type>
void SkiplistNode<type>::SetPrevLink(SkiplistNode<type> *prev){this->prev = prev;}

template <class type>
void SkiplistNode<type>::SetData(type data){ this->data = data; }

template <class type>
SkiplistNode<type>* SkiplistNode<type>::GetNext() const{ return next; }

template <class type>
SkiplistNode<type>* SkiplistNode<type>::GetPrev() const{ return prev; }

template <class type>
SkiplistNode<type>* SkiplistNode<type>::GetDown() const{ return down; }

template <class type>
type SkiplistNode<type>::GetData() const{ return data; }

#endif //SKIPLIST_SKIPLISTNODE_H
