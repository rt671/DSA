#include <iostream>
#include <vector>
using namespace std;

void subseq(vector<int>& arr, int idx, vector<int> ans)
{
    if(idx>=arr.size()) {for(auto it: ans) cout<<it<<" "; cout<<endl; return;}
    ans.push_back(arr[idx]);
    subseq(arr, idx+1, ans);
    ans.pop_back();
    subseq(arr, idx+1, ans);
}

int main()
{
    vector<int> arr = {1,2,3,4};
    subseq(arr, 0, {});
    return 0;
}