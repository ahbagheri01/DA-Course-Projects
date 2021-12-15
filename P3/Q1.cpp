#include <bits/stdc++.h>
using namespace std;
void find_pal_sub(unordered_set<string>& palindromic,string& input,int low,int high){
    while(low >=0 & high <= input.length()&input[low] == input[high]){
        palindromic.insert(input.substr(low, high - low + 1));
        low--;high++;
    }
}
void find_even(unordered_set<string>& palindromic,string& input,int index){
    find_pal_sub(palindromic,input,index,index+1);

}
void find_odd(unordered_set<string>& palindromic,string& input,int index){
    find_pal_sub(palindromic,input,index,index);
}
int countAll(string& input){
    unordered_set<string> palindromic;
    for(int index = 0 ; index < input.length();index++){
        find_even(palindromic,input,index);
        find_odd(palindromic,input,index);
    }
    return palindromic.size();
}
 
int main()
{
    string input;
    cin>>input;
    cout<<countAll(input);
    return 0;
}