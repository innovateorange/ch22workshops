#ifndef CAKELIST_H
#define CAKELIST_H
#include<vector>
#include<algorithm>
#include <queue>
#include "cake.hpp"
#include "node.hpp"
class cakeList{

public:
    cakeList(std::vector<cake*> );
    std::vector<cake*> getCakes();

    node* head;
    node* tail;
    int n;

};

#endif