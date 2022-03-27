# Arrays

Sort an array of 0’s, 1’s and 2’s
```
void findans()
{
  int i=0, j=0, k=nums.size()-1;
  while(j<k)
  {
    if(nums[j]==0) swap(nums[i++], nums[j++]);
    else if(nums[j]==1) j++;
    else swap(nums[k--], nums[j]);
  }
}
```
3 way partitioning of an array around a range  
Duplicates in a string  
Move all negative elements to the left

