#define MAX_DEF 50
#define MAX_WORD 20

typedef struct NODO
{
  char *word;
  char *def;
  int red;
  struct NODO *parent;
  struct NODO *rchild;
  struct NODO *lchild;
} NODO;

/*
Input:
-nameFile: contains the name of the text file from which a first dictionary is created with no definitions, for example Text.txt
Output:
- the address to the data structure containing the ordered "dictionary".
Error handling: return in case of any type of NULL error. specify in the report
errors that may occur
*/
NODO *createFromFile(char *nameFile);

/*
Input:
-dictionary: the data structure in which you have stored the dictionary
The function must print the words of the dictionary one by one with next to one's own definition, if any,
EXACTLY like this:

"table": [Mobile consisting of a wooden or other material supported by four legs]
"cup": [(null)]
"tablecloth": [Piece of fabric or other material lying on the table to set the table]
*/
void printDictionary(NODO *dictionary);

/*
Input:
-dictionary: the data structure in which you have stored the dictionary
Output:
- the number of words saved in the dictionary
*/
int countWord(NODO *dictionary);

/*
Input:
-dictionary: the data structure in which you have stored the dictionary
-word: the word to be included in the dictionary, without the definition
Output:
-0 in case of absence of errors
-1 in case of errors
*/
int insertWord(NODO **dictionary, char *word);

/*
Input:
-dictionary: the data structure in which you have stored the dictionary
-word: the word to be deleted in the dictionary
Output:
-0 in case of absence of errors
-1 in case of errors
*/
int cancWord(NODO **dictionary, char *word);

/*
Input:
-dictionary: the data structure in which you have stored the dictionary
-index: index indicating the word iesima (according to the dictionary order)
Output:
- the word located in the dictionary at the i-th position in the order of saving
-NULL in case of errors or word not present
*/
char *getWordAt(NODO *dictionary, int index);

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
int insertDef(NODO *dictionary, char *word, char *def);

/*
Input:
-dictionary: la struttura dati in cui avete memorizzato il dizionario
-word: la parola per cui si deve cercare la definizione
Output:
-la definizione nel caso essa sia presente, altrimenti NULL
*/
char *searchDef(NODO *dictionary, char *word);

/*
Input:
-dictionary: the data structure in which you have stored the dictionary
-fileOutput: the name of the file in which you want to save the dictionary
Output:
- (-1) in case of errors
- 0 otherwise
*/
int saveDictionary(NODO *dictionary, char *fileOutput);

/*
Input:
-fileInput: the name of the file containing the dictionary [same format used in saving and printing]
Output:
- the dictionary read from the file
*/
NODO *importDictionary(char *fileInput);

/*
Input:
-dictionary: the data structure in which you have stored the dictionary
-word: the word for which you want to look for presence
-first, second, thirdRis: in these three variables it is necessary to memorize
the three most similar entries / close to the word to search.
Output:
-0 in case of absence of the term in the dictionary
-1 in case of presence of the term in the dictionary
- (-1) in case of errors
*/
int searchAdvance(NODO *dictionary, char *word, char **primoRis, char **secondoRis, char **terzoRis);

/*
Input:
-dictionary: the data structure in which you have stored the dictionary
-fileOutput: the name of the file in which the compression result is to be saved
Output:
-0 in case it happened
- (-1) in case of errors
*/
int compressHuffman(NODO *dictionary, char *fileOutput);

/*
Input:
-fileInput: the name of the file containing the compressed data
-dictionary: the data structure in which the dictionary is to be stored
Output:
-0 in case it happened
- (- 1) in case of errors
*/
int decompressHuffman(char *fileInput, NODO **dictionary);
