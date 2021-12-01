#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pus;
typedef pair<pus,int> edge;
vector<bool> go(vector<edge> &edges,vector<edge> &sorted,vector<vector<int>>& queries,int q,int n,int m,int* pre,int*rk);
int find(int* pre,int x);
void join_set(int* rk,int * pre,int x,int y);
bool dfs(vector<bool>& visited,vector<vector<int>>& MST,vector<vector<int>>& temp,int n,int start,int parent);
bool dfs(vector<bool>& visited,vector<vector<int>>& MST,vector<vector<int>>& temp,int n,int start,int parent){
    visited[start] = true;
    bool c = true;
    for (auto v : temp[start] ){
        if (!visited[v]){
            if (dfs(visited,MST,temp,n,v,start)){
                return true;}
            
        }
        else if(v != parent){
            return true;
        }
        else if(c){
            c = false;
        }else{
            return true;
        }
    }
    for (auto v : MST[start] ){
        if (!visited[v]){
            if (dfs(visited,MST,temp,n,v,start)){
                return true;}
            
        }
        else if(v != parent){
            return true;
        }
        else if(c){
            c = false;
        }else{
            return true;
        }
    }
    return false;
}
bool cycle(vector<vector<int>>& MST,vector<vector<int>>& temp,int n,int start);
bool cycle(vector<vector<int>>& MST,vector<vector<int>>& temp,int n,int start){
    vector<bool> visited(n+1,false);
        visited[start] = true;
        for (auto v : temp[start] ){
        if (!visited[v]){
            if (dfs(visited,MST,temp,n,v,start)){
                return true;}
            
        }
        }
        for (auto v : MST[start] ){
        if (!visited[v]){
            if (dfs(visited,MST,temp,n,v,start)){
                return true;}
            
        }
        }

    return false;
}
int find(int* pre,int x) {
	if(x== pre[x]) return x;
	return find(pre,pre[x]);
}
void join_set(int* rk,int * pre,int x,int y) {
	if(rk[x]==rk[y]) ++rk[x];
	if(rk[x]<rk[y]) swap(x,y);
	pre[y]=x;
}

vector<bool> go(vector<edge> &edges,vector<edge> &sorted,vector<vector<int>>& queries,int q , int n,int m,int* pre,int*rk){
    vector<bool> ans(q,true);
    vector<int> query_index(q,0);
    vector<vector<int>> MST(n+1);
    for (int i = 0 ; i < n ; i++){
        pre[i+1] = i+1;
        rk[i+1] = 1;
    }
    int set1,set2,start;
    int sorted_index = 0;
    for (;sorted_index<m; sorted_index++){
        for(int qu = 0 ; qu < q ; qu++){
            if(ans[qu]){
                start = 0;
                vector<vector<int>> temp(n+1);
                while (sorted[sorted_index].second == edges[queries[qu][query_index[qu]]].second){
                    start = edges[queries[qu][query_index[qu]]].first.first;
                    temp[edges[queries[qu][query_index[qu]]].first.first].push_back(edges[queries[qu][query_index[qu]]].first.second);
                    temp[edges[queries[qu][query_index[qu]]].first.second].push_back(edges[queries[qu][query_index[qu]]].first.first);
                    query_index[qu]++;
                }
                if (start != 0 &&cycle(MST,temp,n,start)){
                    ans[qu] = false;
                }
            }
        }
        
        set1 = find(pre,sorted[sorted_index].first.first);
        set2 = find(pre,sorted[sorted_index].first.second);
        if(set1 != set2){
            MST[sorted[sorted_index].first.first].push_back(sorted[sorted_index].first.second);
            MST[sorted[sorted_index].first.second].push_back(sorted[sorted_index].first.first);
            //cout<<"( " <<sorted[sorted_index].first.first <<"  "<< sorted[sorted_index].first.second << "  "<<sorted[sorted_index].second << "  )";
            join_set(rk,pre,set1,set2);
        }
    }
    return ans;
}
int main(){
    int n,m;
    cin >> n >> m;
    int s,d,w;
    int pre[n+1],rk[n+1];
    vector<edge> edges(m+1);
    vector<edge> sorted(m);
    for (int i = 0 ; i < m ; i++ ){
        cin>>s>>d>>w;
        edges[i+1].first = pus(s,d);
        edges[i+1].second = w;
        sorted[i].first = pus(s,d);
        sorted[i].second = w;
    }
    sort(sorted.begin(), sorted.end(),[](const edge & a, const edge & b) -> bool
        {
            return a.second < b.second;
        });
    int q,ci;
    cin >> q;
    vector<vector<int>> queries(q);
    for(int i = 0; i< q ; i++){
        cin>>ci;
        for (int j = 0; j < ci ; j++){
            cin>>w;
            queries[i].push_back(w);
        }
        sort(queries[i].begin(),queries[i].end(),[edges](const int & a, const int & b) -> bool
        {
            return edges[a].second < edges[b].second;
        });
    }
    vector<bool> ans = go(edges,sorted,queries,q,n,m,pre,rk);
    for (auto answer : ans ){
        cout<<(answer ? "YES":"NO")<<endl;
    }
    return 0;
}

