#include "node.hpp"
#include<iostream>
node::node(){
    prev = NULL;
    next = NULL;
    std::priority_queue<cake*, std::vector<cake*>, Compare>  myTPQ;
    myPQ = myTPQ;
    
}