#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pus;
#define V 400

int bfs(int rGraph[V][V], int s, int t, int parent[])
{
     bool visited[V];
    memset(visited, 0, sizeof(visited));
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
  
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}
void dfs(int rGraph[V][V], int s, bool visited[])
{
    visited[s] = true;
    for (int i = 0; i < V; i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited);
}
  
vector<pair<int,int>> minCut(int graph[V][V], int s, int t)
{
    int u, v;
    int rGraph[V][V]; 
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];
    int parent[V];  
    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
    }
    bool visited[V];
    memset(visited, false, sizeof(visited));
    dfs(rGraph, s, visited);
    vector<pair<int,int>> final_edge;
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
         if (visited[i] && !visited[j] && graph[i][j])
            final_edge.emplace_back(pus(i,j));
    return final_edge;
}
int main() {
        const int MAX = 3e5+20;

    int n, m,tmp,tmp1;
    cin >> n >> m;
    vector<vector<int>> costs(2);
    vector<vector<int>> egdes(n);
    int graph[V][V];
    for(int i = 0 ; i < 2 ; i++){
        for(int j = 0 ; j < n;j++){
            cin>>tmp;
            costs[i].emplace_back(tmp);
        }
    }
    for(int i = 0 ; i < m ; i++){
        cin>>tmp>>tmp1;
        graph[tmp][tmp1+n] = INT32_MAX;
    }
    int s = 0;
    int d = 2*n+1;
    tmp = 1+n;
    for(int i = 0 ; i < n ; i++){
        graph[0][i+1] = costs[1][i];
        graph[i+tmp][d] = costs[0][i];
    }

    vector<pair<int,int>> final_edge = minCut(graph, s, d);
    int u,v,sum = 0;
    int size = final_edge.size();
    for (int i = 0 ; i <  size; i++){
        sum += graph[final_edge[i].first][final_edge[i].second];
    }
    cout<<sum<<endl;
    cout<<size<<endl;
    for(int i = 0 ; i < size ; i++){
        u = final_edge[i].first;
        v = final_edge[i].second;
        if (u==0){
            cout<<v<<" "<<"out\n";
        }else{
            cout<< u -n <<" "<<"in\n";
        }
    }
    return 0;
}