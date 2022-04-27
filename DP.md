# Dynamic Programming
Time complexity of dp: all paramaters multiplied  (Example: mn in case of Grid dp, moving right and down)  
Time complexity of recursion: (options)^(all parameters multiplied)  (Example: 2^(m*n) in case of Grid dp, moving right and down)

Recursion (exponential, (linear) stack space) -> Memoization (polynomial, (linear) stack space + dp storage) ->  Tabulation (polyonomial, dp storage only) -> space optimized tabulation (polynomial, constant space)  

Why Greedy cannot be applied? There is no uniformity along the steps.  

- **Climbing Stairs**  
> Number of steps required to reach the nth stair from the 0th given that you can taken 1 or 2 steps at a time
Number of steps required to reach the nth stair from the 0th => Number of stairs required to reach the n-1th stair + n-2th stair 
```
findans(n) { return findans(n-1) + findans(n-2)} //Recursive
t[i] = t[i-1] + t[i-2]; //Iterative
```

- **Climbing Stairs with Variable Jumps**  
Number of steps to reach the nth stair => Number of stairs to reach the ?what? (it can be n-1, n-2...; do i know the limit? NO) [depends]  
Hence, twist the definition of subproblem. (reverse the direction)
Number of steps to reach from ith to the nth stair => Sum of number of steps to reach from the for(steps in array) to the nth stair.  
```
for(int i=arr.size(); i>=0; i--) { for(all steps in array) t[i]+= t[i+steps];}
```

ANOTHER WAY (Ignore it to avoid confusion in general formation of DP)   
My general formation is go from the given values downwards in any case.   
```
t[0]=1;     for(int i=0; i<arr[j]; i++) if(j+i<arr.size()) t[j+i]+=t[i];   //for every stair
```

- **Climbing Stairs with Minimum Cost** (1 or 2 steps allowed)   
Minimum cost to reach Nth step => min(Minimum cost to reach (N-1)th step + cost of (N-1)th step, (N-2)th step + cost of (N-2)th step)  
OR
Minimum cost to reach Nth step => min(Minimum cost to reach (N-1)th step, (N-2)th step) + cost of Nth step (In this case, the costs of current steps are included) Hence, finally return min(t[n-1], t[n-2])    
```
t[i] = min(t[i-1], t[i-2]) + cost[i];
return min(t[n-1], t[n-2]);
```

- **Maximum sum of subsequence with non adjacent elements**  
```
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