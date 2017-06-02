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
    unsigned int height; // number of levels on skip list

    void PrintLinkedList(const SkiplistNode<int>*curr) const;
    void AdjustHeight(unsigned int num_times_to_insert);
    void InsertIntoLinkedList(SkiplistNode<type>*&current, type data);
    int  FlipCoin();

public:
    Skiplist();
    ~Skiplist();

    void Insert(type data);
    void Remove(type data);
    bool IsEmpty() const;
    int  Height() const;
    void Print() const;

    const SkiplistNode<type>* Find(type data) const;
    const SkiplistNode<type>* Head() const;
    const SkiplistNode<type>* Front() const;

};


// Class implementation
template <class type>
Skiplist<type>::Skiplist() {

    this->height = 1;

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
        if(current->GetNext()->GetData() > data)
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

    // Create and fill new node to be inserted
    SkiplistNode<type>*new_node = new SkiplistNode<type>;
    new_node->SetData(data);

    SkiplistNode<type>*current = this->head;
    unsigned int current_level = this->height;
    bool location_found        = false;

    // traverse left to right (and down the skip list if necessary) and finds the
    // correct location to insert the new node.
    while(!location_found){
        // If we are on the correct level where the new node needs to be inserted first
        if(current_level == num_times_to_insert){
            if(current->GetNext() && current->GetNext()->GetData() > data)
                    location_found = true;
            else if(current->GetNext() && current->GetNext()->GetData() <= data)
                    current = current->GetNext();
            else
                location_found = true;
        }
        else{
            if(current->GetNext() && current->GetNext()->GetData() <= data)
                    current = current->GetNext();
            // move down a level
            else{
                current = current->GetDown();
                current_level--;
            }
        }
    }

    // Insert first node
    if(!current->GetNext())
        current->SetNextLink(new_node);
    else{
        new_node->SetNextLink(current->GetNext());
        current->SetNextLink(new_node);
    }

    // Traverse the skip list level by level and create nodes for each level (if coin tosses were > 0)
    SkiplistNode<type>*temp = current->GetNext();
    for(unsigned int i = 0; i < num_times_to_insert; i++){
        current = current->GetDown();
        InsertIntoLinkedList(current, data); // performs a normal linked list insertion
        temp->SetDownLink(current->GetNext());
        temp = temp->GetDown();
    }

}

// Removes an element from the skip list
template <class type>
void Skiplist<type>::Remove(type data){

}

// Returns true if the skip list is empty
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

// Helper function to Insert(Type data)
template <class type>
int Skiplist<type>::FlipCoin(){ ;
    return rand() % 2;
}

// Increases the height of a skip list
template <class type>
void Skiplist<type>::AdjustHeight(unsigned int num_times_to_insert) {
    if(num_times_to_insert >= height){
        unsigned int count = this->height;
        for(unsigned int i = count; i < num_times_to_insert+1; i++){
            SkiplistNode<type>*new_sentinel_node = new SkiplistNode<type>;
            SkiplistNode<type>*temp = this->head;
            this->head = new_sentinel_node;
            this->head->SetDownLink(temp);
            this->height++;
        }
    }
}

// Returns height of skip list
template <class type>
int Skiplist<type>::Height() const{ return this->height; }

// Helper function to Print()
template <class type>
void Skiplist<type>::PrintLinkedList(const SkiplistNode<int>*curr) const{
    curr = curr->GetNext();
    while(curr){
        std::cout << std::setw(5 +curr->GetData()) << curr->GetData();
        curr = curr->GetNext();
    }
}

// Prints a skip list in skip list format.
template <class type>
void Skiplist<type>::Print() const{
    SkiplistNode<type>*curr = this->head;
    std::cout << "Sentinel --> \n";
    for(int i = 0; i < height + 1; i++){
        std::cout << "Sentinel --> ";
        PrintLinkedList(curr);
        std::cout << std::endl;
        curr = curr->GetDown();
    }
}



#endif //SKIPLIST_SKIPLIST_H
