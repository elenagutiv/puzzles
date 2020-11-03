#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100000
#define MAX_LENGTH_NUMBER 10

typedef struct entry_t {
    char *key;
    unsigned int value; // The value will be the index
    struct entry_t *next;
} entry_t;

typedef struct {
  entry_t **entries;  
}ht_t;


/* Hash Utility Functions */

ht_t *ht_create(void){
    ht_t *hashTable = malloc(sizeof(ht_t) * 1);

    //allocate table entries
    hashTable->entries = malloc(sizeof(entry_t*)* TABLE_SIZE);

    //set each entry to NULL for initialization
    int i = 0;
    for(; i < TABLE_SIZE; i++){
        hashTable->entries[i] = NULL;
    }
    return hashTable;
}

unsigned int hash(const char* key){
    unsigned long int acc = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for(; i < key_len; i++){
        acc = acc * 37 + key[i];
    }
    acc = acc%TABLE_SIZE;

    return acc;
}
entry_t *ht_pair(const char *key, const unsigned int value){
    entry_t *new_entry = malloc(sizeof(entry_t)*1);

    new_entry->key = malloc(strlen(key)+1); // Observe that new_entry->key is malloced!!
    strcpy(new_entry->key, key);

    new_entry->value = value;

    new_entry->next = NULL;

    return new_entry;
}

void ht_set(ht_t *hashTable, const char *key, const unsigned int value){

    unsigned int bucket = hash(key);
    

    entry_t *entry = hashTable->entries[bucket];

    //if entry is NULL then the bucket is still empty, insert immediately
    if(entry == NULL){
        hashTable->entries[bucket] = ht_pair(key, value);
        return;
    }

    entry_t *prev;
    //A collision occurred, we will store in a bucket that is already busy.
    while(entry != NULL){
        if(strcmp(entry->key, key) == 0){ //we update the previous value
            entry->value = value;
            return;
        }
        prev = entry;
        entry = prev->next;
    }
    // End of chain reached without a match, add new element at the end
    prev->next = ht_pair(key,value);

    return;
}

int ht_get(ht_t *hashTable, const char* key, unsigned int *value){
    unsigned int bucket = hash(key);

    entry_t *entry = hashTable->entries[bucket];

    if(entry == NULL){// That key does not exist in the table
        return -1;
    }
    while(entry!=NULL){
        if(strcmp(entry->key, key) == 0){
            *value = entry->value;
            return 0;
        }
        entry = entry->next;
    }
    // End of chain reached without a match
    return -1;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* bruteForceTwoSum(int* nums, int numsSize, int target, int* returnSize){
    int *returnNums = (int*) malloc(sizeof(int)*2);
    int sum, i,j;
    *returnSize = 2;
    for(i = 0; i < numsSize-1; i++){
        for(j = i+1; j < numsSize; j++){
            sum = nums[i] + nums[j];
            if(sum == target){
                returnNums[0] = i;
                returnNums[1] = j;
                return returnNums;
            }
        }
    }
    printf("Not two sum solution");
    return NULL;
    
}

void ht_print(ht_t *hashTable){
    int i = 0;
    entry_t *entry;
    for(; i < TABLE_SIZE; i++){
        entry = hashTable->entries[i];
        if(entry != NULL){
            printf("[Bucket %d] -> ", i);

            while(entry!=NULL){
                printf("(Key: %s, Value: %d)\t", entry->key, entry->value);
                entry = entry->next;
            }
            printf("\n");
        }
    }
    return;
}

// int* twoPassHashTableTwoSum(int* nums, int numsSize, int target, int* returnSize){

// }

void printSolution(int* returnNums, int returnSize){
    printf("[");
    for (int i = 0; i < returnSize; i++){
        printf("%d\t", returnNums[i]);
    }
    printf("]\n");
}
int main(void) { 
   
  // keep this function call here
  int A[] = {2,7,11,15}, returnSize, returnNums;
  int target = 9;
  int arrLength = sizeof(A) / sizeof(*A);
  // returnNums = bruteForceTwoSum(A, arrLength, targey, returnSize);
  // if(returnNums != NULL){
  //   printSolution(returnNums, returnSize);
  // }
  // Note from the problem: you may assume that each input would have exactly one solution
  // That means that no two elements in the array are equal and thus, every key is different.
  ht_t *hashTable = ht_create();

  
  char key_i[MAX_LENGTH_NUMBER+2]; // counts the sign and '\0'
  int i = 0;
  for(; i < arrLength; i++){
    sprintf(key_i, "%d", A[i]);
    ht_set(hashTable, key_i, i);
  }
  
  ht_print(hashTable);
  
  return 0;
    
}

// Complexity Analysis - Brute Force Solution
// Time complexity : O(n^2). For each element, we try to find its complement by looping through the rest of array which takes O(n) time. Therefore, the time complexity is O(n2).
// Space complexity : O(1).