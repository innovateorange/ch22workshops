#ifndef STREE_HEADER
#define STREE_HEADER
#include "node.hpp"
#include <vector>


class stree{
public:
    stree(int depth); //Lone constructor for this project
    node* root;       //All trees have roots
    bool isOkay();    //Consistency check for tree
    void playTree(int num_nodes); //Playground for tree updates
    void naiveCrawl(int num_nodes); //Naive crawl algorithm
private:    
    
    void build_tree_helper(node* cur_root, int cur_depth, int max_depth); //tree builder algorithm

    std::vector<node*> all_nodes_in_tree_in_order; //All nodes in tree in-order traversal
    int tree_depth; //true depth of tree
    int total_nodes; //length of all_nodes_in_tree_in_order
};






#endif