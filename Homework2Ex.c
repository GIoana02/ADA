#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//
// Created by Ioana Grigoriu on 05.03.2023.
//
typedef struct tree{
    int data;
    struct tree* root;
     struct tree* left;
    struct tree* right;
}Node;

void inorder(struct tree* root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d  ", root->data);
        inorder(root->right);
    }
}

int height( Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = height(root->left);
        printf("\nFor %d we have: \n LeftH %d ", root->data, leftHeight);
        int rightHeight = height(root->right);
        printf("RightH %d, \n", rightHeight);
        if (leftHeight > rightHeight) {
            return (leftHeight + 1);
        } else {
            return (rightHeight + 1);
        }
    }
}

int isPerfectlyBalanced(Node* root) {
    if (root == NULL) {
        return 1;
    } else {
        //We will check firstly for
        int leftHeight = height(root->left);
        printf("\nThis is answer for %d - leftH: %d \n", root->data, leftHeight);
        int rightHeight = height(root->right);
        printf("\nThis is answer for %d - rightH:%d \n", root->data, rightHeight);
        if (abs(leftHeight - rightHeight) <= 1 && isPerfectlyBalanced(root->left) && isPerfectlyBalanced(root->right)) {
            return 1;
        } else {
            return 0;
        }
    }
}

Node *search(Node* root, int k){
    if(root==NULL){
        return 0;
    }

    if(root->data==k){
        return root;
    }
    Node *closest=root;
    if(k< root->data){
        Node *leftClosest= search(root->left,k);
        if(leftClosest && abs(leftClosest->data-k)< abs(closest->data-k)){
         //   printf("leftClosest: %d\n", leftClosest->data);
          //  printf("Closest: %d\n", closest->data);
            closest=leftClosest;

        }
    }
    else {
      //  printf("The Current Root to compare is %d\n", closest->data);
        Node *rightClosest = search(root->right, k);
        printf("The Closest Root is %d\n", closest->data);
        printf("\nThe Right closest we want to compare the key with is %d\n", rightClosest->data);
        printf("\nThe diffrence between  %d and %d is: %d\n", rightClosest->data, k, abs(rightClosest->data-k));
        printf("\nThe diffrence between  %d and %d is: %d\n", closest->data, k, abs(closest->data-k));
        if (rightClosest && abs(rightClosest->data - k) < abs(closest->data - k)) {
             printf("\nThe diffrence between  %d and  %d is: %d\n", rightClosest->data , k, abs(rightClosest->data-k));
             printf("\nThe diffrence between  %d and  %d is: %d\n", closest->data, k, abs(closest->data-k));
            closest = rightClosest;
        }
    }
    return closest;
}

Node *insert(Node* root, int value){
    if (root==NULL){
        Node *new_node=malloc(sizeof(Node));
        new_node->data=value;
        new_node->left=NULL;
        new_node->right=NULL;
        return new_node;
    }
    else if(value<root->data){
        root->left= insert(root->left,value);
    }
    else{
        root->right= insert(root->right,value);
    }
    return root;

}
int main(){
    Node *root=NULL;
    int nums[]={8,2,15,1,5,10,20,4,7,18,22, 3};
    int size =sizeof (nums) / sizeof (nums[0]);

    for(int i=0; i<size; i++){
        root= insert(root, nums[i]);
    }
   // Node* closestNum= search(root,16);
    printf("%d ",isPerfectlyBalanced(root));
    //printf("%d\n", closestNum->data);
    return 0;
}