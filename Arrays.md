# Arrays

## PARTITION PROCESS OF QUICKSORT
- Sort an array of 0’s, 1’s and 2’s   (CODE BELOW)
- 3 way partitioning of an array around a range (less than, between, greater than) (Order not important)
- Remove duplicates from sorted array
- Move all negative elements to the left (Order not important)
- Rearrange array in alternating +ve and -ve items (Order not important)

```c++
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

## Quick Sort

First find the partition index of the array and then partition it using recursive calls.   
The partition function needs to do the swapping and return the index of the sorted position value, so as QuickSort() can divide the array accordingly.   
```c++
int partition (int arr[], int low, int high)
    {
       int i = low+1, j = low+1;
       while(j<=high)
       {
           if(arr[j] > arr[low]) j++;
           else swap(arr[i++], arr[j++]);
       }
       swap(arr[low], arr[i-1]);
       return (i-1);
    }
    
    void quickSort(int arr[], int low, int high)
    {
        if(low>=high) return;
        int mid = partition(arr, low, high);
        quickSort(arr, low, mid-1);
        quickSort(arr, mid+1, high);
    }
```

## Merge Sort

Divide the arrays in half and then merge.
```c++
void merge(int arr[], int l, int m, int r)
    {
        vector<int> temp(r-l+1);
        int i = l, j = m+1, k=0;
        while(i<=m && j<=r)
        {
            if(arr[i]>arr[j]) temp[k++] = arr[j++];
            else temp[k++] = arr[i++];
        }
        while(i<=m) temp[k++] = arr[i++];
        while(j<=r) temp[k++] = arr[j++];
        for(int i=0; i<temp.size(); i++)
        {
            arr[l+i] = temp[i];
        }
    }
    
    void mergeSort(int arr[], int l, int r)
    {
        if(l>=r) return;
        int mid = l +(r-l)/2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid+1, r);
        merge(arr, l, mid, r);
    }
```

## Set Matrix Zeroes   
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

1. Can we make the row and column zero in one go? No   
2. Take two arrays for row and column respectively, and mark which ones to set zero   
3. Do the above work in one row and column of the matrix itself. Can it be any row or column? Oh yes. One thing needs to be taken care of: the intersection point of the selected row and column can represent for either that row or that column. Hence, represent one and take a variable for the other.   
```c++
void setZeroes(vector<vector<int>>& matrix) {
        bool row = 1;
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(matrix[i][j]==0) {if(i==0) row=0; else matrix[i][0]=0; matrix[0][j]=0;}
            }
        }
        for(int i=m-1; i>0; i--)
        {
            for(int j=n-1; j>=0; j--)
            {
                if(matrix[i][0]==0 || matrix[0][j]==0) matrix[i][j]=0;
            }
        }
        if(row==0) {
            for(int i=0; i<n; i++) matrix[0][i]=0;
        }
    }
```

## Next Permutation
Find the next permutation of the given array.   

1. Generate all permutations, then find the permutation just larger than it.    
2. Find the least significant index with a strictly smaller value than a value after it. This is so as to replace it with any larger value after it and make it big. Otherwise with all smaller values after, it cannot be done. Then swap it with the upper bound on the right, and sort (actually reverse) all the elements after it.
```c++
  void permutation(vector<int> nums)
  {
     int i = nums.size()-2;
     while(i>=0 && nums[i]>=nums[i+1]) i--;
     if(i<0) {reverse it and return}
     int key = i;
     i = nums.size()-1;
     while(nums[i]<=nums[key]) i--;
     swap(nums[key], nums[i]);
     reverse(nums.begin()+key+1, nums.end());

  }
```

## Maximum Subarray   
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.   

1. Find through all subarrays: three loops, two for the extremes of the subarray and the third one to find the sum  O(n*n*n)   
2. Find through all subarrays: As you move the end pointer, also add the sum O(n*n)   
3. Linearly traverse and find the maximum subarray sum possible with subarray ending at the current index. This can be done by considering two choices: either take that index alone (because usse pehle negative hai) or include the sum of the previous index.   
> dp[i] = max(dp[i-1] + nums[i], nums[i]);
```c++
 int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int ans = INT_MIN;
        for(int i=0; i<nums.size(); i++)
        {
            if(sum<0) sum=nums[i];
            else sum+=nums[i];
            ans = max(sum, ans);
        }
        return ans;
    }
