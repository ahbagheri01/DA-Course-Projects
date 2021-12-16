#include<bits/stdc++.h>
using namespace std;
#define UINDEX 0
#define VINDEX 1
#define WEIGHINDEX 2
#define EDGEINDEX 3
#define MSTINDEXU 4
#define MSTINDEXV 5
vector<int>* edges;
int find(int*rootSet, int x) {
    if (rootSet[x] == x)
        return x;
    return find(rootSet,rootSet[x]);
}

void join_sets(int* rootSet , int*rank_of_set, int x, int y) {
    x = find(rootSet,x); y = find(rootSet,y);
    if (rank_of_set[x] > rank_of_set[y])
        rootSet[y] = x;
    else if(rank_of_set[x] < rank_of_set[y])
        rootSet[x] = y;
    else {
        rank_of_set[x]++;
        rootSet[y] = x;
    }
}
void reset_sets(int* rootSet , int*rank_of_set,const int n){
        for (int i = 1; i < n + 1; i++) {
        rootSet[i] = i;
        rank_of_set[i] = 1;
    }
}
void findMST(int* rootSet , int*rank_of_set,int m){
    int mst_index = 0;
    int e;
    while (mst_index < m) {
        int e = mst_index;
        edges[e].push_back(find(rootSet,edges[e][UINDEX]));
        edges[e].push_back(find(rootSet,edges[e][VINDEX]));
        e++;
        while (e < m && edges[e][WEIGHINDEX] == edges[mst_index][WEIGHINDEX]){
            edges[e].push_back(find(rootSet,edges[e][UINDEX]));
            edges[e].push_back(find(rootSet,edges[e][VINDEX]));
            e++;
        }
        while (mst_index < e) {
            while (mst_index < e && find(rootSet,edges[mst_index][UINDEX]) == find(rootSet,edges[mst_index][VINDEX]))
                mst_index++;
            if (mst_index < e)
                join_sets(rootSet , rank_of_set,edges[mst_index][UINDEX], edges[mst_index][VINDEX]);
        }
    }
}
void find_cycle(vector<int>& query ,vector<bool>& query_ans,int query_counter,int c,int* rootSet,int * rank_of_set ){
    int e;
    for (int i = 0 ; query_ans[query_counter] && i < c;){
            e = i;
             if  (find(rootSet,edges[query[e]-1][MSTINDEXU]) == find(rootSet,edges[query[e]-1][MSTINDEXV]))  {
                    query_ans[query_counter] = false;}
            while (query_ans[query_counter] && e < c && edges[query[e]-1][WEIGHINDEX] == edges[query[i]-1][WEIGHINDEX]){
                if  (find(rootSet,edges[query[e]-1][MSTINDEXU]) == find(rootSet,edges[query[e]-1][MSTINDEXV]))  {
                    query_ans[query_counter] = false;
                    break;
                }
                join_sets(rootSet,rank_of_set,edges[query[e]-1][MSTINDEXU], edges[query[e]-1][MSTINDEXV]);
                e++;

            }
            while (i < e) {
                rootSet[edges[query[i]-1][MSTINDEXU]] = edges[query[i]-1][MSTINDEXU];
                rootSet[edges[query[i]-1][MSTINDEXV]] = edges[query[i]-1][MSTINDEXV];
                i++;
            }
        }
}
int main() {
    int n, m;
    cin >> n >> m;
    int rootSet[n+3], rank_of_set[n+3];
    vector<int> Myedges[m+4];
    edges = Myedges;
    reset_sets(rootSet , rank_of_set ,n);
    int u,v,w;
    for (int i = 0; i < m; i++) {
        vector<int> edge;
        cin>>u>>v>>w;
        edge.emplace_back(u);
        edge.emplace_back(v);
        edge.emplace_back(w);
        edge.emplace_back(i + 1);
        edges[i] = edge;
    }
    sort(edges, edges + m, [](const vector<int> & a, const vector<int> & b) -> bool
        { return a[WEIGHINDEX] < b[WEIGHINDEX]; });
    findMST(rootSet , rank_of_set,m);
    reset_sets(rootSet , rank_of_set,n);
    sort(edges, edges + m,[](const vector<int>& a,const vector<int>& b) -> bool {
        return a[EDGEINDEX] < b[EDGEINDEX]; });
    int q;
    cin>>q;
    vector<bool> query_ans(q,true);
    for (int query_counter = 0; query_counter < q ; query_counter++) {
        int c,e;
        cin >> c;
        vector<int> query(c);
        for (int i = 0; i < c; i++) {
            cin >> e;
            query[i] = e;
        }
        sort(query.begin(), query.end(), [](const int& a,const int& b) -> bool {
            return edges[a-1][WEIGHINDEX] < edges[b-1][WEIGHINDEX];});
        find_cycle(query ,query_ans,query_counter,c,rootSet,rank_of_set);
        query = vector<int>();
    }
    for (auto answer : query_ans ){
        cout<<(answer ? "YES":"NO")<<endl;
    }
    return 0;
}
