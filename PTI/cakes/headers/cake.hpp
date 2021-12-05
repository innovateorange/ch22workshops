#ifndef CAKE_H
#define CAKE_H
#include<string>

class cake{
public:
    std::string name;
    cake(std::string name, float profit, int deadLine);
    
    float profit;
    int deadLine;
};

#endif