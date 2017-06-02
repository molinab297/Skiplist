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


// Class implementation
template <class type>
Skiplist<type>::Skiplist() {

    this->level_count = 1;

    // Create initial sentinel nodes
    SkiplistNode<type>*level_0_sentinel_node = new SkiplistNode<type>;
    SkiplistNode<type>*level_1_sentinel_node = new SkiplistNode<type>;
    level_1_sentinel_node->SetDownLink(level_0_sentinel_node);
    this->head  = level_1_sentinel_node;
    this->front = level_0_sentinel_node;
}

template <class type>
Skiplist<type>::~Skiplist(){
    // come back to this
}

// Performs a normal, ascended ordered, linked list insertion. This is a helper function
// to Insert(type data).
template <class type>
void Skiplist<type>::InsertIntoLinkedList(SkiplistNode<type>*&current, type data){

    // create and fill new node
    SkiplistNode<type>*new_node = new SkiplistNode<type>;
    new_node->SetData(data);

    // insert new node in proper location
    bool location_found = false;
    while(!location_found && current->GetNext()){
        if(current->GetNext() > new_node->GetData())
            location_found = true;
        else
            current = current->GetNext();
    }

    if(!current->GetNext())
        current->SetNextLink(new_node);
    else{
        new_node->SetNextLink(current->GetNext());
        current->SetNextLink(new_node);
    }

}

template <class type>
void Skiplist<type>::Insert(type data){

    // Flip coin to see how many times to insert 'data'
    unsigned int num_times_to_insert = 0;
    while(FlipCoin() != 0)
        num_times_to_insert++;

    // Adjust stack height of sentinel nodes if necessary (The stack of sentinels must always be one greater than level count)
    AdjustHeight(num_times_to_insert);

    // Create new node to be inserted
    SkiplistNode<type>*new_node = new SkiplistNode<type>;
    new_node->SetData(data);

    SkiplistNode<type>*current = this->head;
    unsigned int current_level = this->level_count;
    bool location_found = false;

    // traverse left to right (and down the skip list if necessary) and finds the
    // correct location to insert the new node.
    while(!location_found){
        // If we are on the correct level where the new node needs to be inserted first
        if(current_level == num_times_to_insert){
            if(current->GetNext()) {
                if (current->GetNext()->GetData() > data)
                    location_found = true;
                else
                    current = current->GetNext();
            }
            else
                location_found = true;
        }
        else{
            if(current->GetNext()) {
                if (current->GetNext() <= data)
                    current = current->GetNext();
            }
                // move down a level
            else{
                current = current->GetDown();
                current_level--;
            }
        }
    }

    if(!current->GetNext())
        current->SetNextLink(new_node);
    else{
        new_node->SetNextLink(current->GetNext());
        current->SetNextLink(new_node);
    }

    // Traverse down the skip list and create nodes for each level (if coin tosses were > 0)
    SkiplistNode<type>*temp = current->GetNext();
    for(unsigned int i = 0; i < num_times_to_insert; i++){
        current = current->GetDown();
        InsertIntoLinkedList(current, data); // performs a normal linked list insertion
        temp->SetDownLink(current->GetNext());
        temp = temp->GetDown();
    }

}

template <class type>
void Skiplist<type>::Remove(type data){

}

template <class type>
bool Skiplist<type>::IsEmpty() const{ return (this->head->GetDown()->GetNext() == nullptr); }

template <class type>
const SkiplistNode<type>* Skiplist<type>::Find(type data) const{

}


// Returns read-only pointer to first sentinel node on the skip list
template <class type>
const SkiplistNode<type>* Skiplist<type>::Head() const{
    if(head)
        return this->head;
    return nullptr;
}

// Returns read-only pointer to the first non-sentinel node on the skip list
template <class type>
const SkiplistNode<type>* Skiplist<type>::Front() const{
    if(this->front->GetNext())
        return this->front->GetNext();
    return nullptr;
}

template <class type>
int Skiplist<type>::FlipCoin(){
    srand (time(NULL));
    return rand() % 1 + 0;
}

template <class type>
void Skiplist<type>::AdjustHeight(unsigned int num_times_to_insert) {
    if(num_times_to_insert >= level_count){
        unsigned int count = this->level_count;
        for(unsigned int i = count; i <= num_times_to_insert; i++){
            SkiplistNode<type>*new_sentinel_node = new SkiplistNode<type>;
            SkiplistNode<type>*temp = this->head;
            this->head = new_sentinel_node;
            this->head->SetDownLink(temp);
            this->level_count++;
        }
    }
}

template <class type>
int Skiplist<type>::GetLevelCount() const{ return this->level_count; }



#endif //SKIPLIST_SKIPLIST_H
