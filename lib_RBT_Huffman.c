#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib_RBT_Huffman.h"


//FUNCTION STANDARD BST

//Function which returns the minimum of a BST
NODO* BSTminNode(NODO* root)
{
								if (root == NULL)
																return NULL;

								if (root->lchild == NULL)
																return root;
								return BSTminNode(root->lchild);
}

//Function that returns the successor of a given node in a BST
NODO* BSTsuccessor(NODO* node)
{
								if (node == NULL)
																return NULL;

								if (node->rchild != NULL)
																return BSTminNode(node->rchild);

								NODO* y = node->parent;
								while (y != NULL && node == y->rchild)
								{
																node = y;
																y = y->parent;
								}

								return y;
}

//Find the node that contains word or returns NULL
NODO* BSTfind(NODO* root, char* word)
{
								if (root == NULL || word == NULL)
																return NULL;

								int dir = strcmp(word, root->word);
								if (dir == 0)
																return root;
								else if (dir > 0)
																BSTfind(root->rchild, word);
								else
																BSTfind(root->lchild, word);
}


//ACCESSORY FUNCTIONS FOR RBT
//Function that creates a new node by initializing it
NODO* RBnodeCreate(char* word, char* def)
{
								int l = 0;
								NODO* node = (NODO*)malloc(sizeof(NODO));

								//if the allocation is successful
								if (node != NULL) {
																node->red = 0;
																node->lchild = NULL;
																node->rchild = NULL;
																node->parent = NULL;

																if (def == NULL)
																								node->def = NULL;
																else
																{
																								l = strlen(def);
																								node->def = (char*)malloc(sizeof(char*) * l);
																								strncpy(node->def, def, l + 1);
																}
																if (word == NULL)
																								node->word = NULL;
																else
																{
																								l = strlen(word);
																								node->word = (char*)malloc(sizeof(char*) * l);
																								strncpy(node->word, word, l + 1);
																}
								}
								return node;
}

//Function that verifies if a node is red (returning 1) or black (0)
int nodeIsRed(NODO* node)
{
								if (node != NULL && node->red)
																return 1;
								else
																return 0;
}

//MORE ELABORATE FUNCTIONS ON RBT

void rotateLeft(NODO** root, NODO* node)
{
								NODO *y = node->rchild;

								node->rchild = y->lchild;
								if (y->lchild != NULL)
																y->lchild->parent = node;

								if (y != NULL) y->parent = node->parent;
								if (node->parent)
								{
																if (node == node->parent->lchild)
																								node->parent->lchild = y;
																else
																								node->parent->rchild = y;
								}
								else
																*root = y;

								y->lchild = node;
								if (node != NULL)
																node->parent = y;
}

void rotateRight(NODO** root, NODO* node)
{
								NODO* y = node->lchild;

								node->lchild = y->rchild;
								if (y->rchild != NULL) y->rchild->parent = node;

								if (y != NULL) y->parent = node->parent;
								if (node->parent)
								{
																if (node == node->parent->rchild)
																								node->parent->rchild = y;
																else
																								node->parent->lchild = y;
								}
								else
																*root = y;

								y->rchild = node;
								if (node != NULL)
																node->parent = y;
}

//Performs the colors and rotations necessary to keep the RBTree
void insertFixup(NODO** root, NODO* x)
{
								if (*root == NULL)
																return;

								while (x != *root && nodeIsRed(x->parent))
								{
																if (x->parent == x->parent->parent->lchild)
																{
																								NODO* y = x->parent->parent->rchild;
																								if (y != NULL && nodeIsRed(y))
																								{
																																x->parent->red = 0;
																																y->red = 0;
																																x->parent->parent->red = 1;
																																x = x->parent->parent;
																								}
																								else
																								{
																																if (x == x->parent->rchild)
																																{
																																								x = x->parent;
																																								rotateLeft(&(*root), x);
																																}
																																x->parent->red = 0;
																																x->parent->parent->red = 1;
																																rotateRight(&(*root), x->parent->parent);
																								}
																}
																else
																{
																								NODO* y = x->parent->parent->lchild;
																								if (y != NULL && nodeIsRed(y))
																								{
																																x->parent->red = 0;
																																y->red = 0;
																																x->parent->parent->red = 1;
																																x = x->parent->parent;
																								}
																								else
																								{
																																if (x == x->parent->lchild)
																																{
																																								x = x->parent;
																																								rotateRight(&(*root), x);
																																}
																																x->parent->red = 0;
																																x->parent->parent->red = 1;
																																rotateLeft(&(*root), x->parent->parent);
																								}
																}
								}
								(*root)->red = 0;
}

