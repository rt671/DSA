# Binary Search Trees  
The most efficient solution for any BST question can be considered as an O(h) solution.  
Many questions of BST can be solved with the property that inorder is a sorted sequence.  
  
- **Search in a BST**  
In BT, do any traversal (pre/in/post/level): O(n)  
In BST, it's O(logn);
  
- **Ceil in a BST** (Similarly floor)  
In Binary Search, there were two ways: 1. return low    2. whenever moving left, store mid as potential ceil  
The first method can't work here (it will be null), second method works perfectly.  
  
- **Insert into BST**  
Recursive way seems better, as in iterative we have to keep track of the previous element to which we can assign the new element as a child. In recursive, root->left = findans(root->left, target); helps.  
```
TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root) return new TreeNode(val);
        if(root->val > val) root->left = insertIntoBST(root->left, val);
        else root->right = insertIntoBST(root->right, val);
        return root;
    }
```
  
- **Delete from BST**    
Replace with inorder successor (or predecessor) and delete that element (recursively)  
```
TreeNode* inordersucc(TreeNode* root)
    {
        root = root->right;
        while(root->left)
            root=root->left;
        return root;
    }
    
    TreeNode* deleteNode(TreeNode* root, int key) {
        
        if(root==NULL) return root;
        if(root->val == key)
        {
            if(root->left==NULL) return root->right;
            if(root->right==NULL) return root->left;
            
            TreeNode* temp = inordersucc(root);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
            return root;
        }
        else if(root->val > key) root->left = deleteNode(root->left, key);
        else root->right = deleteNode(root->right, key);
        return root;
    }
``` 

- **Kth smallest element in a BST**  
The inorder traversal gives the sorted order, store the inorder in an array and return arr[k-1]; Or stop the inorder traversal at reaching kth node. This can done both in recursion or iteration. In iteration it is easier.  
```c++
while (true) {
      while (root != null) {
        stack.push(root);
        root = root.left;
      }
      root = stack.top();
      stack.pop();
      if (--k == 0) return root.val;
      root = root.right;
    }

    
```
> Time Complexity: O(h+k); (h to reach down the leaf first (root->left))  
> Space Complexity: O(h)

- **Populating next right pointers in a tree**   
Given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

```c++
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.   

1. Use Level Order Traversal   
2. Use the property that it is a perfect binary tree.   
```c++
    Node* temp = root;
    while(temp->left)
    {
        Node* curr = temp;
        while(curr)
        {
            curr->left->next = curr->right;
            if(curr->next) curr->right->next = curr->next->left;
            curr = curr->next;
        }
        temp=temp->left;
    }
```
- **Convert Sorted Array to Height Balanced Binary Search Tree**    

```c++
TreeNode* findans(vector<int>& nums, int low, int high)
    {
        if(low>high) return NULL;
        int mid = low +(high-low)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = findans(nums, low, mid-1);
        root->right = findans(nums, mid+1, high);
        return root;
    }
```


- **Validate a BST** (Check if a BT is a BST)   

1. Considered lower bounds and upper bounds
```c++
 bool findans(TreeNode* root, long long lb, long long ub)
    {
        if(root==NULL) return true;
        if(root->val>ub || root->val<lb) return false;
        return findans(root->left, lb, (long long)root->val-1) && findans(root->right, (long long)root->val+1, ub);
    }
```

2. Better way, check if inorder is sorted (if next element is greater than previous, for every node traversed)
```c++
 bool isValidBST(TreeNode* root) {
        TreeNode* prev = NULL;
        stack<TreeNode*> st;
        while(root || !st.empty())
        {
            while(root)
            {
                st.push(root);
                root=root->left;
            }
            root = st.top();
            st.pop();
            if(prev && root->val <= prev->val) return false;
            prev=root;
            root = root->right;
        }
        return true;
    }
```

- **LCA in BST**   
Simply use BST property
```
 TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
        if(root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);
        return root;
    }
