#include <iostream>
#include <vector>

using namespace std ; 

class DisjointSet {
    private:
        int *father ; 
        int *count ; 
        int Size ; 
        void init() {
            father = new int[Size] ; 
            count = new int [Size] ; 
            for(int i=0 ; i<Size ; i++) {
                father[i] = i ; 
                count[i] = 0 ; 
            }
        }
    public:

        int GetFather(int x) {
            return x == father[x] ? x : father[x] = GetFather(father[x]) ; 
        }

        void UFunion(int a, int b) {
            int father_a = GetFather(a) ; 
            int father_b = GetFather(b) ; 

            if(count[father_a] < count[father_b]) {
                swap(father_a, father_b) ; 
            }
            father[father_b] = father_a ; 
        }
} ; 
