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

- **Container with most water**  
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


