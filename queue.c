#include<stdio.h>
#include<stdlib.h>
typedef int item;
typedef struct node{

}node;
typedef struct queue{
    int front;
    int rear;
    item* qu;
    int maxsize;
}Queue;
Queue* queueinit(int size){
    Queue* q = (Queue*)malloc(sizeof(Queue*));
    q->qu = (item*)malloc(size*sizeof(item));
    q->rear=0;
    q->front =0;
    q->maxsize = size;
    return q;
}
int queuempty(Queue* q){
    return q->rear==q->front;
}
int queuefull(Queue* q){
    return (q->rear+1%q->maxsize == q->front)?1:0;
}
item queuefront(Queue* q){
    if(queuempty(q)) return 0;
    return q->qu[q->front];
}
item queuerear(Queue* q){
    if(queuempty(q)) return 0;
    return q->qu[(q->rear+1)%q->maxsize];
}
void queueenter(Queue* q, item x){
    if(queuefull(q)) q->qu[(q->rear++)%q->maxsize] = x; 
}
void queuedel(Queue* q){
    if(queuempty(q)) q->front++;
}
