#include <iostream>

using namespace std;
struct node {
    int data;
    node* p_node_right;
    node* p_node_left;
};

node* insert(node* p_tree, int key) {

    if (p_tree == nullptr) {
        node* new_node = new node;
        new_node->data = key;
        new_node->p_node_left = nullptr;
        new_node->p_node_right = nullptr;

        return new_node;
    }

    if (key < p_tree->data) {
        p_tree->p_node_left = insert(p_tree-> p_node_left, key);

    } else {
        p_tree->p_node_right = insert(p_tree-> p_node_right, key);
    }

    return p_tree;
}

void display_nodes(node* p_tree, node* prev = nullptr) {
    if (p_tree == nullptr) return;

    if (p_tree->p_node_left == nullptr && p_tree->p_node_right == nullptr) {
        cout << p_tree->data << "\n";
        return;
    }

        display_nodes(p_tree->p_node_left, prev);

        cout << p_tree->data << "\n";

        display_nodes(p_tree->p_node_right, prev);
   
}


void count_nodes(node* p_tree, int &count) {
    if (p_tree == nullptr) return;
   
    count++;
    count_nodes(p_tree->p_node_left, count);
    count_nodes(p_tree->p_node_right, count);
}


int isBalanced(node* p_tree) {
    if (p_tree == nullptr) {
        return 0;
    }

    int hleft = isBalanced(p_tree->p_node_left);
    int hright = isBalanced(p_tree->p_node_right);

    if (hleft == -1 || hright == -1 || abs(hright - hleft) > 1) {
        return -1;
    }

    return max(hright, hleft) + 1;
}

    
    
int main() {

   node* root = nullptr;

    root = insert(root, 3);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 7);
    root = insert(root, 5);

    int total = 0;
    display_nodes(root);
    cout << isBalanced(root);
    // count_nodes(root, total);
    // cout << total;
    return 0;
}

