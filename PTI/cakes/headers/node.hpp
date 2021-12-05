#ifndef NODE_H
#define NODE_H
#include <vector>
#include "cake.hpp"
#include<queue>

class Compare
{
public:
    bool operator() (cake* a, cake* b)
    {
        return a->profit < b->profit;
    }
};
class node{
public:
    node();
    node* next;
    node* prev;
    int test;
    std::priority_queue<cake*, std::vector<cake*>, Compare>  myPQ;
};

#endif