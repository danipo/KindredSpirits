//Daniel Powley, da872859
//Assignment 3, Kindred Spirits

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "KindredSpirits.h"

#define EMPTY_STACK_ERR INT_MAX

//struct borrowed from stacks.c
typedef struct Stack{
    int *array;
    int size;
    int capacity;
} Stack;

//counts nodes, to use as the capacity for our stacks
int count_nodes(node *root) {

    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;

    else
        return 1+(count_nodes(root->left) + count_nodes(root->right));
}

//checks if the trees are reflections
int isReflection(node *a, node *b){

    //if both trees are empty, they are reflections
    if(a == NULL && b == NULL)
        return 1;

    //if one is NULL, then this means the other is not
    if(a == NULL)
        return 0;
    if(b == NULL)
        return 0;

    //recursively checks if the left node matches the right node and the opposite
    //but only if the data in each node is the same
    if(a->data == b->data){
        if (isReflection(a->left,b->right) && isReflection(b->left,a->right))
            return 1;
    }

    return 0;
}

node *makeReflection(node *root){

    node *root2;

    if(root == NULL)
        return root;

    root2 = malloc(sizeof(node));

    //copies the data into the second node, then recursively adds the node to the opposite
    //child on the other subtree
    root2->data = root->data;
    root2->left = makeReflection(root->right);
    root2->right = makeReflection(root->left);

    return root2;
}

//following stack functions borrowed from stacks.c
Stack *createStack(int capacity){

    Stack *s = malloc(sizeof(Stack));

    s->array = malloc(sizeof(int) * capacity);

    s->size = 0;
    s->capacity = capacity;

    return s;
}

int isFull(Stack *s){

    //return (s == NULL || s->size >= s->capacity);

    if(s->size >= s->capacity)
        return 1;

    return 0;
}

int isEmpty(Stack *s){
    return (s == NULL || s->size ==0 );
}

void push(Stack *s, int data){

    if(isFull(s))
        return EMPTY_STACK_ERR;

    s->array[s->size++] = data;
}

int pop(Stack *s){
    if(isEmpty(s)){
        //printf("Stack is full");
        return;
    }

    return s->array[--s->size];
}

Stack *destroyStack(Stack *s){

    if(s == NULL)
        return NULL;

    free(s->array);
    free(s);

    return NULL;
}

//These two traversal functions are borrowed and adapted from bst.c
void preorder(Stack *s, node *root)
{
	if (root == NULL)
		return;

	push(s,root->data);
	preorder(s,root->left);
	preorder(s,root->right);
}

void postorder(Stack *s, node *root)
{
	if (root == NULL)
		return;

	postorder(s,root->left);
	postorder(s,root->right);
	push(s,root->data);
}

//helper function that checks the two stacks are equal, by popping the top
//of both stacks and comparing that value
int KindredHelper(Stack *s1, Stack *s2){

    while(!isEmpty(s1)){
        if(pop(s1) != pop(s2)){
            return 0;
        }
    }

    return 1;
}

//Kindred function creates two stacks, then the traversal functions will add values to the stacks
//Then, the helper checks to see if the stacks are equal
int kindredSpirits(node *a, node *b){

    Stack *s1 = createStack(count_nodes(a));
    Stack *s2 = createStack(count_nodes(b));

    if(a == NULL && b == NULL)
        return 1;

    if(count_nodes(a) != count_nodes(b))
        return 0;

    preorder(s1, a);
    postorder(s2, b);

    if(KindredHelper(s1,s2)){
        destroyStack(s1);
        destroyStack(s2);
        return 1;
    }

    destroyStack(s1);
    destroyStack(s2);

    s1 = createStack(count_nodes(a));
    s2 = createStack(count_nodes(b));

    postorder(s1, a);
    preorder(s2, b);

    if(KindredHelper(s1,s2)){
        destroyStack(s1);
        destroyStack(s2);
        return 1;
    }

    destroyStack(s1);
    destroyStack(s2);
    return 0;
}

double difficultyRating(void){
	return 3.5;
}

double hoursSpent(void){
	return 20.0;
}
