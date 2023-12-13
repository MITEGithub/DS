#include <iostream>
#include <cmath>
#include <vector>
using namespace std ; 
class node {
    
} ; 
template <class T> 
class heap {
        vector<T> data ; 
        int count ; 
        int getleft(int x) {
            if(x==1) return -1 ; 
            return 2 * x ; 
        }
        int getright(int x) {
            return 2 * x + 1 ; 
        }
        int getfa(int x) {
            return x / 2 ; 
        }
        bool is(int x) {
            if(x > count) return false ; 
            else return true ; 
        }
        void keep(int x) {
            if(!is(x)) return ; 
            int left = getleft(x) ; 
            int right = getright(x) ; 
            if(!is(left) && !is(right)) return ; 
            int tmp = 99999999 ; 
            int index ; 
            if(is(left) && data[left] < tmp) {tmp = data[left] ; index = left ; }
            if(is(right) && data[right] < tmp) {tmp = data[right] ; index = right ;} 
            swap(data[index], data[x]) ; 
            keep(index) ; 
        }
        void init() {
            int len = floor(count / 2) ; 
            for(int i=len ; i>=1 ; i++) {
                keep(i) ;   
            }
        }
        public:
        T Getmin() {
            return data[1] ; 
        }
        void Deletemin() {
           swap(data[1], data[count]) ; 
           count-- ; 
           keep(1) ; 
        } 
        void Insert(int x) {
            data.push_back(x) ; 
            count++ ; 
            int tmp = getfa(x) ; 
            while(data[tmp] > x) {
                swap(data[tmp], x) ; 
                tmp = getfa(data[tmp]) ; 
                if(tmp == -1) break ; 
            }
        }
} ; 
