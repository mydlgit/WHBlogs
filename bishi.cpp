#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    int tmp;
    while(cin>>n){
       vector<int> vec;
       unordered_set<int> uset;
       for(int i=0;i<n;i++){
           cin>>tmp;
           if(uset.count(tmp)==0){
               uset.insert(tmp);
               vec.emplace_back(tmp);
           }
       }
       sort(vec.begin(), vec.end());
       for(auto &v:vec)cout<<v<<endl;
    }
    return 0;
}
