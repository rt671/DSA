## Binary Trees With Factors (LeetCode 823)   
Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.     

We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.    

Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.    

For any valid tree, the largest value v, in that tree, must be the root. So, let's say that dp(v) is the number of ways to make a tree with root node v.   

If the root node of the tree (with value v) has children with values x and y (where x * y == v must be true), then there are dp(x) * dp(y) ways to make this tree.   

Each unique value in A is a valid root value for at least one tree - a tree containing just that node.   

To get the total number of valid trees, we should calculate how many valid trees there are with each possible root value, and then add them all together.   