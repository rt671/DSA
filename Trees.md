# Trees

### Iterative Traversals
- **Preorder:** Just use a stack instead of queue and same as a bfs  
- **Inorder:**  
- **Postorder:**

### Height
- **Maximum depth of a tree (HEIGHT):**  
max(lh, rh)+1;
- **Check if the tree is balanced:**  
Height function, with a balance check for each node included. If not balanced, return -1;
- **Maximum Diameter of the tree:**  
Height function, for each node find the diameter going through that node i.e. lh+rh (store the max diameter in a variable);
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
Note: bottom up approaches are always better (just modifying the height function), rather than a top down in which height function is called separately for each  node
- **Maximum path sum in a given binary tree:**  
Same as maximum diameter of the tree: For each node, consider the path through it, calculate the maxSum then i.e. lsum+rsum+root->val. If any of the left sum or right sum is negative, assign them 0. Return finally max(lsum, rsum)+root->val;

### Advanced Traversals
- **ZigZag Traversal**  
Same as Level Order, just reverse the order alternatively (How? By not using reverse function, but filling the answer vector directly in reverse order)
- **Boundary Traversal**  
```
void leftone(Node* root, vector<int>& ans)
    {
        if(root==NULL) return;
        if(root->left==NULL && root->right==NULL) return;
        ans.push_back(root->data);
        leftone(root->left, ans);
        if(root->left==NULL) leftone(root->right, ans);
    }
    
    void rightone(Node* root, vector<int>& ans)
    {
        if(root==NULL) return;
        if(root->left==NULL && root->right==NULL) return;
        rightone(root->right, ans);
        if(root->right==NULL) rightone(root->left, ans);
        ans.push_back(root->data);
    }
    
    void leaves(Node* root, vector<int>& ans)
    {
        if(root==NULL) return;
        if(root->left==NULL && root->right==NULL) ans.push_back(root->data);
        leaves(root->left, ans);
        leaves(root->right, ans);
    }
    
    vector <int> boundary(Node *root)
    {
        vector<int> ans;
        ans.push_back(root->data);
        leftone(root->left, ans);
        leaves(root->left, ans);
        leaves(root->right, ans);
        rightone(root->right, ans);
        return ans;
    }
```
- **Print path from root to node**  
```
bool findans(TreeNode* root, int target, vector<int>& path)
    {
        if(root==NULL) return false;
        path.push_back(root->val);
        if(root->val == target) return true;
        if(findans(root->left, target, path) || findans(root->right, target, path)) return true;
        path.pop_back();
        return res;
    }
```
- **Print all paths from root to leaves:**   
Here no returning of true or false needed, because backtracking can be applied here. In the last case, as we found the node, we just had to return back totally.
 ```
 void findans(TreeNode* root, string ans, vector<string>& finalans)
    {
        if(root==NULL) return;
        ans+= to_string(root->val);
        if(root->left==NULL && root->right==NULL) {finalans.push_back(ans); return;}
        findans(root->left, ans+"->", finalans); findans(root->right, ans+"->", finalans);
        ans.pop_back();
    }
```
- **Longest Common Ancestor:**  
Return the node if found, else return Null; When a non Null value is returned from both sides, return the node value then. 
>My way
 ```
 bool findans(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode** ans)
    {
        if(root==NULL) return false;
        bool a = findans(root->left, p, q, ans);
        bool b = findans(root->right, p, q, ans);
        if(a&&b || ((a||b) &&(root==p||root==q))) {*ans = root; return true;}
        if(root==p || root==q) return true;
        else return (a||b);
    }
```

> Another good way
```
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL) return NULL;
        if(root==p || root==q) return root;
        TreeNode* a = lowestCommonAncestor(root->left, p, q);
        TreeNode* b = lowestCommonAncestor(root->right, p, q);
        if(a==NULL) return b;
        else if(b==NULL) return a;
        else return root;
    }
```

# Binary Search Trees

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
```
while (true) {
      while (root != null) {
        stack.push(root);
        root = root.left;
      }
      root = stack.pop();
      if (--k == 0) return root.val;
      root = root.right;
    }
  }
```
> Time Complexity: O(h+k); (h to reach down the leaf first (root->left))  
> Space Complexity: O(h)

- **Validate a BST** (Check if a BT is a BST)  
I applied recursion. (1. if null or leaf, return true;  2. if any child false, return false;    3. compare current node value with inorder successor and predecessor)

Better way, check if inorder is sorted (if next element is greater than previous, for every node traversed)
```
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
