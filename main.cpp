#include <iostream>
#include "Skiplist.h"
using namespace std;



int main() {

    Skiplist<int> skiplist;
    skiplist.Insert(5);
    skiplist.Insert(6);
    skiplist.Insert(4);
    skiplist.Print();



    return 0;
}