/*
   Input: the root of the RBT and the node to be inserted
   Output: -1 if the node is null
   0 if the node is already present (so it will not be inserted again) or the insertion takes place correctly
 */
int RBinsertNode(NODO** root, NODO* newNode)
{
								if (newNode == NULL)
																return -1;

								if (*root == NULL)
								{
																*root = newNode;
																return 0;
								}

								NODO* parent, *current;

								parent = NULL;
								current = *root;
								//scroll until it finds the right parent for newNode
								while (current != NULL)
								{
																//value is present
																if (compareWords(newNode, current) == 0)
																								return 0;

																parent = current;
																//if newNode is bigger it moves to the right otherwise to the left
																if (compareWords(newNode, current) > 0)
																								current = current->rchild;
																else
																								current = current->lchild;
								}

								newNode->parent = parent;
								newNode->red = 1;

								//insert it to the right or left of the found parent
								if (parent != NULL)
								{
																if (compareWords(newNode, parent) > 0)
																								parent->rchild = newNode;
																else
																								parent->lchild = newNode;
								}
								else
								{
																*root = newNode;
																newNode->red = 0;
								}

								insertFixup(&(*root), newNode);
								return 0;
}

//Performs the colors and rotations necessary to keep the RBTree
void deleteFixup(NODO** root, NODO* x)
{
								if (*root == NULL)
																return;

								while (x != NULL && x != *root && nodeIsRed(x) == 0)
								{
																if (x == x->parent->lchild) {
																								NODO *w = x->parent->rchild;
																								if (w != NULL && nodeIsRed(w))
																								{
																																w->red = 0;
																																x->parent->red = 1;
																																rotateLeft(&(*root), x->parent);
																																w = x->parent->rchild;
																								}
																								if (w != NULL && nodeIsRed(w->lchild) == 0 && nodeIsRed(w->rchild) == 0)
																								{
																																w->red = 1;
																																x = x->parent;
																								}
																								else
																								{
																																if (w != NULL && nodeIsRed(w->rchild) == 0)
																																{
																																								w->lchild->red = 0;
																																								w->red = 1;
																																								rotateRight(&(*root), w);
																																								w = x->parent->rchild;
																																}
																																w->red = x->parent->red;
																																x->parent->red = 0;
																																w->rchild->red = 0;
																																rotateLeft(&(*root), x->parent);
																																x = *root;
																								}
																}
																else
																{
																								NODO *w = x->parent->lchild;
																								if (w != NULL && nodeIsRed(w) == 1) {
																																w->red = 0;
																																x->parent->red = 1;
																																rotateRight(&(*root), x->parent);
																																w = x->parent->lchild;
																								}
																								if (w != NULL && nodeIsRed(w->rchild) == 0 && nodeIsRed(w->lchild) == 0) {
																																w->red = 1;
																																x = x->parent;
																								}
																								else
																								{
																																if (w != NULL && nodeIsRed(w->lchild) == 0)
																																{
																																								w->rchild->red = 0;
																																								w->red = 1;
																																								rotateLeft(&(*root), w);
																																								w = x->parent->lchild;
																																}
																																w->red = x->parent->red;
																																x->parent->red = 0;
																																w->lchild->red = 0;
																																rotateRight(&(*root), x->parent);
																																x = *root;
																								}
																}
								}
								if (x != NULL)
																x->red = 0;
}