```

- **Construct BST from preorder traversal**  
**Approach 1** Consider the preorder as list of keys and just call insert() for each. O(N^2)  
**Approach 2** Store the sorted preorder as inorder, now generate the binary tree O(NlogN +N)  
**Approach 3** Instead of separately storing the inorder, try to incorporate the BST property while using preorder traversel itself. O(NlogN) will be saved.  
> **Example:**
> Preorder: 8 5 1 7 10 12
> Initialize UpperBound as INT_MAX; 
> Node 8: Less than upper bound, insert it.
> Now left child has upper bound 8, and right INT_MAX 
> Node 5: less than 8, insert to the left, move to left with upper bound 5
> Insert Node 1, move to left with upper bound 1
> With upper bound as 1, node 7 cannot be inserted, return back
> Move to the right, upper bound is 5 (LEFT CHILD OF NODE 1 HAS UBOUND 1 AND RIGHT CHILD HAS UBOUND 5 (That of the node))
> Still Node 7 cannot be inserted, return back
> Move to the right (of 5), upper bound is 8. Node 7 can be inserted

> ![BST from preorder](https://user-images.githubusercontent.com/82562103/161968384-c5faf2d5-f0a1-4e3d-856d-dcdcf768b44f.png)

- **Inorder successor of a given value in BST** (or predecessor)   
**Approach 1:** Brute Force - Store the inorder (O(n)), search for the value and return the next element (Binary Search can be applied in this case, though there's no benefit) TC: O(n)    SC: o(n)  
**Approach 2:** Perform inorder traversal (iterative is better in such a case), return the first value encountered greater than the given value. TC: O(n)    SC: o(1) (NOT CONSIDERING STACK SPACE/ OR DO MORRIS TRAVERSAL)  
**Approach 3:** Kinda go with the BST flow      TC: O(h)    SC: o(1)  
```
potentialAns=NULL;
while(root) {
    if(root->val <= givenVal) root=root->right;  //left subtree can simply be ignored
    else if(root->val > givenVal) {potentialAns = root->val; root=root->left; } //right subtree can simply be ignored
}
return potentialAns;
```

- **BST Iterator**  
Approach 1: Store the inorder in the vector, and hehe  
Approach 2: Do iterative inorder traversal, just move it's different segments into corresponding functions.  
```
  int next() {
        while(root) {st.push(root); root=root->left;}
        root = st.top(); st.pop();
        int temp = root->val;
        root=root->right;
        return temp;
    }
    
    bool hasNext() {
        return (root || !st.empty());
    }
```
- **Trim BST**  
Trim BST so that all its elements lie in [low, high]  
```
TreeNode* deleteit(TreeNode* root, int low, int high)
    {
        if(root==NULL) return NULL;
        if(root->val < low) {root = deleteit(root->right, low, high);}
        else if(root->val > high) {root = deleteit(root->left, low, high);}
        else
        {
            root-> left = deleteit(root->left, low, high);
            root-> right = deleteit(root->right, low, high);
        }
        return root;
    }
```

- **Two sum in BST**    

1. For every element, do a binary search in the bst (O(nlogn), O(1))   
2. Use a set, do a search and check for k-node->val for each node. (O(n), O(n))   
3. Find the inorder, store in an array and do two sum (O(n), O(n))
4. Use BST iterators and do two sum directly on the BST hence. (O(n), O(h))
```c++
class BSTiterator{
private:
    stack<TreeNode*> st;
    TreeNode* temp;
    bool reverse;
public:   
    BSTiterator(TreeNode* root, bool val)
    {
        temp = root;
        reverse = val;
    }
    
    int next()
    {
        while(temp){st.push(temp); if(!reverse)temp = temp->left; else temp=temp->right;}
        TreeNode* a = st.top();
        st.pop();
        if(!reverse) temp = a->right; else temp=a->left;
        return a->val;
    } 
    
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        BSTiterator low(root, 0);
        BSTiterator high(root, 1);
        
        int i=low.next(), j=high.next();
        while(i<j)
        {
            if(i+j > k) j = high.next();
            else if(i+j <k) i = low.next();
            else return true;
        }
        return false;
    }
};
```
- **Recover BST**  
The values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.    

1. Store inorder and find two elements where arr[i-1]>arr[i]; OR using the inorder, reassign all the values of the tree     
2. Do the same step, just don't store, do on the way   
>This function finds the two elements to be swapped.   
```c++
void inorder(TreeNode* root)
    {
        if(root==NULL) return;
        inorder(root->left);
        if(prev->val > root->val)
        {
            if(flag==0) {firstele = prev; flag=1; secondele =root;}
            else { secondele = root;}
        }
        prev = root;
        inorder(root->right);
    }
```   
- **Largest BST in BT**   

