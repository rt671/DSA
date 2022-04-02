# Trees

## Traversals
### Preorder: Just use a stack instead of queue and same as a bfs

## Maximum depth of a tree (HEIGHT): ### max(lh, rh)+1;
## Check if the tree is balanced: ### Height function, with a balance check for each node included. If not balanced, return -1;
## Maximum Diameter of the tree: ### Height function, for each node find the diameter going through that node i.e. lh+rh (store the max diameter in a variable);
```
int findans(TreeNode* root, int* diam)
    {
        if(root==NULL) return 0;
        int maxleft = findans(root->left, diam);
        int maxright = findans(root->right, diam);
        *diam = max(*diam, maxleft+maxright);
        return max(maxleft, maxright)+1;
    }
```
### Note: bottom up approaches are always better (just modifying the height function), rather than a top down in which height function is called separately for each  node
## Maximum path sum in a given binary tree: ### Same as maximum diameter of the tree: For each node, consider the path through it, calculate the maxSum then i.e. lsum+rsum+root->val. If any of the left sum or right sum is negative, assign them 0. Return finally max(lsum, rsum)+root->val;