/*
   Input: the root of the RBT and the node to be deleted
   Output: -1 if the node is null
   0 if cancellation occurs correctly
 */
int deleteNode(NODO** dictionary, NODO* node) {
								NODO *x = NULL;
								NODO *y = NULL;

								//if the node is not present exits returning error
								if (node == NULL)
																return -1;

								//if node not have child
								if (node->lchild == NULL || node->rchild == NULL)
																y = node;
								//otherwise he finds his successor who has no children
								else
																y = BSTsuccessor(node);

								if (y->lchild != NULL)
																x = y->lchild;
								else
																x = y->rchild;

								//remove
								if (x != NULL)
																x->parent = y->parent;

								if (y->parent != NULL)
								{
																if (y == y->parent->lchild)
																								y->parent->lchild = x;
																else
																								y->parent->rchild = x;
								}
								else
																*dictionary = x;

								if (y != node)
								{
																node->word = y->word;
																node->def = y->def;
								}

								if (nodeIsRed(y) == 0)
																deleteFixup(&(*dictionary), x);

								return 0;
}

//FUNCTIONS TO MANAGE THE STRINGS
/*
   Input: two strings
   Output:
   < 0	node < root
   0	root = node
   > 0	node > root
 */
int compareWords(NODO* node, NODO* root)
{
								if (root == NULL || node == NULL)
								{
																printf("nodi nulli (dir)");
																return NULL;
								}
								int len1 = strlen(node->word), len2 = strlen(root->word);

								return strcmp(node->word, root->word);
}

/*
   Input: a dictionary node
   Output: 1 in case of absence of the node, 0 if the printing is successful
 */
int printNode(NODO* node)
{
								if (node == NULL)
																return 1;
								printf("\"%s\" : ", node->word);
								if (node->def == NULL)
																printf("[(null)]\n");
								else
																printf("[%s]\n", node->def);
								return 0;
}

/*
   Input: two strings
   Output: their distance (int) of Hamming
 */
int HammingDistance(char* str1, char *str2)
{
								int i = 0, j = 0, fine = 0, dist = 0;

								while ((i <= 20 && j <= 20) && (str1[i] != '\0' || str2[j] != '\0')) {
																if (str1[i] != str2[j]) {
																								dist++;
																}
																if (str1[i] != '\0') {
																								i++;
																}
																if (str2[j] != '\0') {
																								j++;
																}
								}
								return dist;
}

/*
   Input: two int. Pointers
   Output: the two pointers with the value exchanged
 */
void swap(int* a, int* b)
{
								int tmp = b;
								b = a;
								a = tmp;
}

/*
   Input: array of three int
   Output: The array ordered in descending order
 */
void decreasingSortThreeNumbers(int array[])
{
								if (array[0] < array[2])
																swap(array[0], array[2]);

								if (array[0] < array[1])
																swap(array[0], array[1]);

								if (array[1] < array[2])
																swap(array[1], array[2]);
}

/*
   Input:
   -nameFile: contains the name of the text file from which a first dictionary is created with no definitions, for example Text.txt
   Output:
   - the address to the data structure containing the ordered "dictionary".
   Error handling: return in case of any type of NULL error. specify in the report
   errors that may occur
 */
NODO* createFromFile(char* nameFile)
{
								char word[MAX_WORD];
								char ch;
								unsigned int i = 0;
								int returnValue = 0;

								NODO* root = NULL;

								//open the file and verify the correct opening
								FILE* fp = fopen(nameFile, "r");
								if (fp == NULL)
								{
																printf("\nFile non trovato");
																return NULL;
								}

								//until the file ends
								while ((ch = fgetc(fp)) != EOF)
								{
																//reads a word
																while (ch != EOF && i < MAX_WORD && isalpha(ch))
																{
																								word[i++] = tolower(ch);
																								fscanf(fp, "%c", &ch);
																}

																//if legal inserts it
																if (i >= 2 && i < MAX_WORD)
																{
																								word[i] = '\0';
																								returnValue = insertWord(&root, word);
																								//verify the correct insertion in the RBTree
																								if (returnValue == -1)
																								{
																																printf("\nError(s) during insertion\n");
																																return NULL;
																								}
																}
																i = 0;
																word[0] = '\0';
								}

								fclose(fp);
								return root;
}

