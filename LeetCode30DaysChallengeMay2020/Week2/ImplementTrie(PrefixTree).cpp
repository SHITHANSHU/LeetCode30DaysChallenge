//Question

/*

Implement Trie (Prefix Tree)
Solution
Implement a trie with insert, search, and startsWith methods.

Example:

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");   
trie.search("app");     // returns true
Note:

You may assume that all inputs are consist of lowercase letters a-z.
All inputs are guaranteed to be non-empty strings.

*/

//Solution 

/*

As they have already given that we have to use prefix tree as a data structure 

a prefix tree data structure which is used to store string or data in a tree like structure

where each of the node act as a alphabet and the next alphabet is child of current alphabet 

eg 
    start
    |
    a
    |
    p
    |
    p           this will be the tree formed by apple
    |
    l
    |
    e  

and if we add "test" to the same tree the

then it will change to 

            start 
            /   \
           /     \
           a      t
           |      |
           p      e
           |      |
           p      s
           |      |
           l      t
           |
           e

now if we add apps word ro the tree it will change to

            start 
            /   \
           /     \
           a      t
           |      |
           p      e
           |      |
           p      s
         / |      |
        /  l      t
       s   |
           e

now we need to keep track of end of word so we need a boolean to tell us if the word has completed or not

we also need to make nodes such that each of them has 26 childern i.e. which means there should be a node

available for each possible alphabet



*/


//Solution 
class Trie {
    Trie* nextCharacter[26];
    bool last;
public:
    /** Initialize your data structure here. */
    Trie() {
        for(int i=0;i<26;i++)
            nextCharacter[i]=NULL;
        last=false;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* thisVal=this;
        for(char c : word)
        {
            if(thisVal->nextCharacter[c-'a']==NULL)
                thisVal->nextCharacter[c-'a']=new Trie();
            thisVal=thisVal->nextCharacter[c-'a'];
        }
        thisVal->last=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        
         Trie* thisVal=this;
        for(char c : word)
        {
            if(thisVal->nextCharacter[c-'a']!=NULL)
                thisVal=thisVal->nextCharacter[c-'a'];
            else
                return false;
        }
        if(thisVal->last)
            return true;
        else
            return false;
        
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* thisVal=this;
        for(char c : prefix)
        {
            if(thisVal->nextCharacter[c-'a']!=NULL)
                thisVal=thisVal->nextCharacter[c-'a'];
            else
                return false;
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
