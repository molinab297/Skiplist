#include "SkiplistNode.h"

template <class type>
SkiplistNode<type>::SkiplistNode() {
    this->next = nullptr;
    this->prev = nullptr;
    this->up   = nullptr;
    this->down = nullptr;
}

template <class type>
SkiplistNode<type>::~SkiplistNode() {
    // come back to this
}

template <class type>
void SkiplistNode<type>::SetLinks(SkiplistNode<type>*next, SkiplistNode<type>*prev,
              SkiplistNode<type>*up, SkiplistNode<type>*down){
    this->next = next;
    this->prev = prev;
    this->up   = up;
    this->down = down;
}

template <class type>
void SkiplistNode<type>::SetNextLink(SkiplistNode *next){
    this->next = next;
}

template <class type>
void SkiplistNode<type>::SetPrevLink(SkiplistNode *prev){
    this->prev = prev;
}

template <class type>
void SkiplistNode<type>::SetUpLink(SkiplistNode *up){
    this->up = up;
}

template <class type>
void SkiplistNode<type>::SetDownLink(SkiplistNode *down){
    this->down = down;
}

template <class type>
void SkiplistNode<type>::SetData(type data){
    this->data = data;
}

template <class type>
SkiplistNode<type>* SkiplistNode<type>::GetNext() const{
    return next;
}

template <class type>
SkiplistNode<type>* SkiplistNode<type>::GetPrev() const{
    return prev;
}

template <class type>
SkiplistNode<type>* SkiplistNode<type>::GetUp() const{
    return up;
}

template <class type>
SkiplistNode<type>* SkiplistNode<type>::GetDown() const{
    return down;
}

template <class type>
type SkiplistNode<type>::GetData() const{
    return data;
}