/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   The function must print the words of the dictionary one by one with next to one's own definition, if any,
   EXACTLY like this:

   "table": [Mobile consisting of a wooden or other material supported by four legs]
   "cup": [(null)]
   "tablecloth": [Piece of fabric or other material lying on the table to set the table]
 */
void printDictionary(NODO*  dictionary)
{
								if (dictionary == NULL)
																return NULL;
								printDictionary(dictionary->lchild);
								printNode(dictionary);
								printDictionary(dictionary->rchild);
}

/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   Output:
   - the number of words saved in the dictionary
 */
int countWord(NODO* dictionary)
{
								// recursively recalling itself by adding 1 the result until it reaches nodes = NULL
								if (dictionary == NULL)
																return 0;
								return (1 + countWord(dictionary->lchild) + countWord(dictionary->rchild));
}

/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   -word: the word to be included in the dictionary, without the definition
   Output:
   -0 in case of absence of errors
   -1 in case of errors
 */
int insertWord(NODO** dictionary, char* word)
{
								//Check input
								if (strlen(word) < 2)
																return 0;

								//Being an RBTree, it uses the standard functions to insert a new node
								NODO* newNode = RBnodeCreate(word, NULL);
								if (newNode == NULL)
								{
																printf("\nAllocazione fallita\n");
																return -1;
								}
								return RBinsertNode(&(*dictionary), newNode);
}


/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   -word: the word to be deleted in the dictionary
   Output:
   -0 in case of absence of errors
   -1 in case of errors
 */
int cancWord(NODO** dictionary, char* word) {
								return deleteNode(&(*dictionary), BSTfind(*dictionary, word));
}


/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   -word: the word to be deleted in the dictionary
   Output:
   -0 in case of absence of errors
   -1 in case of errors
 */
char* getWordAt(NODO* dictionary, int index)
{
								NODO* startNode = BSTminNode(dictionary);
								while (index != 0)
								{
																startNode = BSTsuccessor(startNode);
																index--;
								}

								return startNode->word;
}


/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   -word: the word for which the definition is to be inserted
   -def: the definition to be included in the dictionary
   Output:
   -0 in case of absence of errors
   -1 in case of errors, for example if the word does not exist in the dictionary
   the function will not produce any effect
   in the event that a definition is already present, it must be totally overwritten
 */
int insertDef(NODO* dictionary, char* word, char* def)
{
								NODO* tmp = BSTfind(dictionary, word);
								if (tmp == NULL)
																return 1;

								tmp->def = def;
								return 0;
}


/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   -word: the word for which the definition is to be searched
   Output:
   - the definition if it is present, otherwise NULL
 */
char* searchDef(NODO* dictionary, char* word)
{
								//search for the node and print its definition
								NODO* tmp = BSTfind(dictionary, word);
								if (tmp == NULL)
																return NULL;
								return tmp->def;
}


/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   -fileOutput: the name of the file in which you want to save the dictionary
   Output:
   - (-1) in case of errors
   - 0 otherwise
 */
int saveDictionary(NODO* dictionary, char* fileOutput)
{
								//if the dictionary is empty, the function returns zero but exits immediately
								NODO* tmp = BSTminNode(dictionary);
								if (tmp == NULL)
																return 0;

								FILE* fp = fopen(fileOutput, "w");

								//if the file is not found, it returns an error and exits
								if (fp == NULL)
								{
																printf("\nFile non trovato");
																return -1;
								}

								//as long as he finds elements in the tree he keeps writing
								do
																fprintf(fp, "\"%s\" : [%s]\n", tmp->word, tmp->def);
								while ((tmp = BSTsuccessor(tmp)) != NULL);

								fclose(fp);
								return 0;
}


