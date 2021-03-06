# NOTA SULLE OPZIONI DI COMPILAZIONE
# l'opzione -ansi equivale all'opzione -std=c90.
# L'opzione -ansi definisce la compilazione secondo lo standard C90
# e l'aggiunta dell'opzione -Wpedantic avvisa in caso
# di istruzioni che, secondo lo standard C90,
# rendono il codice meno leggibile,
# ad esempio se mischio dichiarazioni e codice eseguibile
#     "ISO C90 forbids mixed declarations and code".
# Avrei potuto anche usare analogamente -std=c90 -Wpedantic
# Infine l'opzione -Wall chiede al compilatore
# di notificare con dei warning la presenza di
# istruzioni potenzialmente "pericolose"
# come ad esempio la presenza di chiamate a fuunzioni
# che non sono state dichiarate
#     "warning: implicit declaration of function"
#
# Inserisco la define -D_BSD_SOURCE per abilitare l' uso
# di alcune funzioni quali random e srandom.
# Queste funzioni NON sono fornite dalle librerie standard del C90
# Queste funzioni sono state implementate
# inizialmente nello standard  _BSD_SOURCE
# e successivamente incluse nello standard gnu99.
# Pero', invece di usare l'opzione -std=gnu99
# preferisco usare la define -D_BSD_SOURCE
# perche' se compilassi con le estensioni del C gnu99
# accetterei anche quelle estensioni del C gnu99
# che non mi piacciono,
# ad esempio le dichiarazioni di variabili in mezzo al codice.
# Infatti, se usassi -std=gnu99 l'opzione -Wpedantic
# non avrebbe piu' effetto e non mi impedirebbe piu'
# di mischiare dichiarazioni e codice.

all:	mainExample.exe

mainExample.exe:	mainExample.o lib_RBT_Huffman.o
		gcc -o mainExample.exe  mainExample.o lib_RBT_Huffman.o

mainExample.o:	mainExample.c lib_RBT_Huffman.h
		gcc -c mainExample.c

lib_RBT_Huffman.o:	lib_RBT_Huffman.c
		gcc -c lib_RBT_Huffman.c

.PHONY:	clean

clean:
		rm -f mainExample.exe mainExample.o lib_RBT_Huffman.o
