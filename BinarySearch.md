# Binary Search   

search in rotated sorted array: 1 0 1 1 1
sliding window median


## Find nth root of M   
To find it with precision of upto 6 decimal places.   
```c++ 
while((high-low)>1e-6){}
```

## Matrix median   
Find the median of a row-wise sorted matrix   
Example: A = [1, 3, 5]   
             [2, 6, 9]   
             [3, 6, 9]   
Median is 5.   

1. Add elements in a 1D array, sort and find the median   
2. We cannot use extra memory, so we can’t actually store all elements in an array and sort the array.
But since, rows are sorted it must be of some use, right?    

Note that in a row you can binary search to find how many elements are smaller than a value X in O(log M).
This is the base of our solution.   

Say k = N*M/2. We need to find (k + 1)^th smallest element.
We can use binary search on answer. In O(N log M), we can count how many elements are smaller than X in the matrix.   

```c++
int findMedian(vector<vector<int> > &arr) {
    int m = arr.size();
    int n = arr[0].size();

    int half = (m*n)/2;
    //find low and high
    int low = INT_MAX, high = INT_MIN;  
    for(int i=0; i<m; i++)   //O(n)
    {
        low = min(arr[i][0], low);
        high = max(arr[i][n-1], high);
    }

    int res=-1;
    while(low<=high)
    {
        int mid = low + (high-low)/2;
        int smallcnt = 0;
        for(int i=0; i<m; i++)  //O(mlogn)
        {
            smallcnt += upper_bound(arr[i].begin(), arr[i].end(), mid) - arr[i].begin();
        }

        if(smallcnt <= half) low=mid+1;
        else 
        {
            res=mid;
            high = mid-1;
        }
    }
    return res;
}
```


## Single element in a sorted array   
Given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once. Return the single element that appears only once.    

1. Do XoR of all O(n)   
2. Binary Search O(logn)   
```c++
int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int low = 0, high = n-1;
        while(low<=high)
        {
            int mid = low + (high-low)/2;
            //cout<<mid<<endl;
            if(mid<n-1 && nums[mid]==nums[mid+1]) {if(mid%2==0) low = mid+2; else high = mid-1;}
            else if(mid>0 && nums[mid]==nums[mid-1]) {if(mid%2==0) high=mid-2; else low=mid+1;}
            else return nums[mid];
        }
        return -1;
    }
```

## Search in a sorted rotated array   

```c++
    int search(vector<int>& arr, int target) {
        int n = arr.size();
        int low = 0, high = n-1;
        if(n==1) {if(arr[0]==target) return 0; else return -1;}
        int pivot;
        while(low<=high)
        {
            int mid = low + (high-low)/2;
            int next = (arr[(mid+1)%n]);
            int prev = (arr[(mid+n-1)%n]);
            if(arr[mid]==target) return mid;
            else if(arr[mid]<next && arr[mid]<prev) {pivot = mid; break;}
            else if (arr[mid] < arr[n-1]) high=mid-1;
            else low=mid+1;
        }
        
        if(target <= arr[n-1]) return bsearch(arr, target, pivot, n-1);
        else return bsearch(arr, target, 0, pivot-1);
    }
```
In the above solution, i was chosing to go to the unsorted partition to find the pivot.    
We also can directly look for target and forget about pivot. We use again the property that one side will be sorted. Hence check if the target can be present in that partition, if yes, go there, else move to unsorted part. If we move to the sorted part, both parts will now be sorted but that doesn't cause any problem. 

```c++
int search(vector<int>& nums, int target) {
        
        int n=nums.size();
        int l=0, h=n-1;
        int minidx=-1;
        while(l<=h)
        {
            int mid = l+(h-l)/2;
            if(nums[mid]==target) return mid;
            else if(nums[l]<=nums[mid])
            {
                if(target>=nums[l] && target<nums[mid])
                    h=mid-1;
                else
                    l=mid+1;
            }
            else if(nums[h]>=nums[mid])
            {
                if(target<=nums[h] && target>nums[mid])
                    l=mid+1;
                else
                    h=mid-1;
            }
        }
       return -1;
    }
```