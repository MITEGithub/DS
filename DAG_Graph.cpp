#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ; 
#define SIZE 10001
struct node {
    bool operator==(const node *a) {
        return this->time == a->time ; 
    }
    int index ; 
    int time ; 
}; 
class DAGGraph {
        int ssize ; 
        vector<node> list_to[SIZE] ; 
        vector<node> list_from[SIZE] ; 
        int isuse[SIZE] ; 
        void build() {
            int n, m ; 
            cin>>n>>m ; 
            ssize = n ; 
            for(int i=0 ; i<m ; i++) {
                int from, to, time ; 
                cin>>from>>to>>time ; 
                node tmp = {to, time} ; 
                list_to[from].push_back(tmp) ;  
                list_from[to].push_back(tmp) ; 
            }
        }
        int GetRoot() {
           for(int i=0 ; i<ssize ; i++) {
               if(!isuse[i] && list_from[i].size()) return i ; 
           }
           return -1 ; 
        }
        
        void DAG() { 
            for(int i=0 ; i<ssize ; i++) {
                isuse[i] = 0 ; 
            }
            int root = GetRoot() ; 
            while(root != -1) {
                for(auto iter : list_to[root]) {
                    auto it = find(list_from[iter.index].begin(), list_from[iter.index].end(), (node){0, root}) ; 
                    if(it != list_from[iter.index].end()) {
                        list_from[iter.index].erase(it) ; 
                    }
                }
                isuse[root] = 1 ; 
                }
            }
} ; 