/*
   Input:
   -fileInput: the name of the file containing the dictionary [same format used in saving and printing]
   Output:
   - the dictionary read from the file
 */
NODO* importDictionary(char *fileInput)
{
								NODO* dictionary = NULL;
								NODO* tmp = NULL;

								FILE* fp = fopen(fileInput, "r");

								if (fp == NULL)
								{
																printf("\nFile non trovato");
																return NULL;
								}

								char word[MAX_WORD];
								char def[MAX_DEF];
								char ch;
								unsigned int i = 0;

								while ((ch = fgetc(fp)) != EOF)
								{
																//if the read char is alphanumeric reads, otherwise it jumps to the char after
																if (isalpha(ch))
																{
																								//copy all the characters that will be the word
																								i = 0;
																								while (ch != EOF && i < MAX_WORD && isalpha(ch))
																								{
																																word[i++] = ch;
																																fscanf(fp, "%c", &ch);
																								}

																								word[i] = '\0';

																								//salta spazi e punteggiatura fra la word e la sua def
																								while (ch != EOF && !isalpha(ch))
																																fscanf(fp, "%c", &ch);

																								//skip spaces and punctuation between the word and its def
																								i = 0;
																								while (ch != EOF && i < MAX_DEF && ch != ']')
																								{
																																def[i++] = ch;
																																fscanf(fp, "%c", &ch);
																								}

																								def[i] = '\0';

																								//insert the node in the dictionary
																								tmp = RBnodeCreate(word, def);
																								if (RBinsertNode(&dictionary, tmp) == -1)
																								{
																																printf("\nErrore/i durante l'inserimento\n");
																																return NULL;
																								}

																								word[0] = '\0';
																								def[0] = '\0';
																}
								}

								fclose(fp);
								return dictionary;
}

/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   -word: the word for which you want to look for presence
   -first, second, third: these three variables must be memorized
   the three most similar entries / close to the word to search.
   Output:
   -0 in case of absence of the term in the dictionary
   -1 in case of presence of the term in the dictionary
   - (-1) in case of other errors
 */
int searchAdvance(NODO* dictionary, char* word, char** primoRis, char** secondoRis, char** terzoRis)
{
								//if it does not find word it exits and returns 0
								if (BSTfind(dictionary, word) == NULL)
																return 0;

								NODO* tmp = BSTminNode(dictionary);
								*primoRis = NULL;
								*secondoRis = NULL;
								*terzoRis = NULL;

								//the array distances stores the distances between the first three nodes (if any) with respect to words
								int distances[3] = { 0 };
								int i = 0;

								/*
								   it follows the nodes in a lexicographical order and verifies that there are some who have Hamming distance
								   less than what it has possibly found (excluding word) and adds them to the result together with
								   relative distances (distances [])
								 */
								while (tmp != NULL)
								{
																if (strcmp(tmp->word, word) != 0)
																{
																								int tmpDistance = HammingDistance(word, tmp->word);

																								if (tmpDistance < distances[0] || *primoRis == NULL)
																								{
																																distances[0] = tmpDistance;
																																*primoRis = tmp->word;
																								}
																								else if (tmpDistance < distances[1] || *secondoRis == NULL)
																								{
																																distances[1] = tmpDistance;
																																*secondoRis = tmp->word;
																								}
																								else if (tmpDistance < distances[2] || *terzoRis == NULL)
																								{
																																distances[2] = tmpDistance;
																																*terzoRis = tmp->word;
																								}

																								decreasingSortThreeNumbers(distances);
																}

																tmp = BSTsuccessor(tmp);
								}
								return 1;
}


/* Huffman tree*/
typedef struct hufftree
{
								struct hufftree *left;
								struct hufftree *right;
								int letter;
								int freq;
} hufftree;

//Free the memory used by the various trees
void FreeTree(hufftree *tree)
{
								if (tree)
								{
																FreeTree(tree->left);
																FreeTree(tree->right);
																free(tree);
								}
}