```
This is also called Kadane's Algorithm.

## Find the subarray with maximum sum   

## Rotate Matrix
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise) in place.   

1. Rotate layer by layer
```c++
void rotate(vector<vector<int>> matrix) {
        int n = matrix.size();
        for (int i = 0; i < (n + 1) / 2; i ++) {
            for (int j = 0; j < n / 2; j++) {
                int temp = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - j - 1];
                matrix[n - 1 - i][n - j - 1] = matrix[j][n - 1 -i];
                matrix[j][n - 1 - i] = matrix[i][j];
                matrix[i][j] = temp;
            }
        }
    }
```
2. Take transpose and reverse


## **Merge Intervals**   
Merge all overlapping intervals.   

Sort the list first. Can take a buffer or directly use the last interval of the final interval array, and compare it with next's beginning, if less add it else update the end of the interval.  
```c++
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> ans;
    sort(intervals.begin(), intervals.end());
    ans.push_back(intervals[0]);
    for(int i=1; i<intervals.size(); i++)
    {
        if(ans.back()[1] >= intervals[i][0]) ans.back()[1] = max(ans.back()[1], intervals[i][1]);
        else ans.push_back(intervals[i]);
    }
    return ans;
```

## Count Inversions   
Inversion refers to the pair a[i], a[j] such that i<j and a[i]>a[j];   

**Approach 1**: Check for each element of the array (O(n*n))   
**Approach 2:** Inversions are very easy to count if the array is sorted. Hence, we try to use break the solution into subproblems where the array is sorted and we can count the inversions easily. For this merge sort is the best option. Use merge sort, you will obtain the inversions from both the left half and right half subarray, and the subarrays will be obtained as sorted. You will calcuate more inversions at the merge step.   
Keep a pointer at the beginning of both the subarrays. If left[i]>right[j]; in that case count is all the elements in the right. Else, i++.
Hence, exact same as Merge Sort with a very small change.   
```c++
long long merge(long long arr[], int l, int m, int r)
    {
		   long long count = 0;
        vector<long long> temp(r-l+1);
        int i = l, j = m+1, k=0;
        while(i<=m && j<=r)
        {
            if(arr[i]>arr[j]) {temp[k++] = arr[j++]; count+=m-i+1;}
            else temp[k++] = arr[i++];
        }
        while(i<=m) temp[k++] = arr[i++];
        while(j<=r) temp[k++] = arr[j++];
        for(int i=0; i<temp.size(); i++)
        {
            arr[l+i] = temp[i];
        }
		return count;
    }
```
## Majority Element    
Find the element which appears more than half of the size of the array.   

1. Consider each element, and count its frequency   
2. Count the frequencies in a map, and return the one with the maximum     
3. Sort the array and return the middle element   
4. There are enough majority elements to cancel the non-majority elements. Hence, consider any element as majority, add support if same element found, else reduce support. If the support gets 0, change the majority element to the next one. Eventually the actual majority element will be present.
```c++
int majorityElement(vector<int>& nums) {
        int maj = nums[0];
        int cnt=0;
        for(int i=0; i<nums.size(); i++)
        {
            if(cnt==0) {maj = nums[i]; cnt++;}
            else if(nums[i]==maj) cnt++;
            else cnt--;
        }
        return maj;
    }
```
## Majority Element II   

## 2SUM, 3SUM, 4SUM
Handling duplicates: can skip them simply in the case we have got the indices, otherwise not.

## **Longest Consecutive Sequence**   
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.   

1. Sorting O(nlogn)   
2. Use approach 1 but start for only those whose previous element is not present, because otherwise that element would have been counted. O(n)   
```c++
 int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st;
        int ans = 0;
        for(int i=0; i<nums.size(); i++)   st.insert(nums[i]);
        
        for(int i=0; i<nums.size(); i++)
        {
            if(st.find(nums[i]-1) == st.end())
            {
                int temp = nums[i];
                int cnt=0;
                while(st.find(temp)!=st.end()) {cnt++; temp++;}
                ans = max(cnt, ans);
            }
        }
        return ans;
    }
