#include<iostream>
#include<vector>
using namespace std;

class DSU{

    private:

    int* parent;
    int* rank;

    public:

    DSU(int n){
        
        parent = new int[n];
        rank = new int[n];

        for(int i = 0;i<n;i++){
            parent[i] = -1;
            rank[i] = 1;
        }

    }


// find by path compression
    int find(int i){

        if(parent[i] == -1){
            return i;
        }

        return parent[i] = find(parent[i]);
    }


// union by rank
    void set_union(int x,int y){

        int s1 = find(x);
        int s2 = find(y);

        if(s1 != s2){

            if(rank[s1] > rank[s2]){
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }else{
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
        }
    }

};

class Graph{

    private:
    int V;
    vector<vector<int> > edgeList;

    public: 

    Graph(int V){
        this->V = V;
    }

    void addEdge(int w,int x,int y){

        vector<int> v;
        v.push_back(w);
        v.push_back(x);
        v.push_back(y);

        edgeList.push_back(v);
    }

    int kruskal_mst(){


        DSU s(V);
        int ans = 0;
        sort(edgeList.begin(),edgeList.end());

        for(auto edge: edgeList){

            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            if(s.find(x) != s.find(y)){
                s.set_union(x,y);
                ans += w;
            }
        }
        return ans;

    }




};

int main(){



Graph g(6);

g.addEdge(3,2,4);
g.addEdge(1,1,2);
g.addEdge(2,2,3);
g.addEdge(3,3,4);
g.addEdge(2,1,4);
g.addEdge(2,1,3);


cout<<g.kruskal_mst();

}