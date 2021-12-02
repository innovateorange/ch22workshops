#include "cakeList.hpp"
#include <iostream>
cakeList::cakeList(std::vector<cake*> in){
    head = new node();
    tail = new node();
    head->prev = NULL;
    tail->next = NULL;
    int maxDeadLine = -1;
    for(int i = 0; i < in.size(); i++){
        if(in[i]->deadLine > maxDeadLine){
            maxDeadLine = in[i]->deadLine;
        }

    }
    int i = 0;
    node* previous = head;
    while(i <= maxDeadLine){
        node* nextNode = new node();
        previous->next = nextNode;
        nextNode->prev = previous;

        for(int j = 0; j < in.size(); j++){
            if(in[j]->deadLine==i){
                nextNode->myPQ.push(in[j]);
            }
        }
        previous = nextNode;
       
        i++;
    }
    tail->prev = previous;
    previous->next = tail;
    n = maxDeadLine;

}

std::vector<cake*> cakeList::getCakes(){
    std::vector<cake*> schedule;
    node* cur = head->next;
    
    int d = 0;
    while(d <= n){
        if(cur->myPQ.size() != 0){
            schedule.push_back(cur->myPQ.top());
            cur->myPQ.pop();
            if(cur->myPQ.size() != 0){
                cake* nextCake = cur->myPQ.top();
                float nextProfit = nextCake->profit;
                float worstProfit = nextProfit - 1;
            
                while(worstProfit < nextProfit && cur->myPQ.size() > 0){
                    int worstIndex = -1;
                    worstProfit = nextProfit + 1;
                    for(int i = 0 ; i < schedule.size() - 1; i++){
                        if (schedule[i]->profit < worstProfit){
                        worstProfit = schedule[i]->profit;
                        worstIndex = i;
                        }
                    }
                    if(worstProfit < nextProfit){
                        schedule[worstIndex] = nextCake;
                        cur->myPQ.pop();
                        if(cur->myPQ.size() != 0){
                            nextCake = cur->myPQ.top();
                            nextProfit = nextCake->profit;
                        }
                        
                    } 
                }
            }
        }
        
        cur = cur->next;
        d++;

    }
    std::cout << "The cakes to be baked are as follows: " << std::endl;
    for(int i = 0; i < schedule.size(); i++){
        std::cout << "The cake: " << schedule[i]->name << " is baked by: " << schedule[i]->deadLine << " for a profit of: "
             << schedule[i]->profit << std::endl;
  
    }
    return schedule;
}