# Greedy   

## N meetings in one room    
Sort according to the earliest finish time.   

## Jump Game II   
```c++
int i=0;
int end = 0;
int cnt = 0;
while(i<=n && end<n)
    {
        cnt++;
        int maxpossible = 0;
        while(i<=n && i<=end)
        {
            maxpossible = max(maxpossible, ranges[i++]);
        }
        if(maxpossible == end) return -1;
        end = maxpossible;
    }
```