

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef struct p{
    int start = 0;
    int end = 0;
    bool  has_diamond = false;
} interval;
int greedy(vector<interval>* p,int n);

int main() {
    int n,m;
    cin>>n >> m;
    int row , col;
    vector<interval> diamonds(n) ;
    for(int k = 0;k < m ; k++){
        cin>>row>>col;
        row--;
        col--;
        if (!diamonds[row].has_diamond){
            diamonds[row].start = col;
            diamonds[row].end = col;
            diamonds[row].has_diamond = true;
            continue;
        }
        if(diamonds[row].start > col)
            diamonds[row].start = col;
        else if (diamonds[row].end < col)
            diamonds[row].end = col;
    }
    std::cout << greedy(&diamonds,n);
    return 0;
}

int greedy(vector<interval>* p,int n){
    int templow,temphigh,templength, l,low ,high , row  = 0;
    bool low_allowed,high_allowed;
    while((!((*p)[row].has_diamond)))
        row++;
    l = (*p)[row].end - (*p)[row].start +1;
    low = (*p)[row].start;
    high = (*p)[row].end;
    row++;
    for (;row < n;row++){
        low_allowed = high_allowed = false;
        templow = low;
        temphigh = high;
        if(!((*p)[row].has_diamond)){
            low = max(0,low-1);
            high = min(n-1,high+1);
            continue;
        }
        if (l < ((*p)[row].end -(*p)[row].start+1)) {
            low = max (low -((*p)[row].end - (*p)[row].start +1 - l ) , 0) ;
            high = min((*p)[row].end - (*p)[row].start +1 - l + high,n-1);
            l = (*p)[row].end - (*p)[row].start +1;
        }
        if (low > (*p)[row].start){
            templow = (*p)[row].start;
            l = l + low - templow -1;
            low = templow;
            high = low+l-1;
            continue;
        }
        if (high <  (*p)[row].end){
            temphigh = (*p)[row].end;
            l = l + temphigh - high   -1;
            high = temphigh;
            low = high - l +1;
            continue;
        }

        if ((low -1 < (*p)[row].start && low-1+l-1 >= (*p)[row].end ) ||(high+1 > (*p)[row].end && high+1-l +1  <= (*p)[row].start ) ) {
            if (low - 1 < (*p)[row].start && low - 1 + l > (*p)[row].end) {
                templow = max(0, low - 1);
                low_allowed = true;
            }

            if (high + 1 > (*p)[row].end && high + 1 - l < (*p)[row].start) {
                temphigh = min(n - 1, high + 1);
                high_allowed = true;
            }
            if (low_allowed&&high_allowed){
                low = templow;
                high = temphigh;
            }else if(low_allowed){
                low = templow;
                high = (*p)[row].start+l-1;
            }else{
                high = temphigh;
                low = (*p)[row].end -l+1;
            }

            continue;
        }
        templength = l - ((*p)[row].end - (*p)[row].start +1);
        low = max((*p)[row].start - templength , 0);
        high = min((*p)[row].end + templength , n-1);
    }
    return l;
}

