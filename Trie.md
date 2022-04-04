#Trie
This data structure is used when we need to:   
-> insert a word  
-> check if a word is present  
-> check if there's a word with the given prefix.  

It is a class or struct which contains two elements:  
1. An array of trie pointers, length 26 (considering all lowercase alphabets) (intially all set to NULL)
2. A boolean flag to mark the end of the word

**For example:**   
**Inserting word 'apple'**
The array index of the trie corresponding to 'a' is inserted with the address of new 'reference trie of a' created.   
Then in this reference node of a, the p index is inserted with the address of the newly created 'reference node of p'. And so on.  
When the word ends, the boolean flag of the reference node of the last character (which will have Null array) is set to true.

**Inserting 'apps' now**  
Traverse to the reference node of the second 'p' (created from insertion of 'apple'). Then insert the address of the newly created reference node for 's' in the s index. Now this trie contains two array elements containing the addresses.  

**Why Trie?**  
Searching a word in a database containing a million of words, it will be much easier through a trie. The height of the trie is equal to the length of the longest word.

**Implementing a Trie**  
```
struct Node{
    Node* links[26];
    bool flag=false;
    bool containsKey(char ch) {
        return (links[word[i]-'a']!=NULL)
    }
    Node* get(char ch) {
        return links[ch-'a'];
    }
}

class Trie{
    private: Node* root;
    public:
    Trie()
    {
        root = new Node();
    }

    void insert(string word)
    {
        Node* temp = root;
        for(int i=0; i<word.size(); i++)
        {
            if(!temp->containsKey(word[i])) links[word[i]-'a'] = new Node();
            temp = temp->get(word[i]);
        }
        temp->flag=true;
    }

    bool search(string word)
    {
        Node* temp = root;
        for(int i=0; i<word.size(); i++)
        {
            if(!temp->containsKey(word[i])) return false;
            temp = temp->get(word[i]);
        }
        return temp->flag;
    }

    bool startWith(string prefix)
    {
        Node* temp = root;
        for(int i=0; i<word.size(); i++)
        {
            if(!temp->containsKey(word[i])) return false;
            temp = temp->get(word[i]);
        }
        return true;
    }
}
```