# RECURSION   
1. 'Choices' are always associated with recursion. This is because recursion creates separate solution spaces for each different call, which can be considered running independently. Hence for choices, it's easy to think this way.    

2. Recursion is also associated with recurrence relations (choices eventually structure as rec relations too). This is when there are no choices, but still recursion can be applied because of dependencies in input. (n obtains values from n-1)    

In case of overlapping subproblems, this property of creating separate solution spaces itself causes problem, because of creating separate spaces for calls with same parameters too. Hence, memoization is done, and tabulation can further optimize it.    

Every recursion has an iterative version. Think of finding all subsequences of a string, traverse the array, maintaning a list, and adding on to the list according to the take/not take choices. For choices, recursion is preferred as easy to write. For recurrence relations, iteration is preferred.   

Hence, Recursion can be solved in two ways:   
1. Using recurrence relations (the current depends on previous; current obtains previous' value and operates on it) (For this, mostly iterations are preferred directly, we applied recursion on these problems for just practice)  
2. When there are choices.(Recursion is always the first thought in these cases. Howcver, in case of overlapping subproblems, optimization of memoization or bottom up approach (iteration) is definitely needed)   

### In short, use Recursion if there are choices. And further, if there are overlapping subproblems do dynamic programming.   

- ### **Find all the subsequences of an array**   
We have choices: take or not take -> recursion   
```c++
void subseq(vector<int>& arr, int idx, vector<int> ans)
{
    if(idx>=arr.size()) {print(ans); return;}
    ans.push_back(arr[idx]);
    subseq(arr, idx+1, ans);
    ans.pop_back();
    subseq(arr, idx+1, ans);
}
```

- ### **Find all the subsequences with sum k**   
```c++
void subseq(vector<int>& arr, int idx, vector<int> ans, int ansSum, int givenSum)
{
    if(idx>=arr.size() || ansSum>givenSum) {if(ansSum==givenSum) print(ans); return;}
    ansSum+=arr[idx];
    subseq(arr, idx+1, ans, ansSum, givenSum);
    ansSum-=arr[idx];
    subseq(arr, idx+1, ans, ansSum, givenSum);
}
```

- ### **Find any one subsequence with sum k**   
Same as above with little modification.   
> Whenever required 'any one', use this true-false way  
```c++
bool subseq(vector<int>& arr, int idx, vector<int> ans, int ansSum, int givenSum)
{
    if(idx>=arr.size() || ansSum>givenSum) {if(ansSum==givenSum) {print(ans); return true;} return false;}
    ansSum+=arr[idx];
    if(subseq(arr, idx+1, ans, ansSum, givenSum)) return true;
    ansSum-=arr[idx];
    if(subseq(arr, idx+1, ans, ansSum, givenSum)) return true;
    return false;
}
```

- ### **Count of all subsequences with sum k**   
Same as above, just replace the boolean true and false with integer 1 and 0.
In general:
```c++
int findans()
{
    if(base case) {
        if(condition satisfied) return 1;
        else return 0;
    }
    
    option1 = findans();
    option2 = findans();
    ...
    int ans = option1+option2+...;
    return ans;
}
```

- ### **Combination Sum**  
Given an array of 'distinct' integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. The same number may be chosen from candidates an unlimited number of times.  

There are two approaches:   
1. Like unbounded knapsack, traverse index-wise and options are take or not take   
2. Options are all indices, then next time options are all indices after the previous selected index. (If permutations asked, all indices would have the options every time. Here not so as to avoid repetition (A and then B or B and then A should be the same))

>WAY1 (Take/Not Take)
``` c++
void findans(vector<int>& arr, int target, int idx, vector<int> output, vector<vector<int>>& ans)
    {
        if(idx>=arr.size() || target<=0) {if(target==0) ans.push_back(output); return; }
        
        //take it
        if(target>=arr[idx]){
        output.push_back(arr[idx]); 
        findans(arr, target-arr[idx], idx, output, ans);
        output.pop_back();
         }
        //don't take it
        findans(arr, target, idx+1, output, ans);
    }
```
>WAY2 (Which index to take?)
```c++
void findans(vector<int>& arr, int target, int idx, vector<int> output, vector<vector<int>>& ans)
    {
        if(idx>=arr.size() || target==0) { if(target==0) ans.push_back(output); return;}
        
        for(int i=idx; i<arr.size(); i++)
        {
            if(arr[i]>target) continue;
            output.push_back(arr[i]);
            findans(arr, target-arr[i], i, output, ans);
            output.pop_back();
        }
    }
```
TC: O(n^(t/m))   
SC: O(n)

- ### **Combination Sum 2**  
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target. Each number in candidates may only be used once in the combination.   

Approach:      
WAY1 of combination sum:
1. Out of k occurences of a number, if one is in the subset, it can be anyone. Similarly if 2 occ present, can be any 2.   
Sort the array. If you select the element, you can go to next element easily. If you don't select the element (which means you are satisfied with the number of occurences), go to the next distinct element, as you don't want anymore occurences of that element.   
2. This can also be thought of in terms of counts. Create a table with distinct values and their counts. Now, instead of having unlimited choices, you have that occurence number of choices for each element. You can run a for loop and recurse for every count starting from 0. 

WAY2 of combination sum:   
Same logic + one more logic, while choosing which index to take, consider only the starting elements of each group of same elements.   
>WAY 1
```c++
void findans(vector<int>& arr, int target, int idx, vector<int> output, vector<vector<int>>& ans)
    {
        if(idx>=arr.size() || target<=0) {if(target==0) ans.push_back(output); return;}
        
        //take it
        if(arr[idx]<=target)
        {
            output.push_back(arr[idx]);
            findans(arr, target-arr[idx], idx+1, output, ans);
            output.pop_back();
        }
        else return;
        
        //don't take it
        while(idx<arr.size()-1 && arr[idx]==arr[idx+1]) idx++;
        findans(arr, target, idx+1, output, ans);
    }
```

>WAY 2
```c++
void findans(vector<int>& arr, int target, int idx, vector<int> output, vector<vector<int>>& ans)
{
    if(idx>=arr.size() || target<=0) {if(target==0) ans.push_back(output); return;}
    for(int i=idx; i<arr.size(); i++)
    {
        if(i>idx && arr[i]==arr[i-1]) continue;
        if(target<arr[i]) continue;
        output.push_back(arr[i]);
        findans(arr, target-arr[i], i+1, output, ans);
        output.pop_back();
    }
}
```
TC: O(2^n)   
SC: O(n) (auxiliary stack space)

### Hence, for choices over elements of an array, can be dealt in two ways:   
### 1. Take/Don't take over indices linearly
### 2. Which index to take now?

- ### **[Permutations](https://leetcode.com/problems/permutations/)** 
Given an array nums of distinct integers, return all the possible permutations.

Same as when finding all possible combinations. There were two ways: select which index, and take/not take. The latter one will not work here, as there is no option of not taking here. Proceed by index method. The only change is here the next element should not be after the previous selected index but anywhere. (Hence, ``` for(int i= 0 (NOT idx); i<arr.size(); i++) ```). Also, we need to keep track of which elements have already been selected so as to not to repeat them. Hence, keep a boolean array.   

An optimization over the above method, where we can save space corresponding to that boolean array.   
Go index-wise, choose the 0th index, then the 1st, then 2nd..... and swap the different indices to that place.... Intelligent, hehe   
For first call, we choose the 0th index, and there are n options, because each index is swapped with 0th index.   
Output array is also not needed.
```c++
void thisone(vector<vector<int>>& ans, vector<int> nums, int index)
    {
        if(index>=nums.size()) {  ans.push_back(nums);   return; }
        for(int i=index; i<nums.size(); i++)
        {
            swap(nums[index], nums[i]);
            thisone(ans, nums, index+1);
            swap(nums[index], nums[i]);
        }
    }
```
TC: O(n!*n) (n(n-1)(n-2).... calls being made, and finally for each permutation (there are n!), wehave o(n) for storing in result)   
SC: O(Auxiliary stack space: n) + O(storing the result: n!)   


## Permutation 2

```c++
void permute(vector<int>& arr, vector<int>& psf, vector<vector<int>>& res, unordered_map<int,int>& freq)
    {
        if(psf.size() == arr.size())
        {
            res.push_back(psf);
            return;
        }
        
        for(int i=0; i<arr.size(); i++)
        {
            if((i==0 || arr[i]!=arr[i-1]) && freq[arr[i]])  // brackets important
            {
                freq[arr[i]]--;
                psf.push_back(arr[i]);
                permute(arr, psf, res, freq);
                psf.pop_back();
                freq[arr[i]]++;
            }
        }
    }
```

- ### **Palindrome Partitioning**   
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.   
Again, there are choices, **have partition at which index??**
```c++
void findans(string s, int idx, vector<string> output, vector<vector<string>> &ans)
    {
        if(idx==s.size()) {ans.push_back(output); return;}
        for(int i=idx; i<s.size(); i++)
        {
            //check if can be partitioned at i 
            //for that check palindrome the string from idx to i, both inclusive
            if(checkPal(s.substr(idx, i-idx+1))==false) continue;

            output.push_back(s.substr(idx, i-idx+1));
            findans(s, i+1, output, ans, palin);
            output.pop_back();
        }
    }
```
Dp can be applied so as to not check if a substring is a palindrome, again and again.   
TC: O((2^n) *n)   
SC: O(n)

## Permutation with duplicate elements   