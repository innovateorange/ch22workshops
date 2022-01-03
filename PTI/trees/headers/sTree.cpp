#include "sTree.hpp"
#include <iostream>



stree::stree(int depth) 
{
    tree_depth = depth;
    root = new node();
    
    build_tree_helper(root, 0, tree_depth);
    total_nodes = all_nodes_in_tree_in_order.size();
    std::cout << isOkay() << std::endl;
}

void stree::build_tree_helper(node* cur_root, int cur_depth, int max_depth){
   
    all_nodes_in_tree_in_order.push_back(cur_root);
    
    cur_root->my_depth = cur_depth;
    if(cur_depth >= max_depth){
        return;
    }
    
    node* l = new node();
    node* r = new node();
    
    cur_root->my_left_child = l;
    cur_root->my_right_child = r;
    cur_root->my_left_child->my_parent = cur_root;
    cur_root->my_right_child->my_parent = cur_root;
    build_tree_helper(l, cur_depth+1, max_depth);
    build_tree_helper(r, cur_depth+1, max_depth);
    cur_root->my_p_val_with_below += l->my_p_val_with_below + r->my_p_val_with_below;
    
}

void stree::playTree(int num_nodes){
    
    std::vector<std::vector<node*>>  modified_nodes(tree_depth);
    for(int i = 0; i < num_nodes; i++){
        node* random_node = all_nodes_in_tree_in_order[rand() % total_nodes];
        random_node->my_p_val = rand() / (double) RAND_MAX;
        if(random_node->my_left_child){
            random_node->my_p_val_with_below = random_node->my_p_val + random_node->my_left_child->my_p_val_with_below + random_node->my_right_child->my_p_val_with_below;
        } else{
            random_node->my_p_val_with_below = random_node->my_p_val;
        }
        if(random_node->my_parent){
            if(!random_node->my_parent->is_dirty){
                modified_nodes[random_node->my_parent->my_depth].push_back(random_node->my_parent);
                random_node->my_parent->is_dirty = true;
            
            }
        }
        
    }
    
    for(int i = tree_depth ; i >= 0; i--){
        for(auto& dirty_node: modified_nodes[i]){
            dirty_node->my_p_val_with_below = dirty_node->my_p_val + dirty_node->my_left_child->my_p_val_with_below + dirty_node->my_right_child->my_p_val_with_below;
            if(i != 0 && !dirty_node->my_parent->is_dirty){
                modified_nodes[i-1].push_back(dirty_node->my_parent);
                dirty_node->my_parent->is_dirty = true;
            }
        }
    }

    std::cout << isOkay() << std::endl;


}


bool isOkayHelper(node* root){
    if(root->my_left_child){
        double diff = abs(root->my_p_val_with_below - (root->my_p_val + root->my_left_child->my_p_val_with_below + root->my_right_child->my_p_val_with_below));
        bool ret = diff < .0001; 
            if(!ret){
                std::cout << "ERROR In Tree check at " << root->my_depth << std::endl;
                std::cout << "GOT: " << root->my_p_val_with_below << std::endl;
                std::cout << "EXPECTED: " << root->my_p_val + root->my_left_child->my_p_val_with_below + root->my_right_child->my_p_val_with_below << std::endl;
                std::cout << "DIFF: " << diff << std::endl;
            }
            return ret &&
            isOkayHelper(root->my_right_child) && isOkayHelper(root->my_left_child);;
    } else{
        double diff = abs(root->my_p_val_with_below - root->my_p_val);
        bool ret = diff < 1e-3; 
       if(!ret){
           std::cout << "ERROR In Tree check at " << root->my_depth << std::endl;
           std::cout << "GOT: " << root->my_p_val_with_below << std::endl;
           std::cout << "EXPECTED: " << root->my_p_val << std::endl;
           std::cout << "DIFF: " << diff << std::endl;
           std::cout << "IN LEAVES" << std::endl;
       }
       return ret;
    }
}


bool stree::isOkay(){
    return isOkayHelper(root);
}

