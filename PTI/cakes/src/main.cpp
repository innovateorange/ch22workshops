#include "../headers/cakeList.hpp"
#include<iostream>
int main(){
    cake* cake1b= new cake("cake1b", 5, 0);
    cake* cake1 = new cake("cake1", 13, 0);
    cake* cake2 = new cake("cake2", 11, 1);
    cake* cake3 = new cake("cake3", 12, 2);
    cake* cake3b = new cake("cake3b", 15, 2);
    cake* cake5 = new cake("cake5", 1, 4);

    std::vector<cake*> listOfCakes;
    listOfCakes.push_back(cake1); listOfCakes.push_back(cake2); listOfCakes.push_back(cake3); listOfCakes.push_back(cake1b);
    listOfCakes.push_back(cake3b); listOfCakes.push_back(cake5);
    cakeList cl(listOfCakes);
  
    auto k = cl.getCakes();
}