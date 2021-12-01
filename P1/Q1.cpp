#include <iostream>
#include <vector>
using namespace std;
typedef struct p{
    int start;
    int end;
    p( int start_ , int end_ )
    {
        start = start_;
        end = end_;
    }
} interval;
void reverse_arr(int start,int end,int *arr);
void sort_array(int start,int end,int*arr,vector<interval>* out);
int main() {
    int n;
    cin>>n;
    int* array = (int*)malloc(sizeof(int)*n);
    for(int i = 0;i < n ; i++){
        cin>>array[i];
    }
    vector<interval> out;
    sort_array(0,n,array,&out);
    cout<<out.size()<<endl;
    for (int i  = 0; i < out.size();i++){
        cout<<out[i].start<<" "<<out[i].end<<endl;
    }
    return 0;
}
void sort_array(int start,int end,int*arr,vector<interval>* out){
    if (end-start > 1) {
        int middle = (start + end) / 2;
        sort_array(start, middle, arr, out);
        sort_array(middle, end, arr, out);
        if (*(arr + middle - 1) == 1 && *(arr + middle) == 0) {
            int start_of_one = 0;
            int end_of_zero = 0;
            while (middle - 1 - start_of_one >= start && *(arr + middle - 1 - start_of_one) == 1) {
                start_of_one += 1;
            }
            while (*(arr + middle + end_of_zero) == 0 && middle + end_of_zero < end) {
                end_of_zero += 1;
            }
            reverse_arr(middle - start_of_one, middle + end_of_zero - 1, arr);
            out->push_back(interval(middle - start_of_one + 1, middle + end_of_zero));
        }
    }
}
void reverse_arr(int start,int end,int *arr){
    while (start < end ){
        *(arr+end) ^= *(arr+start) ^=*(arr+end) ^= *(arr+start);
        start+=1;
        end-=1;
    }
}


