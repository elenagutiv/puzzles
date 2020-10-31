#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define SIZE_ALPH 26

/* This function is not used. I leave it here for future use*/
int remove_duplicate_elements(char input[], char output[], int n){

  if (n==0 || n==1){
    return n;
  }
  char temp[n];
  int j = 0, i;
  for (i = 0; i < n-1; i++){
    if (input[i] != input[i+1]){
      temp[j++] = input[i];
    }
  }
  temp[j++] = input[n-1];

  for (i = 0; i < j; i++){
    output[i] = temp[i];
  }
  return j;
}

int fMap(char ch){
  return ((int)ch)-97;
}
void parikhVector(int* parikhV, char* string){
  int lengthString = strlen(string);
  memset(parikhV, 0, SIZE_ALPH * sizeof(*parikhV));
  int i;

  for(int j = 0; j < lengthString; j++){
    i = fMap(string[j]);
    parikhV[i]++;
  }
}

int validWindow(int* v1, int* v2){
  for(int i = 0; i < SIZE_ALPH; i++){
    if(v1[i] < v2[i]){
      return 0;
    }
  }
  return 1;
}

int isBetterWindowThan(int* parikhWindow, int lengthWindow, int* bestParikhWindow, int bestLengthWindow){
  for(int i = 0; i < SIZE_ALPH; i++){
    if(parikhWindow[i] > bestParikhWindow[i]){
      return 0;
    }
  }
  if(lengthWindow > bestLengthWindow){
      return 0;
  }
  return 1;
}

int isTheBestWindow(int* bestParikhWindow, int lengthWindow, int* parikhK, int lengthk){
  if(lengthWindow == lengthk){
    for(int i = 0; i < SIZE_ALPH; i++){
      if(bestParikhWindow[i] != parikhK[i]){
        return 0;
      } 
    }
    return 1;
  }
  return 0;

}
void widenWindow(int* parikhWindow, int* lengthWindow, int* rp, char* strArr){
  (*lengthWindow)++;
  (*rp)++;

  int i = fMap(strArr[*rp]);
  parikhWindow[i]++;

}
void narrowWindow(int* parikhWindow, int* lengthWindow, int* lp, char* strArr){
  (*lengthWindow)--;

  int i = fMap(strArr[*lp]);
  parikhWindow[i]--;

  (*lp)++;
}

void MinWindowSubstring(char * strArr[], int arrLength) {

  int lengthN = strlen(strArr[0]);
  int lengthk = strlen(strArr[1]);

  int parikhWindow[SIZE_ALPH], parikhK[SIZE_ALPH], bestParikhWindow[SIZE_ALPH];
  parikhVector(parikhK, strArr[1]);
  memset(parikhWindow, 0, SIZE_ALPH * sizeof(*parikhWindow));

  int lp = 0, rp = -1; //left and right pointers
  int lengthWindow = 0, bestLengthWindow;
  widenWindow(parikhWindow, &lengthWindow, &rp, strArr[0]);
  int firstValidFlag = 1;
  char best_subbuff[lengthN];
  
  while(1){ // The algorithm increases monotonically lp and rp (at each iteration, one at a time) and their values are bounded by lengthN.
            // So, at some point in time either lp == rp or rp == lengthN-1, and thus the loop terminates.

    if(!validWindow(parikhWindow, parikhK) && rp < (lengthN - 1)){

      widenWindow(parikhWindow, &lengthWindow, &rp, strArr[0]);
      
    }else if ((validWindow(parikhWindow, parikhK) && (lp <= rp)) || (validWindow(parikhWindow, parikhK) && (lp == rp))){

      if( firstValidFlag || isBetterWindowThan(parikhWindow, lengthWindow, bestParikhWindow, bestLengthWindow)){
        memcpy(&bestParikhWindow, &parikhWindow, sizeof(bestParikhWindow));
        bestLengthWindow = lengthWindow;
        memcpy(best_subbuff, &strArr[0][lp], rp-lp+1);
        best_subbuff[rp-lp+1] = '\0';
        
        if(isTheBestWindow(bestParikhWindow, lengthWindow, parikhK, lengthk)){
          
          printf("The smallest BEST substring of %s that contains all the characters in %s is: %s\n", strArr[0], strArr[1], best_subbuff);
          return;
        }
        firstValidFlag = 0;
      }
      narrowWindow(parikhWindow, &lengthWindow, &lp, strArr[0]);
      

    }else{
      
      printf("The smallest substring of %s that contains all the characters in %s is: %s\n", strArr[0], strArr[1], best_subbuff);
      return;
    
    }
  }
}


int main(void) { 
   
  // keep this function call here
  char * A[] = {"aaabb", "bb"};
  int arrLength = sizeof(A) / sizeof(*A);
  MinWindowSubstring(A, arrLength);
  return 0;
    
}