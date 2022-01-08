#include "node.hpp"
#include <cstdlib>




node::node(){
    my_p_val_with_below = my_p_val = rand() / (double)RAND_MAX; //set p-val and p-val below
    my_left_child = my_right_child = my_parent = NULL; //set ptrs
    my_depth = 0; //set depth
    is_dirty = false; //set dirty flag
}


/*this is unused. safe to ignore but may be helpful for understanding the consistency of each node in the tree*/

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

void node::crawl(){
    if(my_left_child){
        my_p_val_with_below = my_p_val + my_left_child->my_p_val_with_below + my_right_child->my_p_val_with_below;
    } else{
        my_p_val_with_below = my_p_val;
    }
    
    is_dirty = false;
    if(my_parent){
        my_parent->crawl();
    }
    
    
}

void node::update(){
    my_p_val_with_below = my_left_child ?  my_p_val + my_right_child->my_p_val_with_below + my_left_child->my_p_val_with_below:
                                           my_p_val;
    is_dirty = false;
}
