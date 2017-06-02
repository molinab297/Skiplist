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
 *  SkiplistNode<type> *up     - a pointer to the above node
 *  SkiplistNode<type> *down   - a pointer to the below node
 *
 * Represents a single node in a Skip-List data structure. This class
 * provides functionality to access each nodes pointers to other nodes.
 ************************************************************************/
template <class type>
class SkiplistNode{
private:
    SkiplistNode<type> *next;
    SkiplistNode<type> *prev;
    SkiplistNode<type> *up;
    SkiplistNode<type> *down;
    type data;
public:
    SkiplistNode();
    ~SkiplistNode();

    void SetLinks(SkiplistNode<type>*next, SkiplistNode<type>*prev,
                   SkiplistNode<type>*up, SkiplistNode<type>*down);
    void SetNextLink(SkiplistNode<type> *next);
    void SetPrevLink(SkiplistNode<type> *prev);
    void SetUpLink(SkiplistNode<type> *up);
    void SetDownLink(SkiplistNode<type> *down);
    void SetData(type data);

    SkiplistNode<type> *GetNext() const;
    SkiplistNode<type> *GetPrev() const;
    SkiplistNode<type> *GetUp()   const;
    SkiplistNode<type> *GetDown() const;
    type GetData()                const;
};

#endif //SKIPLIST_SKIPLISTNODE_H
