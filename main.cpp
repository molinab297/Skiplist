#include <iostream>
#include <iomanip>
#include "Skiplist.h"
using namespace std;



int main() {

    srand (time(NULL));
    Skiplist<int> skiplist;
    skiplist.Insert(5);
    skiplist.Insert(4);
    skiplist.Insert(10);
    skiplist.Print();





    return 0;
}