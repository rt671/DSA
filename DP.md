# Dynamic Programming

- **Climbing Stairs**  
Number of steps required to reach the nth stair from the 0th => Number of stairs required to reach the n-1th stair + ...  
```
findans(n) { return findans(n-1) + findans(n-2)} //Recursive
t[i] = t[i-1] + t[i-2]; //Iterative
```

- **Climbing Stairs with Variable Jumps**  
Number of steps to reach the nth stair => Number of stairs to reach the **what?** (can be n-1, n-2...) [depends]  
Hence, twist the definition of subproblem.  
Number of steps to reach from ith to the nth stair => Number of steps to reach from the for(steps in array) to the nth stair.  
```
for(int i=arr.size(); i>=0; i--) { for(all steps in array) t[i]+= t[i+steps];}
```

ANOTHER WAY (Ignore it to avoid confusion in general formation of DP)  
```
t[0]=1;     for(int i=0; i<arr[j]; i++) if(j+i<arr.size()) t[j+i]+=t[i];   //for every stair
```

- **Climbing Stairs with Minimum Cost**  
Minimum cost to reach Nth step => min(Minimum cost to reach (N-1)th step + cost of (N-1)th step, (N-2)th step + cost of (N-2)th step)  
OR
Minimum cost to reach Nth step => min(Minimum cost to reach (N-1)th step, (N-2)th step) + cost of Nth step (In this case, the costs of current steps are included) Hence, finally return min(t[n-1], t[n-2])    
```
t[i] = min(t[i-1], t[i-2]) + cost[i];
return min(t[n-1], t[n-2]);
```