```

## **Largest subarray with 0 sum**   

1. Consider all subarrays   
2. Take the cumulative sums, if it is zero for an element: possible OR if it is same as cum sum at any previous index: possible. To find this, use map.   
```c++
int maxLen(vector<int>&arr, int n)
    {   
        int cusum=0;
        unordered_map<int,int> mp;
        int ans=0;
        for(int i=0; i<n; i++)
        {
            cusum+=arr[i];
            if(cusum==0) ans=max(ans, i+1);
            else if(mp.find(cusum)!=mp.end())
            {
                ans=max(ans, i-mp[cusum]); continue;
            }
            mp[cusum]=i;
        }
        return ans;
    }
```

## **Count of subarrays with given xor**   

1. Consider all subarrays   
2. Take the cumulative xor, if it is given k for an element: count++ OR if any previous index contains (element^k) value, then count++. To find this, store the counts for each value in a map.   
```c++
int count(vector<int>&arr, int n, int k)
    {   
        int cuxor=0;
        unordered_map<int,int> mp;
        int ans=0;
        for(int i=0; i<n; i++)
        {
            cuxor^=arr[i];
            if(cuxor==k) ans++;
            if(mp.find(cuxor^k)!=mp.end())
            {
                ans+=mp[cuxor^k];
            }
            mp[cuxor]++;
        }
        return ans;
    }
```

## **Merge two sorted arrays without extra space**   

1. Use extra space, lol   
2. Iterate through both the arrays, and find minimum element everytime to be placed. Hence, if first element is smaller, skip. Else, find the sorted position through insertion of the element of second array. Because this involves shifting etc, rather iterate from the back, and try to find the maximum element everytime.  O(m*n)   
2. Iterate in the first array, and whenever encounter an element that is greater than the jth element of the array 2, then swap that jth element with the last kth (k starts from 0) element of the first array. This is because it is assured that n smaller elements are already placed in first array, so last element needs to go.  O(mlogm + nlogn)   
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

## **Find duplicate in an array of N+1 integers**   
**Approach 1:** Check duplicate for each element (O(n*n), O(1))   
**Approach 2:** Sort the array and check (O(nlogn), O(1))   
**Approach 3:** Use set to store the elements (O(n), O(n))   

These above approaches were general:   
**Approach 4:** Mark as visited, through marking negative. The same array can act as visited array, and negative value means the index has already been visited.  (O(n), O(1))   
**Approach 5:** Swap each element to its sorted position i.e.   
1. if(nums[i]==i+1) i++;     
2. else if(nums[i]==nums[nums[i]-1]) duplicated element found   
3. else swap(nums[i], nums[nums[i]-1])   
(O(n), O(1))
**Approach 6:** Slow and Fast Pointer (The best approach) (O(n), O(1))
Cycle will only appear if there are duplicate elements.    
What about the case of index 4 with value 5 and index 5 with value 4: cycle without duplication:: Not possible.   
Because how will i reach 4, and if i reached 4, then index 5 having 4 again means there's a duplicacy. 0 is the only index which is considered as reached, without being written at any index.   
```c++
 int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        while(slow==0 || slow!=fast)
        {
            fast = nums[nums[fast]];
            slow = nums[slow];
        }
        slow = 0;
        while(slow!=fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
```

## **Find the repeating and missing element**   

1. 

## **Merge two sorted arrays without extra space**   
Given two arrays of size m and n individually sorted, sort both the arrays as a whole.      

**Approach 1:** Using auxiliary array  (Extra space)     
**Approach 2:** Swapping and using insertion to find sorted position. (O(n*n))   
**Approach 3:** Having all elements belonging to an array to their respective arrays and sorting them in the end. O(nlogn +mlogm)      
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
## **Container with most water**  
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