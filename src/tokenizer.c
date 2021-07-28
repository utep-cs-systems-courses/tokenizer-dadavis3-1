#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int main(){
  return 0;

}
  /*  char phrase[100];
  printf("Input a phrase you would like to tokenize: \n");
  while(1){

    printf("If you want to tokenize a phrase, enter the the new phrase\nIf you want to stop tokenizing, press q\n");
    fgets(phrase,100,stdin);

    if(phrase[0] == 'q'){
      printf("Freeing Tokens\nBye Bye!\n");
      free_tokens(tokenize(phrase));
      exit(0);
    }else{
      print_tokens(tokenize(phrase));
      printf("Freeing tokens...\n");
      free_tokens(tokenize(phrase));
    }
  }
  return 0;
  }*/
  
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
