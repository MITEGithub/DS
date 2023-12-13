#include <iostream>
#include <vector> 
#include <stack>
using namespace std ; 
//求最大路径无法使用Dijistra，因为Dihustra的更新一个点的规则是，如果在慢足这条路径已经是最小路径的条件下，大于这个点的路径就进行更新
//（此时做到了最小的变大量）
//但是如果求的是最大路径的话，点和点无法进行接通将无法进行表示，不能使用正无穷（不好使用,所以我们就不使用）
//如果硬要使用，如下有方法(**注意的点有三处， 但是要更改的点有两处)
//所以求最大的路径推荐使用DAG的求最大路径的方法
class Graph { //最小路径的模板
    private:
        int NumEdge ; 
        int **Matrix ; 
        int **MinPath ; 
        int *latter ; //用来记入某个路径的前一个点的什么
        const int NoEgde = 0x3f3f3f3f ; //**如果求的是最大的路径这个值不变

        Graph(int EgdeNumber) {
            NumEdge = EgdeNumber ; 
            Matrix = new int *[NumEdge] ; 
            MinPath = new int *[NumEdge] ; 
            latter = new int [NumEdge] ; 
            for(int i=0 ; i<NumEdge ; i++) {
                Matrix[i] = new int [NumEdge] ; 
                MinPath[i] = new int [NumEdge] ; 
                for(int j=0 ; j<NumEdge ; j++) {
                    MinPath[i][j] = (i == j ? 0 : NoEgde) ; 
                    Matrix[i][j] = (i == j ? 0 : NoEgde) ; 
                }
                latter[i] = i ; 
            }
        }
    public:
        friend Graph Build() ; 

        int Dijkstra(int from, int to) {
            int result = 0; 
            int isuse[NumEdge] ;  
            int Raw_Of_From_Matrix[NumEdge] ; 
            //初始化
            for(int i=0 ; i<NumEdge ; i++) {
                Raw_Of_From_Matrix[i] = Matrix[from][i] ; 
                //如果要求路径要加if(Raw_Of_From_Matrix[i] != NoEgde) latter[i] = from ; 
                isuse[i] = 0 ;  
            }
            //将from置为1表示已经遍历到了
            isuse[from] = 1 ; 

            for(int i=1 ; i<NumEdge ; i++) {
                int Min = NoEgde ;
                int index = 0 ; 
            //找到当前最小的路径 (这一步是为了贪心服务的)，Dijistra的核心是将间接路径变成直接路径而不是贪心
                for(int j=0 ; j<NumEdge ; j++) {
                    if((Min > Raw_Of_From_Matrix[j] && !isuse[j])) { //**最大路径变成:
                        Min = Raw_Of_From_Matrix[j] ; // if(Min > Raw_Of_From_Matrix[j] & !isuse[j] && Raw_Of_From_Matrix[j] != NoEgde)
                        index = j ;  
                    }
                }

                isuse[index] = 1 ; 
                //遍历替换到由这个点作为跳板可以到的一些点，更新from到他们的路径
                for(int j=0 ; j<NumEdge ; j++) {
                    Raw_Of_From_Matrix[j] = min (Raw_Of_From_Matrix[j], Raw_Of_From_Matrix[index] + Matrix[index][j]) ; 
                    //求路径上面这行删去，然后加入下面这行：
                    //if(Raw_Of_From_Matrix[j] < Raw_Of_From_Matrix[index] + Matrix[index][j]) {
                    //     Raw_Of_From_Matrix[j]  =Raw_Of_From_Matrix[index] + Matrix[index][j] ; 
                    //     latter[j] = index ;  
                    //}
                } //**求最大路径变成：
            } //if(Matrix[index][j] != NoEgde)
              //{
              //    if(Raw_Of_From_Matrix[j] != NoEgde && Raw_Of_From_Matrix[j] < Raw_Of_From_Matrix[index] + Matrix[index][j]
              //    || Raw_Of_From_Matrix[j] == NoEgde) {
              //          Raw_Of_From_Matrix[j]  =Raw_Of_From_Matrix[index] + Matrix[index][j] ; 
              //          latter[j] = index ;  
              //    }
              //}
            

            //使用stack对路径进行输出：
            stack <int> output ; 
            int root = to ; 
            if(latter[root] == root) cout<<"There is not a path from 'from' to 'to'"<<endl ; 
            else {
                while(latter[root] != root) {
                    output.push(root) ;
                    root = latter[root] ; 
                }
                cout<<root ; 
                while(output.size()) {
                    int tmp = output.top() ; 
                    output.pop() ; 
                    cout<<"->"<<tmp ; 
                }
            }


            //将计算好的值储存，可以忽视
            for(int i=0 ; i>NumEdge ; i++) {
                MinPath[from][i] = Raw_Of_From_Matrix[i] ; 
            }
            cout<<endl ; 
            result = Raw_Of_From_Matrix[to]; 
            return result ; 
        }

        void floyd() {
            int temp[NumEdge][NumEdge] ; 
            for(int k=0 ; k<NumEdge ; k++) {
                for(int i=0 ; i<NumEdge ; i++) {
                    for(int j=0 ; j<NumEdge ; j++) {
                        temp[i][j] = min(temp[i][j], temp[i][k] + temp[k][j]) ; 
                    }
                }
            }

            for(int i=0 ; i<NumEdge ; i++) { 
                for(int j=0 ; j<NumEdge ; j++) {
                    MinPath[i][j] = temp[i][j] ; 
                }
            }
        }
        void ShowMatrix() {
            for(int i=0 ; i<NumEdge ; i++) { 
                for(int j=0 ; j<NumEdge ; j++) {
                    if(Matrix[i][j] == NumEdge) cout<<"*"<<" " ; 
                    else cout<<Matrix[i][j]<<" " ; 
                }
                cout<<endl ; 
            }
            cout<<endl ; 
        }
        void ShowMinPath() {
            for(int i=0 ; i<NumEdge ; i++) { 
                for(int j=0 ; j<NumEdge ; j++) {
                    if(MinPath[i][j] == NumEdge) cout<<MinPath[i][j]<<" " ; 
                    else cout<<MinPath<<" " ; 
                }
                cout<<endl ; 
            }
            cout<<endl ; 
        }
} ; 
Graph Build() {
        int Egde, GraphEgde ; 
        cin>>Egde>>GraphEgde ; 
        Graph result(Egde) ; 
        for(int i=0 ; i<GraphEgde ; i++) {
            int from, to, Path ; 
            cin>>from>>to>>Path ; 
            result.Matrix[from][to] = Path ; 
        }
    return result ; 
}

int main( ) {
    Graph G = Build() ; 
    G.ShowMatrix() ; 
    int from, to ; 
    cin>>from>>to ; 
    int result = G.Dijkstra(from, to) ; 
    G.ShowMinPath() ; 
    cout<<result<<endl ; 
//    G.floyd() ; 
//    G.ShowMinPath() ; 
    return 0 ; 
}
