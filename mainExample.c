#include <stdio.h>
#include <stdlib.h>
#include "lib_RBT_Huffman.h"
#include <time.h>

char* randomWord(int dim);
char* randomString(int dim);

int main(void) {
								char* stringTemp;
								srand(time(NULL));

								NODO* dictionary = createFromFile("fileTest.txt");

								printf("\nPRINT THE DICTIONARY:\n");
								printDictionary(dictionary);

								printf("\nNumber of words saved in the dictionary: %d\n\n", countWord(dictionary));

								insertWord(&dictionary, "desk");
								insertWord(&dictionary, "b");
								insertWord(&dictionary, "zoo");

								printf("\nDICTIONARY PRINTING after 3 insertions:\n");
								printDictionary(dictionary);

								printf("\nNumber of words saved in the dictionary: %d\n\n", countWord(dictionary));

								cancWord(&dictionary, getWordAt(dictionary, 5));
								cancWord(&dictionary, getWordAt(dictionary, 1));
								cancWord(&dictionary, getWordAt(dictionary, 0));

								printf("\nDICTIONARY PRINTING after 3 cancellations:\n");
								printDictionary(dictionary);

								insertDef(dictionary, getWordAt(dictionary, 2), "definition one");
								insertDef(dictionary, getWordAt(dictionary, 4), "definition two");
								printf("\nDICTIONARY PRINTING after inserting definitions:\n");
								printDictionary(dictionary);
								printf("\nNumber of words saved in the dictionary: %d\n\n", countWord(dictionary));


								printf("\nWord Search \"%s\" -> definition: [%s]\n\n", getWordAt(dictionary, 2), searchDef(dictionary, getWordAt(dictionary, 2)));
								printf("\nWord Search \"%s\" -> definition: [%s]\n\n", getWordAt(dictionary, 7), searchDef(dictionary, getWordAt(dictionary, 7)));
								stringTemp = "eftd";
								printf("\nWord Search \"%s\" -> definition: [%s]\n\n", stringTemp, searchDef(dictionary, stringTemp));

								compressHuffman(dictionary, "compressed.txt");
								decompressHuffman("compressed.txt", &dictionary);
								printf("\nPRINT THE DICTIONARY:\n");
								printDictionary(dictionary);
								return (0);
}



char* randomWord(int dim) {
								int i;

								char* string = (char*)malloc((1 + dim) * sizeof(char));
								if (string == NULL) return "random";

								for (i = 0; i < dim; i++) {
																string[i] = rand() % 25 + 97;
								}
								string[i] = '\0';
								printf("\t\t-----> randomWord = %s \n", string);
								return string;
}

char* randomString(int dim) {
								int r, i;

								char* string = (char*)malloc((1 + dim) * sizeof(char));
								if (string == NULL) return "random string";

								for (i = 0; i < dim; i++) {

																r = rand() % 40 + 97;
																if (r >122) r = ' ';
																string[i] = r;
								}
								string[i] = '\0';
								printf("\t\t-----> randomString = %s \n", string);
								return string;
}
