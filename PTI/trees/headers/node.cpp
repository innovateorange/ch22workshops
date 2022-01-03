#include "node.hpp"
#include <cstdlib>

node::node(){
    my_p_val_with_below = my_p_val = rand() / (double)RAND_MAX;
    my_left_child = my_right_child = my_parent = NULL;
    my_depth = 0;
    is_dirty = false;
}

node::node(node* l, node* r){
    my_right_child = new node();
    my_left_child = new node();
    my_parent = NULL;

    my_right_child->my_p_val = r->my_p_val;
    my_right_child->my_p_val_with_below = r->my_p_val_with_below;
    my_right_child->is_dirty = r->is_dirty;
    my_right_child->my_depth = r->my_depth;


    my_left_child->my_p_val = l->my_p_val;
    my_left_child->my_p_val_with_below = l->my_p_val_with_below;
    my_left_child->is_dirty = l->is_dirty;
    my_right_child->my_depth = l->my_depth;

}
