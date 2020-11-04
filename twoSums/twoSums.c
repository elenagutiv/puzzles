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
static void ll_free(entry_t * ll){
    if(ll == NULL){
        return;
    }else{
        ll_free(ll->next);
        free(ll->key);
        free(ll);
        return;
    }
}

void ht_free(ht_t *hashTable){
    int i = 0;
    for(; i < TABLE_SIZE; i++){
        entry_t *entry = hashTable->entries[i];
        if(entry == NULL){
            continue;
        }else{
            ll_free(entry);
        }
    }
    free(hashTable->entries);
    free(hashTable);
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* bruteForceTwoSum(int* nums, int numsSize, int target, int* returnSize){
    int *returnNums = malloc(sizeof(int)*2);
    if(returnNums == NULL){
        printf("Error in malloc @ bruteForceTwoSum.\n");
        return NULL;
    }
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

// Note: This solution to the problem must assume that the array of integers nums *does not contain duplicates*
// Otherwise, since we are initializing the hashTable in the first pass, the second duplicate will overwrite the
// first one, which will produce unexpected behaviour.

// The one-pass-hash solution avoids this case as every element is introduced in the hash table only when
// we check that it is not the second index of a solution.
// Note that, because the solution is unique, two duplicates are either both part of the solution or any of the elements belongs to the solution
// Thus, if we encounter the second duplicate, we check whether both duplicates are a solution.
// If it is the case, we return the solution.
// If not, we can store it safely in the hash table, rewritting the previous value, as it will not be part of the solution

int *twoPassHashTableTwoSum(ht_t *hashTable, int *nums, int numsSize, int target, int *returnSize){
    int *returnNums = malloc(sizeof(int)*2);
    if(returnNums == NULL){
        printf("Error in malloc @ twoPassHashTableTwoSum.\n");
        return NULL;
    }
    *returnSize = 2;
    int i = 0;
    char key_char[MAX_LENGTH_NUMBER+2]; // counts the sign and '\0'
    char complement_char[MAX_LENGTH_NUMBER+2]; 

    int complement;
    int unsigned value;
    for(; i < numsSize; i++){
        sprintf(key_char, "%d", nums[i]);
        ht_set(hashTable, key_char, i);
    }
    // ht_print(hashTable);
    for(i = 0; i < numsSize; i++){
        complement = target - nums[i];
        sprintf(complement_char, "%d", complement);
        if(ht_get(hashTable, complement_char, &value) == -1){ // complement is not an element in numsSize
            continue;
        }else{
            returnNums[0] = i;
            returnNums[1] = value;
            return returnNums;
        }
    }
    printf("Not two sum solution");
    return NULL;
}

int *onePassHashTableTwoSum(ht_t *hashTable, int *nums, int numsSize, int target, int *returnSize){
    int *returnNums = malloc(sizeof(int)*2);
    if(returnNums == NULL){
        printf("Error in malloc @ twoPassHashTableTwoSum.\n");
        return NULL;
    }
    *returnSize = 2;
    int i = 0;
    char key_char[MAX_LENGTH_NUMBER+2]; // counts the sign and '\0'
    char complement_char[MAX_LENGTH_NUMBER+2];

    int complement;
    int unsigned value;

    for(; i < numsSize; i++){
        
        complement = target - nums[i];
        sprintf(complement_char, "%d", complement);
        if(ht_get(hashTable, complement_char, &value) == -1){ // complement is not an element in numsSize currently
            sprintf(key_char, "%d", nums[i]);
            ht_set(hashTable, key_char, i);
            continue;
        }else{
            returnNums[0] = i;
            returnNums[1] = value;
            return returnNums;
        }

    }
    printf("Not two sum solution");
    return NULL;
}

void printSolution(int* returnNums, int returnSize){
    printf("[");
    for (int i = 0; i < returnSize; i++){
        if(i == returnSize-1){
            printf("%d", returnNums[i]);
        }else{
            printf("%d\t", returnNums[i]);
        }
    }
    printf("]\n");
}
int main(void) { 
   
  // keep this function call here
  int A[] = {3, 3, 2, 8}, returnSize;
  int *returnNums;
  int target = 10;
  int arrLength = sizeof(A) / sizeof(*A);

  // Solution 1:

  // returnNums = bruteForceTwoSum(A, arrLength, target, &returnSize);
  // if(returnNums != NULL){
  //   printSolution(returnNums, returnSize);
  // }
  // free(returnNums);

  // Note from the problem: you may assume that each input would have exactly one solution
  // That means that no two elements in the array are equal and thus, every key is different.
  ht_t *hashTable = ht_create();

  // Solution 2:

  // returnNums = twoPassHashTableTwoSum(hashTable, A, arrLength, target, &returnSize);
  // if(returnNums != NULL){
  //   printSolution(returnNums, returnSize);
  // }
  // free(returnNums);

  // Solution 3:

  returnNums = onePassHashTableTwoSum(hashTable, A, arrLength, target, &returnSize);
  if(returnNums != NULL){
    printSolution(returnNums, returnSize);
  }
  free(returnNums);
  ht_free(hashTable);

  
  return 0;
    
}

// Complexity Analysis - Brute Force Solution
// Time complexity : O(n^2). For each element, we try to find its complement by looping through the rest of array which takes O(n) time. Therefore, the time complexity is O(n2).
// Space complexity : O(1).