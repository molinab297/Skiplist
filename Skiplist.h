//
// Created by Blake Molina on 5/31/17.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H
#include "SkiplistNode.h"
#include <stdlib.h>
#include <time.h>
#include <iomanip>

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
    unsigned int height;      // number of levels on skip list

    void PrintLinkedList(const SkiplistNode<int>*curr) const; // Helper function to Print()
    void AdjustHeight(unsigned int num_times_to_insert);
    void InsertIntoLinkedList(SkiplistNode<type>*&current, type data); // Helper function to Insert(type data)
    int  FlipCoin(); // Generates a 1 (for heads) or a 0 (for tails). See Insert(type data)

public:
    Skiplist();
    ~Skiplist();

    void Insert(type data);
    void Remove(type data);
    bool IsEmpty() const;
    int  Height() const;
    void Print() const;

    SkiplistNode<type>* Find(type key) const;
    const SkiplistNode<type>* Head() const;
    const SkiplistNode<type>* Front() const;
};


/*****************************************************************************
 * Skiplist Class Implementation
 *****************************************************************************/
template <class type>
Skiplist<type>::Skiplist() {

    this->height = 1;

    // Create initial sentinel nodes
    SkiplistNode<type>*level_0_sentinel_node = new SkiplistNode<type>;
    SkiplistNode<type>*level_1_sentinel_node = new SkiplistNode<type>;

    // Set sentinel node values to 'infinity'. (in this case, max int size)
    level_0_sentinel_node->SetData(INT_MAX);
    level_1_sentinel_node->SetData(INT_MAX);

    // Set initial links
    level_1_sentinel_node->SetDownLink(level_0_sentinel_node);
    this->head  = level_1_sentinel_node;
    this->front = level_0_sentinel_node;

    // For randomness in insertion method
    srand(time(NULL));
}

template <class type>
Skiplist<type>::~Skiplist(){
    if(!this->IsEmpty()){
        // Delete nodes on each level
        for(int i = height; i >= 0; i--){
            SkiplistNode<type>*current = this->head;
            current = current->GetNext();
            while(current){
                SkiplistNode<type>*temp = current->GetNext();
                current->SetNextLink(nullptr);
                current->SetDownLink(nullptr);
                delete current;
                current = temp;
            }
            // move head down one level and remove sentinel node
            SkiplistNode<type>*temp = this->head;
            head->SetNextLink(nullptr);
            head = head->GetDown();
            temp->SetDownLink(nullptr);
            delete temp;
        }
    }
}

// Performs a normal, ascending ordered, linked list insertion. This is a helper function
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

    if(!current->GetNext()) {
        current->SetNextLink(new_node);
        new_node->SetPrevLink(current);
    }
    else{
        new_node->SetNextLink(current->GetNext());
        current->GetNext()->SetPrevLink(new_node);
        current->SetNextLink(new_node);
        new_node->SetPrevLink(current);
    }
}

// Inserts 'data' into the skip list. The number of times that data is inserted is dependent
// upon how many heads are flipped in a row (See FlipCoin()).
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
    if(!current->GetNext()) {
        current->SetNextLink(new_node);
        new_node->SetPrevLink(current);
    }
    else{
        new_node->SetNextLink(current->GetNext());
        if(current->GetNext())
            current->GetNext()->SetPrevLink(new_node);
        current->SetNextLink(new_node);
        new_node->SetPrevLink(current);
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

// Removes all elements with the key 'data' from the skip list
template <class type>
void Skiplist<type>::Remove(type data){
    SkiplistNode<type>*current = this->Find(data);
    // If element does not exist, return.
    if(!current)
        return;

    // Traverse down skip list and remove each node with data
    while(current){

        SkiplistNode<type>*prev_to_current = current->GetPrev();
        SkiplistNode<type>*temp = current;
        prev_to_current->SetNextLink(current->GetNext());
        current->SetPrevLink(nullptr);

        if(current->GetNext())
            current->GetNext()->SetPrevLink(prev_to_current);
        // decrease height if necessary
        else if(prev_to_current->GetData() == INT_MAX && !current->GetNext() && this->height != 1){
            SkiplistNode<type>*temp2 = head;
            head = head->GetDown();
            temp2->SetDownLink(nullptr);
            delete temp2;
            this->height--;
        }

        current->SetNextLink(nullptr);
        current = current->GetDown();
        temp->SetDownLink(nullptr);
        delete temp;
    }

}

// Returns true if the skip list is empty
template <class type>
bool Skiplist<type>::IsEmpty() const{ return (this->head->GetDown()->GetNext() == nullptr); }

// Returns a pointer to the first node that contains 'key'. If the
// node does not exist or the skip list is empty, this function
// returns a null pointer.
template <class type>
SkiplistNode<type>* Skiplist<type>::Find(type key) const{
    if(this->IsEmpty())
        return nullptr;

    SkiplistNode<type>*current = this->head;
    bool found = false;
    while(current && !found){
        // Move down to see if we can move through another express lane
        if(current->GetNext() && current->GetNext()->GetData() > key)
            current = current->GetDown();
        // Move along express lane if the value to the right is less than key
        else if(current->GetNext() && current->GetNext()->GetData() < key)
            current = current->GetNext();
        // If the key has been found, exit loop and return pointer to node
        else if(current->GetNext() && current->GetNext()->GetData() == key)
            found = true;
        // By default move down to next express lane
        else
            current = current->GetDown();
    }

    if(found)
        return current->GetNext();
    return nullptr;
}


// Returns read-only pointer to first sentinel node on the skip list
template <class type>
const SkiplistNode<type>* Skiplist<type>::Head() const{
    if(!IsEmpty())
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
            new_sentinel_node->SetData(INT_MAX);
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
        std::cout << std::setfill('-') << std::setw(5);
        std::cout << ">" << curr->GetData();
        curr = curr->GetNext();
    }
}

// Prints a skip list in skip list format.
template <class type>
void Skiplist<type>::Print() const{
    SkiplistNode<type>*curr = this->head;
    unsigned int level = this->height;
    for(int i = 0; i < height + 1; i++){
        std::cout << "Level " << level - i << " ";
        PrintLinkedList(curr);
        std::cout << std::endl;
        curr = curr->GetDown();
    }
}



#endif //SKIPLIST_SKIPLIST_H
