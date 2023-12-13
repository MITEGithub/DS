#include <iostream>
#include <vector>
using namespace std;

int get_father(int index) {
    if(index%2) return (index-1)/2;
    else return (index-2)/2;
}

int get_left(int index) {
    return index * 2 + 1;
}

int get_right(int index) {
    return index * 2 + 2;
}

void Swap(vector<int> &heap, int index) {
    if(index == 0) return;
    else {
        int fa = get_father(index);
        if (heap[fa] < heap[index]) 
            swap(heap[fa], heap[index]);
        Swap(heap, fa);
    }
}
void begin(vector<int> &heap, int len) {
    for(int i=1;i<len;i++) {
        Swap(heap, i);
    }
}
void Keepheap(vector<int> &heap, int index, int len) {
    int left = get_left(index);
    int right = get_right(index);

    if(left <= len && heap[left] > heap[index]) {
        Swap(heap, left);
        Keepheap(heap, left, len);
    }
    if(right <= len && heap[right] > heap[index]) {
        Swap(heap, right);
        Keepheap(heap, right, len);
    }
}
void Heapshow(vector<int> &heap) {
    for(auto iter : heap) {
        cout<<iter<<" ";
    }
    cout<<endl;
}

void Heapsort(vector<int> &heap) {
    int size = heap.size();
    begin(heap, size - 1);
    for(int i=1;i<size;i++) {
        int len = size - i ;
        swap(heap[0], heap[len]);
        Keepheap(heap, 0, len -1 );
    }
}
int main(){
    vector <int> heap;
    int n; cin >> n ;
    for(int i=0;i<n;i++) {
        int t; cin >> t;
        heap.push_back(t);
    }

    Heapsort(heap);
    Heapshow(heap);
    return 0;
}
