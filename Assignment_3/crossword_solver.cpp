// Program which suggests word w.r.t to given input.
// time complexity without map is O(h) where h is the height of the tree
// Tue, Jan 11 2022

#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

struct bintree_node
{
    struct bintree_node *left;
    std::string word;
    int length; // store length of the word
    struct bintree_node *right;
};

// map for each alphabet
std::unordered_map<std::string, struct bintree_node *> alphaMap;

// map for known index of string
std::unordered_map<int, std::string> indexMap;

// create a new node with given word and return the address of the new node
struct bintree_node *getnode(std::string word)
{
    struct bintree_node *temp = new bintree_node;

    temp->word = word;
    temp->length = word.length(); // length is cached, so the complexity is O(1)
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

class Bst
{
private:
    // member to store root node's address
    struct bintree_node *root;

    // member functions
public:
    Bst()
    {
        this->root = NULL;
    }
    int isEmpty()
    {
        return (root == NULL);
    }
    struct bintree_node *insert(std::string word);
    void search_words(char start_letter, int word_length, std::unordered_map<int, std::string> indexMap);
    void inorder_search(bintree_node *ptr, char start_letter, int word_length, std::unordered_map<int, std::string> indexMap);
    void inorder_display();
    void inorder(bintree_node *ptr);
};

// if the current data is less than current node then traverse left and vice versa and then store at the leaf position
struct bintree_node *Bst::insert(std::string word)
{
    struct bintree_node *temp = getnode(word);
    struct bintree_node *ptr = NULL;
    struct bintree_node *parent = NULL;

    // if root is empty then assign the new node to root
    if (isEmpty())
    {
        this->root = temp;
        return this->root;
    }
    // traverse to the appropriate position
    ptr = root;
    while (ptr != NULL)
    {
        // to store the parent node of the current node
        parent = ptr;
        if (word.compare(ptr->word) > 0)
            ptr = ptr->right;
        else if (word.compare(ptr->word) < 0)
            ptr = ptr->left;
        else
        {
            std::cout << "\n[+] Equal keys are not allowed in BST" << std::endl;
            return NULL;
        }
    }
    // got the location of the node now  check to insert it at left or right
    if (word.compare(parent->word) > 0)
    {
        parent->right = temp;
        return parent->right;
    }
    else
    {
        parent->left = temp;
        return parent->left;
    }
}

void Bst::inorder_search(struct bintree_node *ptr, char start_letter, int word_length, std::unordered_map<int, std::string> indexMap)
{
    // std::cout << "zz" << std::endl;
    if (ptr == NULL)
        return;
    // iterator for the map
    std::unordered_map<int, std::string>::iterator itr;
    bool display = true;

    inorder_search(ptr->left, start_letter, word_length, indexMap);
    if (start_letter == ptr->word[0] && word_length == ptr->length)
    {
        // check for given indices
        for (itr = indexMap.begin(); itr != indexMap.end(); ++itr)
            if (std::string(1, ptr->word[itr->first]) != itr->second)
                display = false;
        if (display == true)
            std::cout << ptr->word << " ";
    }
    inorder_search(ptr->right, start_letter, word_length, indexMap);
}

// displays words starting with the given argument
// void Bst::search_words(char start_letter, int word_length)
// {
//     struct bintree_node *ptr = root;
//     std::cout << "Searching..." << std::endl;

//     if (std::string(1, start_letter).compare(ptr->word) < 0)
//         inorder_search(ptr->left, start_letter, word_length);
//     else
//         inorder_search(ptr->right, start_letter, word_length);
// }

void Bst::search_words(char start_letter, int word_length, std::unordered_map<int, std::string> indexMap)
{
    struct bintree_node *ptr = alphaMap[std::string(1, start_letter)];
    std::cout << "[+] Searching..." << std::endl;

    inorder_search(ptr, start_letter, word_length, indexMap);
}

void Bst::inorder_display()
{
    std::cout << "\n---------------------------------------" << std::endl;
    inorder(root);
    std::cout << "\n---------------------------------------" << std::endl;
}

void Bst::inorder(struct bintree_node *ptr)
{
    if (ptr != NULL)
    {
        inorder(ptr->left);
        std::cout << ptr->word << " ";
        inorder(ptr->right);
    }
}

int main()
{
    Bst tree;
    struct bintree_node *temp = NULL;
    std::string word;

    // read dict from file and store in tree
    std::ifstream file("dict.txt");
    if (file)
    {
        for (int i = 0; i < 3700; i++)
        {
            file >> word;
            temp = tree.insert(word);
            // insert into hashmap
            if (alphaMap.count(std::string(1, word[0])) == 0)
                alphaMap.insert(std::pair<std::string, struct bintree_node *>(std::string(1, word[0]), temp));
        }
    }
    else
    {
        std::cerr << "[+] Could not open file dict.txt" << std::endl;
        exit(0);
    }
    file.close();
    std::cout << "[+] Loaded dictionary" << std::endl;

    // tree.inorder_display();

    char start_letter;
    int word_length;
    int letter_count;
    int index;
    std::string letter;

    std::cout << "\n[+] Enter the start_letter of the word: ";
    std::cin >> start_letter;
    std::cout << "\n[+] Enter the length of the string: ";
    std::cin >> word_length;
    std::cout << "\n[+] Enter the count of letter you know: ";
    std::cin >> letter_count;
    for (int i = 0; i < letter_count; i++)
    {
        std::cout << "\n[+] Enter the index of the known letter: ";
        std::cin >> index;
        if (index < word_length && index > word_length)
        {
            std::cout << "\n[+] Invalid index!" << std::endl;
            exit(0);
        }
        std::cout << "\n[+] Enter the known letter: ";
        std::cin >> letter;
        indexMap.insert(std::pair<int, std::string>(index, letter));
    }

    tree.search_words(start_letter, word_length, indexMap);
    std::cout << std::endl;
}