//Concatenates the letters to create an encoding (treated as a string)
char *ConcatLetter(char *prefix, char letter)
{
								char *result = (char *)malloc(strlen(prefix) + 2);
								sprintf(result, "%s%c", prefix, letter);
								return result;
}

//This function is used in the quickSort as a comparison model for trees (to sort them according to frequencies)
int TreeCompare(const hufftree **a, const hufftree **b)
{
								if ((*a)->freq == (*b)->freq)
																return 0;
								else
								{
																if ((*a)->freq < (*b)->freq)
																								return 1;
																else
																								return -1;
								}
}

//Create a Huffman tree based on the frequency table
hufftree *BuildHuffTree(int frequencies[])
{
								int len = 0;
								int i;
								hufftree *coda[256];

								//Create a tree for each character and add it to the queue (treated a bit like disjointed sets)
								for (i = 0; i < 256; i++)
								{
																if (frequencies[i])
																{
																								hufftree *addc = (hufftree *)calloc(1, sizeof(hufftree));
																								addc->letter = i;
																								addc->freq = frequencies[i];

																								coda[len++] = addc;
																}
								}

								while (len > 1)
								{
																hufftree *addc = (hufftree *)malloc(sizeof(hufftree));

																//Sort the various frequencies
																qsort(coda, len, sizeof(hufftree *), TreeCompare);

																//Manages first those with low priority (lower frequency)
																addc->left = coda[--len];
																addc->right = coda[--len];
																addc->freq = addc->left->freq + addc->right->freq;

																//Add in the queue
																coda[len++] = addc;
								}

								//returns the first element of the queue
								return coda[0];
}

//Convert the tree into a table of frequencies and encodings
void CompleteTable(hufftree *tree, char **table, char *prefix)
{
								if (tree->left == NULL && tree->right == NULL)
																table[tree->letter] = prefix;
								else
								{
																if (tree->right)
																								CompleteTable(tree->right, table, ConcatLetter(prefix, '1'));
																if (tree->left)
																								CompleteTable(tree->left, table, ConcatLetter(prefix, '0'));

																free(prefix);
								}
}

//Create a frequency table that will be more convenient during encoding
char **BuildFrequenciesTable(int frequencies[])
{
								static char *table[256];
								char *prefix = (char *)calloc(1, sizeof(char));

								//builds the tree and completes the table
								hufftree *tree = BuildHuffTree(frequencies);
								CompleteTable(tree, table, prefix);
								FreeTree(tree);

								return table;
}

//Libera la memoria usata dalle tabelle
void FreeFrequenceTable(char *table[])
{
								int i;
								for (i = 0; i < 256; i++) {
																if (table[i])
																								free(table[i]);
								}
}

//Free the memory used by the tables
void WriteFileHeader(FILE *out, int frequencies[])
{
								int count = 0;
								int i;

								for (i = 0; i < 256; i++) {
																if (frequencies[i]) {
																								count++;
																}
								}

								fprintf(out, "%d\n", count);

								for (i = 0; i < 256; i++) {
																if (frequencies[i]) {
																								fprintf(out, "%d %d\n", i, frequencies[i]);
																}
								}
}

//I read the header of the encoded file to get the frequencies
int *ReadFileHeader(FILE *in)
{
								static int frequencies[256];
								int freq, i, letter, count;

								if (fscanf(in, "%d", &count) != 1)
																printf("\nFile non valido.");

								for (i = 0; i < count; i++)
								{
																if ((fscanf(in, "%d %d", &letter, &freq) != 2) || letter < 0 || letter >= 256)
																								printf("\nFile non valido.");

																frequencies[letter] = freq;
								}
								fgetc(in);

								return frequencies;
}

//Writes the bits used on the output file
void WriteFileBits(const char *encoding, FILE *out)
{
								static int bits = 0;
								static int count = 0;

								//Shift the various bits to make the compression
								while (*encoding)
								{
																//Shift the various bits to the right
																bits = bits * 2 + *encoding - '0';
																count++;

																//As soon as it fills the 8 bits of the character it prints it on the file
																if (count == 8)
																{
																								fputc(bits, out);
																								bits = 0;
																								count = 0;
																}
																encoding++;
								}
}

