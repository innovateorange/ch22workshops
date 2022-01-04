#ifndef NODE_HEADER
#define NODE_HEADER

/* Node class
    desc: Every node knows who its two children are and who its parent is
          Every node has a p-val and a p-val-with-below 
          p-val is a random value [0,1) and p-val-below is the sum of p-val with the 
          p-val belows of the two children nodes

          depth is the depth the node is in the tree (0 is the root)
          is-dirty means the node is in the modified vector (see stree::playTree)
*/

class node{
public:
    node();
    node(node* l, node* r);
    void crawl();
    double my_p_val;
    double my_p_val_with_below;
    node* my_left_child;
    node* my_right_child;
    node* my_parent;
    int my_depth;
    bool is_dirty;    

};

#endif