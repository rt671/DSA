# Dynamic Programming
Time complexity of dp: all paramaters multiplied  (Example: mn in case of Grid dp, moving right and down)  
Time complexity of recursion: (options)^(all parameters multiplied)  (Example: 2^(m*n) in case of Grid dp, moving right and down)

Recursion (exponential, (linear) stack space) -> Memoization (polynomial, (linear) stack space + dp storage) ->  Tabulation (polyonomial, dp storage only) -> space optimized tabulation (polynomial, constant space)  

Why Greedy cannot be applied? There is no uniformity along the steps.  

- ### **Climbing Stairs**  
> Number of steps required to reach the nth stair from the 0th given that you can taken 1 or 2 steps at a time
Number of steps required to reach the nth stair from the 0th => Number of stairs required to reach the n-1th stair + n-2th stair 
```c++
findans(n) { return findans(n-1) + findans(n-2)} //Recursive
t[i] = t[i-1] + t[i-2]; //Iterative
```

- ### **Climbing Stairs with Variable Jumps**  
Number of steps to reach the nth stair => Number of stairs to reach the ?what? (it can be n-1, n-2...; do i know the limit? NO) [depends]  
Hence, twist the definition of subproblem. (reverse the direction)
Number of steps to reach from ith to the nth stair => Sum of number of steps to reach from the for(steps in array) to the nth stair.  
```c++
for(int i=arr.size(); i>=0; i--) { for(all steps in array) t[i]+= t[i+steps];}
```

ANOTHER WAY (Ignore it to avoid confusion in general formation of DP)   
My general formation is go from the given values downwards in any case.   
```c++
t[0]=1;     for(int i=0; i<arr[j]; i++) if(j+i<arr.size()) t[j+i]+=t[i];   //for every stair
```

- ### **Climbing Stairs with Minimum Cost** (1 or 2 steps allowed)   
Minimum cost to reach Nth step => min(Minimum cost to reach (N-1)th step + cost of (N-1)th step, (N-2)th step + cost of (N-2)th step)  
OR
Minimum cost to reach Nth step => min(Minimum cost to reach (N-1)th step, (N-2)th step) + cost of Nth step (In this case, the costs of current steps are included) Hence, finally return min(t[n-1], t[n-2])    
```c++
t[i] = min(t[i-1], t[i-2]) + cost[i];
return min(t[n-1], t[n-2]);
```

- ### **Maximum sum of subsequence with non adjacent elements**  
```c++
Subseq()
{
    if(n==1) return arr[0];
    if(n<1) return 0;
    pick = arr[n-1] + Subseq(n-2);
    noPick = 0 + Subseq(n-1);
    return max(pick,noPick);
}
```

- **House Robber 2: Circular arrangement**  (Find maximum money such that non adjacent)  
Find the max money removing the first element, then removing the last element, and the max of both.  

- **[Ninja's Training](https://www.codingninjas.com/codestudio/problems/ninja-s-training_3621003?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)**  
In this case, we need to keep in account the activity done on the last day, hence two parameters in recursion. While in the non adjacent case, skipping or not skipping was implicit, just because there were only two options. We could have made a 2D matrix for both the options there also, but rather we used the last value for skipping and last to last value for not skipping.  

- **[Stone Game](https://leetcode.com/problems/stone-game/)**  

## DP ON SUBSEQUENCES/SUBSETS  (0-1 KNAPSACK VARIANTS)
Once choices are identified, the next thing is to write the recurrence relation. This not only includes simply making the call changing the parameters but it should also be thought that what are the return values. 

- ### **Subset with Sum K**    
Return True if present.   

Approach: From all subsets, find if there's any present with sum k. To find subset -> recursion (because take/not take choices). Next, what's the recurrence relation -> f(idx-1, k) will return true if it found a subset till idx-1. This also helps in forming base cases.

```c++
if(k==0) return true;
if(idx<0) return false;

if(k>=arr[idx]){ if(findans(idx-1, k-arr[idx])) return true;}
if(findans(idx-1, k)) return true;
return false;
```
But this will exceed the Time Limit. There are overlapping subproblems in this case. Use memoization.   
What about tabulation?
1. What should be the array dimensions (what represents the row and what represents the column)   
2. What should be the base condition (fill the base cases first)   
3. Write the recurrence relation   
```c++
vector<vector<bool>> t(n+1, vector<bool>(k+1));
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=k; j++)
		{
			if(j==0) t[i][j]=true;
			else if(i==0) t[i][j]=false;
			else 
			{
				bool a =false;
				//take it
				if(j>=arr[i-1]) a=t[i-1][j-arr[i-1]];
				//don't take it
				t[i][j] = a | t[i-1][j];
			}
		}
	}
```
- ### **Minimum subset difference in a set**   
Partition a set into two subsets such that the difference of subset sums is minimum. Return the difference.   

A subset with sum closest to the half of total sum will give the answer. Find if subset exists with sum total_sum/2. In the tabulation, the last row will show true for all sum values till total_sum/2 which can be formed. Take the one closest to the end (total_sum/2).   

- ### **Count of subsets with given sum**   
Same code as return true if present, just add instead of doing OR. But, for cases having 0 or negatives in the subset, we cannot have the base case as ```if(sum==0) return 1;```, because we need to move ahead. So in such cases we will add a 1 also to take+non_take while returning.   

- ### **Count of partitions of set into two subsets with given difference**   

S1+S2 is known and S1-S2 is given. Done!

- ### **0-1 Knapsack**   
We checked if subset exists with given sum, we also found the count. Now we need to find one particular subset with sum closest to that sum with the condition of maximum profit.   

**Note:** There are cases when you have negative conditions for base cases in recursion but this is not possible in tabulation. Hence, it is better to avoid having negative values just when making the calls.   
Hence, the base condition can simply be ```if(W==0||n==0) return 0;``` (no need to have condition for W<0)   

So, the approach is simple,   
1. There are choices of taking and not taking, hence two calls and function will be f(idx, W)   
2. f(idx, w) is the function and returns the maximum profit till that index with weight W   
3. With having the f() values of choices (taking and not taking) take the max of them and return    

[Identify choices: Identify the meaning of the cell: Identify what to do with that cell]   

- ### **Target Sum: Count of ways to assign signs (+/-) to given array to produce output 3**   

Two choices for every index: + or -. Similar to take/non-take funda   
Another way, consider all positives as one set, and all negatives as one set: Their difference will give the target. Their sum can be easily calculated. Done!

- ### **Total number of ways to reach a target with infinite number of supplies of given coin array**   
```c++
if(target>=arr[idx]) take = findans(idx, target-arr[idx]);
not_take = findans(idx-1, target);
return take+not_take;
```

- ### **Unbounded Knapsack**   
Instead of adding as in previous case, find maximum of the profits for both the options.   


## DP ON STRINGS   

- ### **Longest Common Subsequence**   

## DP ON STOCKS   

- ### **Best time to buy and sell stocks**   

For any index, considering it as the selling day, the minimum element before that index will be the best day to buy.   
```c++
int least=prices[0];
int maxim=0;
for(int i=0; i<prices.size(); i++)
{
	if(prices[i]<least) least=prices[i];
	maxim = max(maxim, prices[i]-least);
}
```
- ### **Buy and Sell Stock 2**   
Infinite number of buys and sells are allowed, but a stock should be sold before another buy.   

Approach:   
1. There are OPTIONS on each element (buy/don't buy)   
2. Find the changing parameters for recursion --> index and a boolean buy to track if bought or not   
3. Find the return value, for base case --> profit
4. Find the recurrence relation (what to optimize)
```

   

