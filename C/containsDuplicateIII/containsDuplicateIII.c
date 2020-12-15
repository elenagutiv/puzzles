#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
    int key;
    struct node *left, *right;
}Node;

Node *createNode(int key){
    Node *new_node = malloc(sizeof(Node)*1);
    new_node->key = key;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void inorder(Node* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    printf(" %d ", root->key);
    inorder(root->right);
}
void preorder(Node* root){
    if(root == NULL){
        return;
    }
    printf(" %d ", root->key);
    inorder(root->left);
    inorder(root->right);
}
void postorder(Node* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    inorder(root->right);
    printf(" %d ", root->key);

}

Node *insert(Node* root, int key){

    if(root == NULL){
        return createNode(key);
    }
    if(key > root->key){
        root->right = insert(root->right, key);

    }else if(key < root->key){
        root->left = insert(root->left, key);
    }
    return root;

}
Node* search(Node* root, int key){
    if(root == NULL || root->key == key){
        return root;
    }
    if(key > root->key){
        return search(root->right, key);
    }
    return search(root->left, key);
}

// int containsDuplicateAtDistanceTK(int *array, int arrayLength, int t, int k){

//     ht_t *hashTable = ht_create();
//     int i = 0, j = 0, l;
//     unsigned int value;
//     char key_minus[MAX_LENGTH_NUMBER+1], key_plus[MAX_LENGTH_NUMBER+1], key[MAX_LENGTH_NUMBER+1]; // counts the '\0'
//     for(; i < arrayLength; i++){

//     }
//     ht_free(hashTable);
//     return 0;
// }


int main(void) { 
   
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
 
    // print inoder traversal of the BST
    inorder(root);
    if(search(root, 20)){
        printf("%d\n",root->right->key);
    }else{
        printf("No está\n");
    }

  
  return 0;
    
}

// Complexity Analysis - Hash Table solution
// Time complexity : O(n). In the worst case, for each element in the array we are performing a
// get and/or a set operation, both of which take constant time (O(1)). Therefore, O(n).
// Space complexity: O(n). The space used by a hash table is linear with the number of elements in it

// Complexity Analysis - Sorting algortithm solution (not implemented here)
// Time complexity : O(n log(n)). Sorting is O(n log(n)) and sweeping is O(n). Therefore the time complexity
// is dominated by the sorting algorithm and therefore is O(n log(n))
// Space complexity: Space depends on the sorting implementation. In the case of 'heapsort' the 
// space complexity is O(1). 
// Space complexity: O(n). The space used by a hash table is linear with the number of elements in it