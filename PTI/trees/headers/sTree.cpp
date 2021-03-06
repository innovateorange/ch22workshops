#include "sTree.hpp"
#include <unordered_set>
#include <iostream>
#include <chrono>
/* Lone Constructor */
stree::stree(int depth) 
{
    tree_depth = depth; //Fix the tree-depth
    root = new node();  //Init the root
    
    build_tree_helper(root, 0, tree_depth); //build the tree
    total_nodes = all_nodes_in_tree_in_order.size(); //get the size of the tree
    std::cout << isOkay() << std::endl;     //check if the tree is feeling okay
}

/* Tree construction algorithm.
    Ordering is root, left-child, right-child */
void stree::build_tree_helper(node* cur_root, int cur_depth, int max_depth){
   
    all_nodes_in_tree_in_order.push_back(cur_root); //Add node to the list of existing nodes
    
    cur_root->my_depth = cur_depth; //Set depth
    if(cur_depth >= max_depth){ //Ahh don't go too deep
        return;                 //better go back to the surface
    }
    
    node* l = new node(); //l-child
    node* r = new node(); //r-child
    
    cur_root->my_left_child = l; //set the l-child
    cur_root->my_right_child = r; //set the r-child
    cur_root->my_left_child->my_parent = cur_root; //set the parent
    cur_root->my_right_child->my_parent = cur_root; //set the parent
    build_tree_helper(l, cur_depth+1, max_depth); //build the tree
    build_tree_helper(r, cur_depth+1, max_depth); //build the tree
    cur_root->my_p_val_with_below += l->my_p_val_with_below + r->my_p_val_with_below; //set p-val-with-below
    
}
/* playTree
    desc: Play tree samples <num_nodes> randomly from all_nodes_in_tree_in_order and modifies their p-vals
          this breaks the p-val:p-val-with-below relationship so we have to update the tree to be consistent
    
    algorithm:
        1. update the node which is modified by changing the p-val
        2. check if the node is a leaf and update the p-val below by summing the two children p-val-with-below with p-val
        3. check if the node is the root and place the parent (unless is root) in the modified_nodes vector
            3a. modified_nodes contains nodes which are made inconsistent by the tree-update algorithm
            3b. the i'th index of modified nodes contains all the nodes at the i'th depth which are inconsistent
        4. crawl up the tree by making consistent all nodes at the deepest layer.
*/
void stree::playTree(int num_nodes){
    
    std::chrono::high_resolution_clock clock;
    auto start = clock.now();
    std::vector<std::unordered_set<node*>> modified_nodes(tree_depth);
    for(int i = 0; i < num_nodes; i++){
        node* random_node = all_nodes_in_tree_in_order[rand() % total_nodes]; //randomly get node to modify
        random_node->my_p_val = rand() / (double) RAND_MAX;                   //new p-val
        random_node->update(); //update p-val-with-below
        
        if(random_node->my_parent){
            modified_nodes[random_node->my_parent->my_depth].insert(random_node->my_parent); //add parent to the modified-nodes 
            random_node->my_parent->is_dirty = true;    //set the parent's dirty flag to true
            
        }
        
    }
    
    for(int i = tree_depth-1; i > 0; i--){ //crawl upwards
        for(auto& dirty_node: modified_nodes[i]){
            dirty_node->update();
            modified_nodes[i-1].insert(dirty_node->my_parent);
            dirty_node->my_parent->is_dirty = true;
        }
    }

    root->update();
    auto end = clock.now();

    std::cout << "Update task finished in " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " microseconds" << std::endl;
    std::cout << isOkay() << std::endl; //see if tree is feeling okay


}
void stree::naiveCrawl(int num_nodes){
    std::chrono::high_resolution_clock clock;
    auto start = clock.now();
    std::vector<node*> modified_nodes;
    node* random_node;
    for(int i = 0; i < num_nodes; i++){
        random_node = all_nodes_in_tree_in_order[rand() % total_nodes]; //randomly get node to modify
                          
        if(!random_node->is_dirty){
            random_node->my_p_val = rand() / (double) RAND_MAX; //new p-val
            modified_nodes.push_back(random_node);
            random_node->is_dirty = true;
        }
    }
    
    for(auto& n: modified_nodes){
        n->crawl();
    }
    auto end = clock.now();

    std::cout << "Crawl task finished in " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " microseconds" << std::endl;
    std::cout << isOkay() << std::endl; //see if tree is feeling okay

}
/* Helper function to check tree consistency */
bool isOkayHelper(node* root){
    if(root->my_left_child){
        double diff = abs(root->my_p_val_with_below - (root->my_p_val + root->my_left_child->my_p_val_with_below + root->my_right_child->my_p_val_with_below));
        bool ret = diff < 1e-6; 
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
        bool ret = diff < 1e-6; 
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

