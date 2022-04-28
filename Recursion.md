# RECURSION   
- Every recursion has an iterative version. Think of finding all subsequences of a string, traverse the array, maintaning a list, and adding on to the list according to the take/not take choices.   (bottom up approach can be applied to any recursion (i.e. table toh bana hi sakte hai), however, if that table is being of any profit (if there are actually any overlapping subproblems), that is a different thing)  

Still choices are associated with recursion. Why?   
- The main property of recursion is that it creates separate solution spaces for different calls. Can consider them running independently.   
  This property primarily helps in cases when there are choices. One separate solution/program running for each choice.It's easy to think in terms of recursion because for each choice we call the function as an independent computation happening.   
- Recursion can also be thought of in the form of recurrence relations (choices eventually structure as rec relations too). This is when there are no choices, but still recursion can be applied because of dependencies in input. (n obtains values from n-1)   

Any recursion can be done by iterations also. Moreover, iterations are better. This is because that same property of separate solution spaces, causes a huge time and space complexity while it doesn't in iteration.   
But why so?   
Those calls we make are generally being repeated (already calculated once), and they create their own separate solution spaces again. Iterations don't create separate solution spaces, they use the values already calculated. Hence, iterations are better here. Actually, this is called dynamic programming.   
Still we use Recursion in many cases, atleast in those involving choices. (The problems under recursion, backtracking and DP)   
Because it is easy to form the solution. For recursion and backtracking, iterative and recursive solutions are equivalent. This is because there's no repetition funda in that case. We have to reach the end.   
But in cases where there are overlapping subproblems, i will never leave the solution just as recursive. I will memoize it or form an iterative solution. This is where Dynamic Programming jumps in.   

Hence, there are two use Recursion can be solved in two ways:   
1. Using recurrence relations (the current depends on previous; current obtains previous' value and operates on it) (For this, mostly iterations are preferred directly)  
2. When there are choices.(Recursion is always the first thought in these cases. Howcver, in case of overlapping subproblems, optimizations of memoization or bottom up approach (iteration) is definitely needed)   

### In short, use Recursion if there are choices. And further, if there are overlapping subproblems do dynamic programming.   

- **Find all the subsequences of an array**   
We have choices: take or not take -> recursion   
```
void subseq(vector<int>& arr, int idx, vector<int> ans)
{
    if(idx>=arr.size()) {print(ans); return;}
    ans.push_back(arr[idx]);
    subseq(arr, idx+1, ans);
    ans.pop_back();
    subseq(arr, idx+1, ans);
}
```

- **Find all the subsequences with sum k**   
```
void subseq(vector<int>& arr, int idx, vector<int> ans, int ansSum, int givenSum)
{
    if(idx>=arr.size() || ansSum>givenSum) {if(ansSum==givenSum) print(ans); return;}
    ansSum+=arr[idx];
    subseq(arr, idx+1, ans, ansSum, givenSum);
    ansSum-=arr[idx];
    subseq(arr, idx+1, ans, ansSum, givenSum);
}
```

- **Find any one subsequence with sum k**   
Same as above with little modification.   
> Whenever required 'any one', use this true-false way  
```
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

- **Count of all subsequences with sum k**   
Same as above, just replace the boolean true and false with integer 1 and 0.
In general:
```
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