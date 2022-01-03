#ifndef STREE_HEADER
#define STREE_HEADER
#include "node.hpp"
#include <vector>
class stree{
public:
    stree(int depth);
    node* root;
    bool isOkay();
    void playTree(int num_nodes);
private:    
    
    void build_tree_helper(node* cur_root, int cur_depth, int max_depth);

    std::vector<node*> all_nodes_in_tree_in_order;
    int tree_depth;
    int total_nodes;
};






#endif