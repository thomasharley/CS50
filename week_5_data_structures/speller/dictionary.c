// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;


// Hash table: Choose number of buckets in hash table
node *table[65536]; /* enough buckets to represent 3 letter combinations*/

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    /* convert the word to lower case */
    char lowerCase[LENGTH + 1];
    int i = 0;
    while( word[i] != '\0') {
        lowerCase[i] = tolower(word[i]);
        i++;
    }
    lowerCase[i] = '\0';

    int hashCode = hash(lowerCase);
    node *current = table[hashCode];
    while(current != NULL) {
        if(strcmp(current->word, lowerCase) == 0) {
            return true;
        }
        current = current -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /// TODO: Improve this hash function
    unsigned int code = 0;
    int i = 0;
    while(word[i] != '\0'){
        code = (code << 2) ^ word[i];
        i++;
    }
    return code % 65536;
    //return ((toupper(word[0]) - 'A') * 10000) + ((toupper(word[1]) - 'A') * 100) + ((toupper(word[2]) - 'A') * 1);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *loaded_dict = fopen(dictionary, "r");
    if(loaded_dict == NULL) {
        return false;
    } 

    char word[LENGTH+1];
    while(fscanf(loaded_dict, "%s", word) != EOF) {

        node *new = malloc(sizeof(node));
        if(new == NULL) {
            fclose(loaded_dict);
            return false;
        }

        strcpy(new->word, word);
        new->next = table[hash(word)];
        table[hash(word)] = new;
    }

    fclose(loaded_dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    
    int count = 0;
    for(int i = 0; i < 65536; i++){
        node *current = table[i];
        while(current != NULL){
            count++;
            current = current->next;
        }
    }
    return count;
    
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < 65536; i++) {
        node *current = table[i];
        while(current != NULL) {
            node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    return true;
}
