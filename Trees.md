# Trees

### Iterative Traversals
- **Inorder:**  
```c++
 vector<int> inorderTraversal(TreeNode* root) {
        
        vector<int> ans;
        stack<TreeNode*> st;
        while(root || !st.empty())
        {    
            while(root)
            {
                st.push(root);
                root=root->left;
            }
            TreeNode* temp = st.top();
            st.pop();
            ans.push_back(temp->val);
            root=temp->right;
        }
        return ans;
    }
```
Another way is using morris traversal, which uses the property that the current element will after its inorder predecessor, hence can be formed as the right child of it.   
For every node, make it the right child of its inorder predecessor (the rightmost child in the left subtree) and hence it gets temporarily rid of the left child, gradually converting into a skewed inorder tree.    

Step 1: Initialize current as root   
Step 2: While current is not NULL,   
If current does not have left child      
    a. Add current’s value   
    b. Go to the right, i.e., current = current.right   
Else   
    a. In current's left subtree, make current the right child of the rightmost node   
    b. Go to this left child, i.e., current = current.left   
![morris picture](https://user-images.githubusercontent.com/82562103/171409709-c64b6f4a-1f4d-4269-b285-15c60c1cc960.PNG)

```c++
   vector<int> inorderTraversal(TreeNode* root) {
        vector<int> nodes;
        while (root) {
            if (root -> left) {
                TreeNode* pre = root -> left;
                while (pre -> right && pre -> right != root) {
                    pre = pre -> right;
                }
                if (!pre -> right) {
                    pre -> right = root;
                    root = root -> left;
                } else {
                    pre -> right = NULL;
                    nodes.push_back(root -> val);
                    root = root -> right;
                }
            } else {
                nodes.push_back(root -> val);
                root = root -> right;
            }
        }
        return nodes;
    }
```
- **Preorder:**   
```c++
vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> st;
        while(root || !st.empty())
        {
            while(root)
            {
                ans.push_back(root->val);
                st.push(root);
                root=root->left;
            }
            TreeNode* temp = st.top();
            st.pop();
            root = temp->right;
        }
        return ans;
    }
```

- **Postorder:**

## Leftview   
1. Do level order traversal and print the first node in each level.   
2. Can use recursion as well, whenever the level is more than max so far for the first time, print it.   

## Bottomview   
1. Doing a level order traversal and save ranks in a map (rank-1 for left and rank+1 for right) is the best way.   
2. Recursion can also help: Preorder traversal. But we also need to take care of height/depth, because a later node may update the value of the rank key but it wasn't the lowest. (Do height +1 as well rank+-1, update map only when height is max)

## Topview   
1. Same as bottom view, just update the map the first time only, when key is not present    
2. Same as bottom view, ...............................   

## Vertical Order Traversal   

Do level order traversal and take a map of rank and corresponding list of nodes. There can be multiple nodes at same position, they should be in sorted order. For this we may use a set or heap, but we also want node which came first to remain first even if its value is more. Hence, use a set or minheap of {height, value}. So that first height is considered, if its the same then the value is considered.   
```c++
typedef pair<int,int> pp;

vector<vector<int>> verticalTraversal(TreeNode* root) {
    if(root==NULL) return {};
    
    vector<vector<int>> ans;
    queue<pair<TreeNode*, pair<int,int>>> q;
    q.push({root,{0,0}});
    map<int, priority_queue<pp, vector<pp>, greater<pp>>> mp;
    
    int buffer;
    while(!q.empty())
    {
        int n = q.size();
        for(int i=0; i<n; i++)
        {
            TreeNode* p = q.front().first;
            int rank = q.front().second.first;
            int height = q.front().second.second;
            q.pop();
            
            mp[rank].push({height, p->val});
            if(p->left) q.push({p->left, {rank-1, height+1}});
            if(p->right)  q.push({p->right, {rank+1, height+1}});
        } 
    }
    for(auto it: mp) 
    {
        vector<int> temp;
        while(!it.second.empty()) {temp.push_back(it.second.top().second); it.second.pop();}
        ans.push_back(temp);
    }
    return ans;
}
```

## Height
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

