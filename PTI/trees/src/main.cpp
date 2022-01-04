#include "../headers/sTree.hpp"
#include<iostream>

struct run_time_vars{
    int depth;
    int num_mods;
};

void parse_args(int argc, char* const  argv[], struct run_time_vars* rtv);

int main(int argc, char* argv[]){

    struct run_time_vars* rtv = (struct run_time_vars*) malloc(sizeof(*rtv)); //Allocate memory for run-time-variables in a struct
    parse_args(argc, argv, rtv);                                              //Parse the run-time commands
    stree tree(rtv->depth);                                                   //Create an initial tree
    tree.playTree(rtv->num_mods);                                             //Modify the tree randomly and update
    tree.naiveCrawl(rtv->num_mods);

    
}



/* Argument parsing function
    Self explanatory   */
void parse_args(int argc, char* const  argv[], struct run_time_vars* rtv){
    if(argc != 3){
        std::cout << "ERR expected fmt: <exec> <depth> <num_mods>" << std::endl;
        exit(1);
    }
    
    rtv->depth = atoi(argv[1]);
    rtv->num_mods = atoi(argv[2]);
}