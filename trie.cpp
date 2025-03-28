#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Node
{
    private:
    Node* links[26];
    bool flag;

    public:
    Node()
    {
        for(int i=0; i<26; i++)
        links[i] = nullptr;

        flag = false;
    }

    // checks if a key has been assigned a reference pointer or not
    bool containsKey(char ch)
    {
        return (links[ch - 'a'] != nullptr);
    }

    // assigns a reference pointer to a new position
    void put(char ch, Node* node)
    {
        links[ch - 'a'] = node;
    }

    // returning the reference pointer associated with a character
    Node* get(char ch)
    {
        return links[ch - 'a'];
    }

    // setting the flag of end of a word
    void setEnd()
    {
        flag = true;
    }

    // getting the flag of a node
    bool getEnd()
    {
        return flag;
    }
};

class Trie 
{
    private:
    Node* root;

    public:
    Trie() 
    {
        root = new Node(); 
    }
        
    void insert(string word) 
    {
        Node* ptr = root;

        int l = word.length();
        for(int i=0; i<l; i++)
        {
            if(!ptr->containsKey(word[i]))
            ptr->put(word[i], new Node());

            ptr = ptr->get(word[i]);
        }

        // after inserting all chars, we are at empty trie node which is the end of the word.
        // so set flag = true
        ptr->setEnd();
    }
        
    bool search(string word) 
    {
        Node* ptr = root;
        int l = word.length();

        for(int i=0; i<l; i++)
        {
            if(!ptr->containsKey(word[i]))
            return false;

            ptr = ptr->get(word[i]);
        }

        // if flag = true after trie of last character, then word exists, else no.
        if(ptr->getEnd())
        return true;

        return false;
    }
        
    bool startsWith(string prefix) 
    {
        Node* ptr = root;
        int l = prefix.length();

        for(int i=0; i<l; i++)
        {
            if(!ptr->containsKey(prefix[i]))
            return false;

            ptr = ptr->get(prefix[i]);
        }

        // if nullptr has never been encountered, then prefix is valid, else no 
        return true;
    }
};

int main()
{
    Trie trie;

    trie.insert("apple");
    trie.insert("pineapple");
    trie.insert("Rishabh");

    cout << trie.startsWith("Rishbh") << endl;
}