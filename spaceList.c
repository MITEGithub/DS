#include <stdio.h>
#include <stdlib.h>
typedef int item;
typedef struct node* link;
typedef struct node{
    item element;
    int next;
}node;
typedef struct space* Space;
typedef struct space{
    int num;
    int first1;
    int first2;
    link node;
}space;
Space spaceinit(int max){
    Space res =(Space)malloc(sizeof (space)); 
    res->num = max ;
    res->node = (link)malloc(max * sizeof (node));
    res->first1=0;
    res->first2=-1;
    return res;
}
int spaceall(Space s){
    if(s->first2 == -1) return s->first1++;
    int res = s->first2;
    s->first2 = s->node[res].next;
    return res;
}
void spacedel(Space s, int k){
    s->node[k].next = s->first2;
    s->first2 = k;
}
typedef struct list* List;
typedef struct list{
    int head;
    Space s;
}list;
List listinit(int max){
    List L = (List )malloc(sizeof (list));
    L->s = spaceinit(max);
    L->head = -1; 
    return L;
}
void listinsert(List L, item x, int k){
    int temp = L->head;
    for(int i=1;i<k-1&&temp<=L->s->num&&temp!=-1;i++)
        temp = L->s->node[temp].next; 
    int Node = spaceall(L->s);
    L->s->node[Node].element = x;
    if(temp!=-1){
        L->s->node[Node].next = L->s->node[temp].next;
        L->s->node[temp].next = Node;
    }
    else{
        L->s->node[Node].next = L->head;
        L->head = Node;
    }
}
void listprint(List L){
    int temp = L->head;
    while(temp!=-1){
        printf("%d ",L->s->node[temp].element);
        temp = L->s->node[temp].next;
    }
}
int main(){
   List L = listinit(500);
   for(int i=1;i<=499;i++){
        listinsert(L,i,i);
   }
    listprint(L);
    return 0;
}
