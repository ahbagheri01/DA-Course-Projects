#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void dp(vector<vector<int>> &map_table,int n,int k);
int find_max(vector<vector<int>> &arr,int n,int m);
int find_max(vector<vector<int>> &arr,int n,int m){
    int temp = arr[0][0];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0;j< m;j++){
            temp = std::max(temp,arr[i][j]);
        }
    }
    return temp;
}

void dp(vector<vector<int>> &map_table,int n,int allow_k){
    vector<vector<int>> dp_table(n+2,vector<int> (allow_k+1,0));
    vector<vector<int>> temp_table(n+2,vector<int> (allow_k+1,0));
    for(int i = 1 ; i < n+1 ; i++){
        for(int j = 0 ; j <= allow_k ; j++){
            dp_table[i][j] = map_table[n-1][i-1];
        }
    }
    vector<vector<int>>* dp = &dp_table;
    vector<vector<int>>* t = &temp_table;
    vector<vector<int>>* temp_ptr;
    for(int i = n-1; i>=1 ; i--){
        for(int j = 1 ; j < n+1 ; j++){
            for (int k = 0 ; k <= allow_k ; k++){
                if (k==0){
                    (*t)[j][k] = map_table[i-1][j-1] +max({(*dp)[j-1][k],(*dp)[j+1][k]});
                }
                else{
                    (*t)[j][k] =  map_table[i-1][j-1] + max({(*dp)[j-1][k],(*dp)[j+1][k],(*dp)[j][k-1]});
                }
            }
        }
        temp_ptr = dp;
        dp = t;
        t = temp_ptr;

    }
    cout << find_max(*dp,n+2,allow_k+1);
    return ;

}
int main() {
    int n,k;
    cin>>n >> k;
    vector<vector<int>> map_table(n,vector<int> (n,0));
    for(int i = 0 ; i < n ; i++){
        for (int j = 0; j< n ; j++){
            cin>>map_table[i][j];
        }
    }        
    dp(map_table,n,k);
    return 0;
}

