#include<iostream>
#include<list>

using namespace std;


class Graph{

private:

int V;
list<pair<int,int> > l;

public:

Graph(int V){
    this->V = V;
}

void addEdge(int u,int v){
    l.push_back(make_pair(u,v));
}

int find_set(int i,int parent[]){

    if(parent[i] == -1){
        return i;
    }


// simple find function 
    //return find_set(parent[i],parent);


// path compression 
return parent[i] = find_set(parent[i],parent);

}

void set_union(int x,int y,int parent[]){
    int s1 = find_set(x,parent);
    int s2 = find_set(y,parent);

    if(s1 != s2){
        parent[s2] = s1;
    }
}

// union by rank
void set_union_by_rank(int x,int y,int parent[],int rank[]){
    int s1 = find_set(x,parent);
    int s2 = find_set(y,parent);

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

bool contains_cycle(){

    int* parent = new int[V]; 
    int* rank = new int[V];  

    for(int i = 0;i<V;i++){
        parent[i] = -1;
        rank[i] = 1;
    }

    for(auto edge: l){

        int i = edge.first;
        int j = edge.second;

        int s1 = find_set(i,parent);
        int s2 = find_set(j,parent);

        if(s1 != s2){
            set_union_by_rank(i,j,parent,rank);
        }else{
            return true;
        }

    }
    delete [] parent;
    return false;

}

};

int main(){

    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
   // g.addEdge(3,0);

    cout<<g.contains_cycle();

}

