#include<stdio.h>
#include <stdlib.h>
typedef int stackitem;
typedef struct stack{
    int top;
    int max;
    stackitem* node;
}stack;
stack* stackinit(int size){
    stack* s = (stack*)malloc(sizeof(stack));
    s->node = (stackitem*)malloc(size*sizeof(stackitem));
    s->max = size;
    s->top = -1;
    return s;
}
void push(stack* s, stackitem x){
    if(stackfull()) return;
    s->node[++s->top] = x; 

}
stackitem pop(stack* s){
    if(stackempty()) return 0;
    return s->node[--s->top];
}
// link
typedef struct node{
    stackitem element;
    stackitem* next;
}node;
typedef struct linkstack{
    node* head;
    node* top;
}linkstack;
linkstack* lstackinit(){
    linkstack* s = (linkstack*)malloc(sizeof(linkstack));
    s->top = NULL;
    s->head = (node*)malloc
    return s;
}
