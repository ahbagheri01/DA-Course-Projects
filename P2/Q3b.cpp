#include<bits/stdc++.h>
typedef std :: pair<int,int> pus;
void update_queue(bool*V,int*p,int v,std:: queue <int>* queue_bfs,int u)      
{
    (*queue_bfs).push(v);
    p[v] = u;
    V[v] = true;
}

bool augmenting_flow_bfs(int N,int** res_Graph, int source, int destination, int* p)
{
    bool* nodes_visited = (bool*) calloc(N,sizeof(bool));
    nodes_visited[source] = true;
    p[source] = -1;
    std:: queue <int> qu ;
    std:: queue <int>* queue_bfs = &(qu);
    (*queue_bfs).push(source);
    int u;
    do{
        u = (*queue_bfs).front();
        (*queue_bfs).pop();
        for (int v=0; v<N; v++)
        {
            if (nodes_visited[v]==false && res_Graph[u][v] > 0)
            {
                update_queue(nodes_visited,p,v,queue_bfs,u);
            }
        }
    }while (!(*queue_bfs).empty());
    bool ans = (nodes_visited[destination] == true);
    free(nodes_visited);
    return ans;
}
void find_min_cut(int N,int** res_Graph, int source, bool* nodes_visited,int* p)
{
    nodes_visited[source] = true;
    p[source] = -1;
    std:: queue <int> qu ;
    qu.push(source);
    int u;
    do{
        u = qu.front();
        qu.pop();
        for (int v=0; v<N; v++)
        {
            if (nodes_visited[v]==false && res_Graph[u][v] > 0)
            {
                update_queue(nodes_visited,p,v,&qu,u);
            }
        }
    }while (!qu.empty());
}
int find_maximum_augmenting_path(int source , int dest,int**res_Graph,int* p){
    int augmenting_flow = INT_MAX;
    int u,v;
    for (v=dest; v!=source; v=p[v])
        {
            u = p[v];
            augmenting_flow = std::min(augmenting_flow, res_Graph[u][v]);
        }
    return augmenting_flow;
}
void update_res_Graph(int source,int dest,int augmenting_flow,int** res_Graph,int*p){
    int u,v;
    for (v=dest; v != source; v=p[v])
        {
            u = p[v];
            res_Graph[u][v] -= augmenting_flow;
            res_Graph[v][u] += augmenting_flow;
        }
}
int ** create_res_Graph(int N , int** graph){
    int u, v;
    int** res_Graph = (int**)malloc(N * sizeof(int*));
    for (u = 0; u < N; u++){
        res_Graph[u] = (int*)calloc(N , sizeof(int));
        for (v = 0; v < N; v++)
             res_Graph[u][v] = graph[u][v];
    }
    return res_Graph;
}
std :: vector<std::pair<int,int>> minCut_Flod(int N,int** graph, int s, int t)
{
    int** res_Graph = create_res_Graph(N,graph);
    int* parent = (int*)malloc(N*sizeof(int)); 
    int augmenting_flow; 
    while (augmenting_flow_bfs(N,res_Graph, s, t, parent))
    {
        augmenting_flow = find_maximum_augmenting_path(s,t,res_Graph,parent);
        update_res_Graph(s,t,augmenting_flow,res_Graph,parent);
    }
    bool* visited_nodes = (bool*) calloc(N,sizeof(bool));
    parent = (int*)malloc(N*sizeof(int)); 
    find_min_cut(N,res_Graph, s, visited_nodes,parent);
    std::vector<std:: pair<int,int>> final_edge;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
         if (graph[i][j]&&visited_nodes[i] && !visited_nodes[j] )
            final_edge.emplace_back(pus(i,j));
    for (int i = 0; i < N ; i++){
        free(res_Graph[i]);
    }
    free(res_Graph);
    free(parent);
    free(visited_nodes);
    return final_edge;
}
int main() {
    int n, m,tmp,tmp1;
    std::cin >> n >> m;
    std::vector<std::vector<int>> costs(2);
    std::vector<std::vector<int>> egdes(n);
    for(int i = 0 ; i < 2 ; i++){
        for(int j = 0 ; j < n;j++){
            std::cin>>tmp;
            costs[i].emplace_back(tmp);
        }
    }
    int** graph =(int**)malloc((2*n+2) * sizeof(int*));
    for (int u = 0; u < (2*n+2) ; u++){
        graph[u] = (int*)malloc((2*n+2) * sizeof(int));
    }
    for(int i = 0 ; i < m ; i++){
        std::cin>>tmp>>tmp1;
        graph[tmp][tmp1+n] = INT32_MAX;
    }
    int s = 0;
    int d = 2*n+1;
    tmp = 1+n;
    for(int i = 0 ; i < n ; i++){
        graph[0][i+1] = costs[1][i];
        graph[i+tmp][d] = costs[0][i];
    }

    std::vector<std::pair<int,int>> final_edge = minCut_Flod(d+1,graph, s, d);
    int u,v,sum = 0;
    int size = final_edge.size();
    for (int i = 0 ; i <  size; i++){
        sum += graph[final_edge[i].first][final_edge[i].second];
    }
    std::cout<<sum<<std::endl;
    std::cout<<size<<std::endl;
    for(int i = 0 ; i < size ; i++){
        u = final_edge[i].first;
        v = final_edge[i].second;
        if (u==0){
            std::cout<<v<<" "<<"out\n";
        }else{
            std::cout<< u -n <<" "<<"in\n";
        }
    }
    return 0;
}