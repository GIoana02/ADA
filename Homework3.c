#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define MAX 5000

typedef struct tree{
    int data;
    struct tree* left;
    struct tree* right;
}Node;

Node* rotateLeft(Node* x){
    Node* y;
    y=x->right;
    Node* lC;
    lC=y->left;

    y->left=x;
    x->right=lC;

    return y;
}

Node* rotateRight(Node* x){
    Node* y;
    y=x->left;
    Node* lC;
    lC=y->right;

    y->right=x;
    x->left=lC;

    return y;
}

void quicksort(int arr[MAX],int first,int last){
    int i, j, pivot, temp;

    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(arr[i]<=arr[pivot]&&i<last)
                i++;
            while(arr[j]>arr[pivot])
                j--;
            if(i<j){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }

        temp=arr[pivot];
        arr[pivot]=arr[j];
        arr[j]=temp;
        quicksort(arr,first,j-1);
        quicksort(arr,j+1,last);

    }
}


int height( Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = height(root->left);
      //  printf("\nFor %d we have: \n LeftH %d ", root->data, leftHeight);
        int rightHeight = height(root->right);
       // printf("RightH %d, \n", rightHeight);
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
      //  printf("\nThis is answer for %d - leftH: %d \n", root->data, leftHeight);
        int rightHeight = height(root->right);
       // printf("\nThis is answer for %d - rightH:%d \n", root->data, rightHeight);
        if (abs(leftHeight - rightHeight) <= 1 && isPerfectlyBalanced(root->left) && isPerfectlyBalanced(root->right)) {
            return 1;
        } else {
            return 0;
        }
    }
}

Node *insert(Node* root, int value){
    if (root==NULL){
        Node *new_node=malloc(sizeof(Node));
        new_node->data=value;
        new_node->left=NULL;
        new_node->right=NULL;
        return new_node;
    }
    if(value<root->data){
        root->left= insert(root->left,value);
    }
    else if(value > root->data){
        root->right= insert(root->right,value);
    }
    else {
        return root;
    }

    int balance= isPerfectlyBalanced(root);

    if(balance > 1 && value < root->left->data){
        printf("The tree is not balanced anymore\n");
        return rotateRight(root);
    }
    if(balance < -1 && value > root->right->data){
        printf("The tree is not balanced anymore\n");
        return rotateLeft(root);
    }

    if(balance > 1 && value > root->left->data){
        printf("The tree is not balanced anymore\n");
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if(balance < -1 && value< root->right->data){
        printf("The tree is not balanced anymore\n");
        root->right= rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
      //  printf("%d ", root->data);
        inorder(root->right);
    }
}

int main(){
    int x[MAX];
    Node* root=NULL;
    clock_t start=clock();
    
    for (int i = 0; i < MAX; i++) {
        int okay = 0;

        while (!okay) {
            x[i] = rand() % MAX + 1;
            okay = 1;

            for (int j = 0; j < i; j++) {
                if (x[i] == x[j]) okay = 0;
            }
        }
      //  printf("%d, ",x[i]);
    }
    quicksort(x,0,MAX-1);

    for(int i=0; i<MAX; i++){
        root=insert(root, x[i]);
    }

    inorder(root);

    clock_t end=clock();
    double time_taken = ((double )(end-start))/CLOCKS_PER_SEC;
    printf("Time taken for %d random numbers is: %f seconds\n",MAX, time_taken);


    return 0;
}