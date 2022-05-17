# Arrays

## PARTITION PROCESS OF QUICKSORT
- Sort an array of 0’s, 1’s and 2’s   (CODE BELOW)
- 3 way partitioning of an array around a range (less than, between, greater than) (Order not important)
- Remove duplicates from sorted array
- Move all negative elements to the left (Order not important)
- Rearrange array in alternating +ve and -ve items (Order not important)

```
void findans()
{
  int i=0, j=0, k=nums.size()-1;
  while(j<=k)
  {
    if(nums[j]==0) swap(nums[i++], nums[j++]);
    else if(nums[j]==1) j++;
    else swap(nums[k--], nums[j]);
  }
}
```
- Move all negative elements to the left (Order is Important)

## 2SUM, 3SUM, 4SUM

- ### **Container with most water**  
Two pointer approach: i=0, j=n-1;  
calculate the area, max it and move the pointer which has smaller height.  
Why this works?  
-> The next to greater can be:
                        -> larger (but no benefit, as the other side is the same) 
                        -> equal (no benefit, width decreased)  
                        -> smaller (oof, no benefit)  
-> The next to smaller can be:
                        -> larger (that's good, chance of improvement)  
                        -> smaller (no benefit, previous one would be better)  
                        -> equal (oof, no benefit)

- ### **Next Permutation**   
The smallest value index with a smaller value than the larger values after it. This is so as to replace it with any larger value after it and make it big. Otherwise with all smaller values after, it cannot be done.   

- ### **Kadane's Algorithm**   
Through the intuition of DP   
sum(arr, idx) denotes the sum of subarray from starting from 0 and ending at index idx.   
sum(arr, idx) = (sum(arr, idx-1)>0 ? sum(arr, idx-1): (0)) + arr[idx];   

dp[i] = max(dp[i-1] + nums[i], nums[i]);

- ### **Merge Intervals**   
Merge all overlapping intervals.   

Can take a buffer or directly use the last interval of the final interval array, and compare it with next's beginning, if less add it else update the end of the interval. Sorting needed first.   

- ### **Find duplicate in an array of N+1 integers**   
Approach 1: Check duplicate for each element (O(n*n), O(1))
Approach 2: Sort the array and check (O(nlogn), O(1))
Approach 3: Use set to store the elements (O(n), O(n))

These above approaches were general:   
Approach 4: Mark as visited, through marking negative. The same array can act as visited array, and negative value means the index has already been visited.  (O(n), O(1))   
Approach 5: Swap each element to its sorted position i.e.   
1. if(nums[i]==i+1) i++;     
2. else if(nums[i]==nums[nums[i]-1]) duplicated element found   
3. else swap(nums[i], nums[nums[i]-1])   
(O(n), O(1))
Approach 6:


- ### **Merge two sorted arrays without extra space**   
Given two arrays of size m and n individually sorted, sort both the arrays as a whole.      

Approach 1: Using auxiliary array  (Extra space)     
Approach 2: Swapping and using insertion to find sorted position. (O(n*n))   
Approach 3: Having all elements belonging to an array to their respective arrays and sorting them in the end. O(nlogn +mlogm)      
```c++
void merge(long long arr1[], long long arr2[], int m, int n) 
        { 
            int i=0, j=0, k=m-1;
    		while(j<n && i<=k)
    		{
    			if(arr1[i]<arr2[j]) i++;
    			else
    			{
    				swap(arr2[j], arr1[k--]);
    				j++;
    			}
    		} 
    		sort(arr1, arr1+m);
    		sort(arr2, arr2+n);
        }
```

- ### **Count the inversions in an array**   
Inversion refers to the pair a[i], a[j] such that i<j and a[i]>a[j];   

Approach 1: Check for each element of the array (O(n*n))   
Approach 2: Inversions are very easy to count if the array is sorted. Hence, we try to use break the solution into subproblems where the array is sorted and we can count the inversions easily. For this merge sort is the best option. Use merge sort, you will obtain the inversions from both the left half and right half subarray, and the subarrays will be obtained as sorted. You will calcuate more inversions at the merge step.   
Keep a pointer at the beginning of both the subarrays. If left[i]>right[j]; in that case count is all the elements in the right. Else, i++.
```c++

```