//Read the bits on the file
int ReadFileBit(FILE *in)
{
								int nextbit;
								static int count = 0;
								static int bits = 0;

								//memorizza i bit
								if (count == 0)
								{
																bits = fgetc(in);
																count = (1 << 7);
								}

								nextbit = bits / count;
								bits %= count;
								count /= 2;

								return nextbit;
}

//Interpret the various characters using the Huffman tree previously constructed
int DecodeCharacter(FILE *in, hufftree *tree)
{
								while (tree->left || tree->right)
								{
																if (ReadFileBit(in))
																								tree = tree->right;
																else
																								tree = tree->left;

																if (!tree)
																								printf("\nErrore lettura file.");
								}
								return tree->letter;
}

//Decrypt the file and write it in a totally clean one
void DecodeFile(FILE *in, FILE *out)
{
								int x, *frequencies;
								hufftree *tree;

								//count the letters in the file, calculate the frequencies and then the tree
								frequencies = ReadFileHeader(in);
								tree = BuildHuffTree(frequencies);

								//decode character by character until it reaches the end (EOF == F)
								while ((x = DecodeCharacter(in, tree)) != 70)
																fputc(x, out);

								FreeTree(tree);
}

//He coded the Huffman tree in the file
void EncodeFile(FILE *in, FILE *out)
{
								char **table;
								int x = 0;
								int frequencies[256] = { 0 };

								while ((x = fgetc(in)) != EOF) frequencies[x]++;

								frequencies[70] = 1;
								rewind(in);

								//builds a table to contain the encoding of each letter (in order not to scroll the tree continuously)
								table = BuildFrequenciesTable(frequencies);
								WriteFileHeader(out, frequencies);

								while ((x = fgetc(in)) != EOF)
																WriteFileBits(table[x], out);

								//writes the fake eof (F which in ASCII is 70) which indicates the end of the file
								WriteFileBits(table[70], out);

								//cleans the buffer
								WriteFileBits("0000000", out);
}

/*
   Input:
   -dictionary: the data structure in which you have stored the dictionary
   -fileOutput: the name of the file in which the compression result is to be saved
   Output:
   -0 in case it happened
   - (-1) in case of errors
 */
int compressHuffman(NODO* dictionary, char* fileOutput) {
								FILE *in, *out;

								saveDictionary(dictionary, "support.txt");

								in = fopen("support.txt", "a");
								if (in == NULL)
								{
																printf("\nErrors when opening or creating one or more files");
																return -1;
								}

								//adds the FAKE string that tells me the end of the file
								fprintf(in,"%s","FAKE");
								fclose(in);

								in = fopen("support.txt", "r+");
								out = fopen(fileOutput, "w+");

								if (in == NULL || out == NULL)
								{
																printf("\nErrors when opening or creating one or more files");
																return -1;
								}

								EncodeFile(in, out);

								fclose(in);
								fclose(out);

								//rm for linux change with "del" for windows
								system("rm support.txt");

								return 0;
}

/*
   Input:
   -fileInput: the name of the file containing the compressed data
   -dictionary: the data structure in which the dictionary is to be stored
   Output:
   -0 in case it happened
   - (-1) in case of errors
 */
int decompressHuffman(char *fileInput, NODO** dictionary)
{
								FILE *in, *out;

								in = fopen(fileInput, "r+");
								out = fopen("decompress.txt", "w+");

								if (in == NULL || out == NULL)
								{
																printf("\nErrors when opening or creating one or more files");
																return -1;
								}

								DecodeFile(in, out);

								fclose(in);
								fclose(out);

								if (*dictionary == NULL)
																RBnodeCreate(NULL, NULL);

								*dictionary = importDictionary("decompress.txt");

								system("rm decompress.txt");

								return 0;
}
