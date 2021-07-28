#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c);
int non_space_char(char c);
char *word_start(char *str);
char *word_terminator(char *word);
int count_words(char *s);
char *copy_str(char *inStr, short len);
void free_tokens(char** tokens);
void print_tokens(char** tokens);
char **tokenize(char *s);

int main(){
    char c1 = '\t';
    char c2 = ' ';
    char c3 = 'N';

    char word1[] = "        Hello world 2021"; 
    char word2[] = "Nice to meet you";

    printf("Test space_char [110]: ") ;
    printf("%d", space_char(c1));
    printf("%d", space_char(c2));
    printf("%d", space_char(c3));

    printf("\nTest non_space_char [001]: ") ;
    printf("%d", non_space_char(c1));
    printf("%d", non_space_char(c2));
    printf("%d", non_space_char(c3));

    printf("\n%s", word2);
    printf("%s", "\nTest word_start: ");
    printf("%s", word_start(word2));

    printf("%s", "\nTest word_start: ");
    printf("%s", word_terminator(word2));    

    printf("%s", "\n\nTest count words: ");
    printf("%d", count_words(word2));    

    printf("\nPrinting tokens: ");
    print_tokens(tokenize(word2));

    printf("\nFreeing tokens: \n");
    free_tokens(tokenize(word2));      
}

int space_char(char c){
    if(c == ' ' || c == '\t'){      // return 1 if there is a space 
        return 1;          
    }
    return 0;
}

int non_space_char(char c){
    if(c == ' ' || c == '\t'){  // return 0 if there is a space
        return 0;
    }
    return 1;
}

char *word_start(char *str){

    int i = 0;
    while(str[i] != '\0'){
        if(space_char(str[i]) == 1){
            i++;
        }
        if(non_space_char(str[i]) == 1 && str[i] != '\0'){
            return &str[i];
        }
    }
    return &str[i];
}

char *word_terminator(char *word){

    int i = 0;
    while(word[i] != '\0'){
        if(space_char(word[i]) == 0){
            i++;
        }
        if(non_space_char(word[i]) == 0){
            return &word[i];
        }
    }
    return &word[i];
}

int count_words(char *str){
    int i = 0;
    int count = 0;
    int exit = 0;   //function use this variable to exit out of each word once str is == '\0'

    while(*str){
        if(space_char(str[i]) == 1){  // if s == ' ' or '\t'
            exit = 0;    
        }
        else if(exit == 0){
            exit = 1;    //if exit is 0 then add 1 because a word was found
            ++count;
        }
        ++str;
    }
    return count; 
}

char *copy_str(char *inStr, short len){
    int size = len;
    size = (word_terminator(inStr) - word_start(inStr)); // lenght of word being pointed 
    char* token = (char*) malloc((size+1) * sizeof(char));  // allocates memory of char* with the length of the string 
    char* start = word_start(inStr);                    // variable that points to the first char of pointed word
    
    for(int i = 0; i < size; i++){
        *token = *start;
        token++;  //it points to next location in memory
        start++;
    }
    *token = '\0';   //null variable to end string
    return token -= size; 
}


void free_tokens(char** tokens){
  while(**tokens != '\0'){
    free(*tokens);      // free tokens until **tokens is not a '\0'
    tokens++;
  }

}


void print_tokens(char** tokens){
    int i = 0;
    while(**tokens != '\0'){
        printf("tokens[%d]: %s\n", i, *tokens);    //print each token 
        tokens++;
        
        i++;
    }
}

char** tokenize(char* str){

    int tokensNum = count_words(str);
    char end = '\0';   // this is the end of the line
    char** tokens = (char**) malloc((tokensNum + 1) * sizeof(char*)); // allocate memory in the size of tokensNum
    tokens[tokensNum] = &end;
    char* start = word_start(str);

    for(int i = 0; i < tokensNum; i++){
        tokens[i] = copy_str(start, sizeof(str));  //in each iteration copies the string and send it to tokens 
        start = word_terminator(start);
        start = word_start(start);
    }
    return tokens; // return trhe token of the string

}
