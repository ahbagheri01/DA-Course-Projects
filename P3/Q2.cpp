#include <vector>
#include <iostream>
using namespace std;
typedef vector<vector<int>> Adj_matrix;
int dfs(Adj_matrix& adj,bool* visited,int s,int p,int t,int l){
    if (s == t){
        return l+1;
    }
    visited[s] = true;
    int newL = 0;
    for (auto v : adj[s]){
        if (v == p || visited[v]){
            continue;
        }
        newL = max(newL,dfs(adj,visited,v,s,t,l+1));
    }
    visited[s] = false;
    return newL;
}
int longest_path(Adj_matrix& adj,bool* visited,int s,int t){
    if (s == t){
        return 0;
    }
    int l = 0;
    visited[s] = true;
    int newL = l;
    for (auto v : adj[s]){
        newL = max(newL,dfs(adj,visited,v,s,t,l));
    }
    visited[s] = false;
    return newL;
}
void print_table(int** res , int n){
    int i , j ;
    for( i = 0 ; i < n ; i++){
        for( j = 0 ; j < n-1 ; j++){
            cout<<res[i][j]<<" ";
        }
        cout<<res[i][j]<<endl;
    }
}
int main(){
    int n,m,u,v;
    cin >> n >> m;
    int** res = (int**) malloc( n*sizeof(int*));
    for(int i = 0 ; i < n ; i++){
        res[i] = (int*) malloc( n*sizeof(int));
    }
    Adj_matrix adj(n);
    for(int i = 0 ; i < m ; i++){
        cin>>u>>v;
        adj[v-1].push_back(u-1);
        adj[u-1].push_back(v-1);
    }

    bool* visited = (bool*) calloc(n,sizeof(bool));
    for(int i = 0 ; i < n ; i++){
        res[i][i] = 0;
        for(int j = i+1 ; j < n ; j++){
            res[i][j] = res[j][i] = longest_path(adj,visited,i,j);
        }
    }
    print_table(res,n);
    free(visited);
    for(int i = 0 ; i < n ; i++){
        free(res[i]);
    }
    free(res);
}

