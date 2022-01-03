#ifndef NODE_HEADER
#define NODE_HEADER


class node{
public:
    node();
    node(node* l, node* r);
    double my_p_val;
    double my_p_val_with_below;
    node* my_left_child;
    node* my_right_child;
    node* my_parent;
    int my_depth;
    bool is_dirty;    
};

#endif