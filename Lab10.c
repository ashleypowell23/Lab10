// Ashley Powell
// Lab 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode
{
    struct TrieNode*children[26];
	int count;
};
// Trie structure
struct Trie
{	
    struct TrieNode* root;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	  struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            current->children[index] = (struct TrieNode *)malloc(sizeof(struct TrieNode));
            current->children[index]->count = 0; // Initialize count to 0
            // Initialize links to children nodes to NULL
            for (int j = 0; j < 26; j++)
            {
                current->children[index]->children[j] = NULL;
            }
        }
        current = current->children[index];
    }
    current->count++;
}

// computes the number of occurances of the word
int numberOfOccurences(struct Trie *pTrie, char *word)
{
	struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            return 0; // Word does not exist in the trie
        }
        current = current->children[index];
    }
    return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	if (root) {
        for (int i = 0; i < 26; i++) {
            deallocateTrie(root->children[i]);
        }
        free(root);
    }
}

// Initializes a trie structure
struct Trie *createTrie()
{
	  struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (pTrie)
    {
        pTrie->root = (struct TrieNode *)malloc(sizeof(struct TrieNode));
        if (pTrie->root)
        {
            pTrie->root->count = 0; // Initialize count to 0
            // Initialize links to children nodes to NULL
            for (int i = 0; i < 26; i++)
            {
                pTrie->root->children[i] = NULL;
            }
        }
    }
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        exit(1);
    }

    int numWords = 0;
    char word[256];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = strdup(word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurences(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}