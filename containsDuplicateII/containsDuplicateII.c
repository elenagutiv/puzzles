#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

//For further infor about hash tables: https://medium.com/@jonathansychan/handling-collisions-in-a-hash-table-68a0fac508a

#define TABLE_SIZE 100000
#define MAX_LENGTH_NUMBER 18 // -[11 digits]-[5 digits] = 18 digits

// Constraints
// 0 <= nums.length <= 2 * 10^4
// -2^31 <= nums[i] <= 2^31 - 1
// 0 <= k <= 10^4
// 0 <= t <= 2^31 - 1

typedef struct entry_t {
    char *key;
    unsigned int value; // The value will be the index
    struct entry_t *next;
} entry_t;

typedef struct {
  entry_t **entries; 
  int num_entries; 
}ht_t;



/* Hash Utility Functions */

ht_t *ht_create(int sizeTable){
    ht_t *hashTable = malloc(sizeof(ht_t) * 1);

    //allocate table entries
    hashTable->entries = malloc(sizeof(entry_t*)* sizeTable);

    //set each entry to NULL for initialization
    int i = 0;
    for(; i < sizeTable; i++){
        hashTable->entries[i] = NULL;
    }
    hashTable->num_entries = 0;
    return hashTable;
}
// Java hashcode: https://stackoverflow.com/questions/40303333/how-to-replicate-java-hashcode-in-c-language
// This is called "desarrollo en base mixta"
// Another alternative: Interpret your key as a number and perform modulo of a prime p. Then the size of your table must be p
// Yet another alternative (expensive): use SHA. SHA takes as input an array of 0-1's and returns another one
// of 32 bytes. The probability that two different arrays yield the same SHA is very low
// Miguel's suggestion: Use 4 bytes of SHA to identify the bucket and use the remaining 28 bytes as an identifier
// of the key

unsigned int hash(const char* key, int sizeTable){
    unsigned long int acc = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for(; i < key_len; i++){
        acc = acc * 37 + key[i]; //31? 31 is the value used in the source code of OpenJDK
    }
    acc = acc%sizeTable;

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
// Another alternative to solve collisions to chaining: rehashing, linear probing or quadratic probing 
int ht_set(ht_t *hashTable, const char *key, const unsigned int value, int sizeTable){

    if(hashTable->num_entries == sizeTable){
        return 0;
    }

    unsigned int bucket = hash(key, sizeTable);
    

    entry_t *entry = hashTable->entries[bucket];

    //if entry is NULL then the bucket is still empty, insert immediately
    if(entry == NULL){
        hashTable->entries[bucket] = ht_pair(key, value);
        hashTable->num_entries++;
        return 1;
    }

    entry_t *prev;
    //A collision occurred, we will store in a bucket that is already busy.
    while(entry != NULL){
        if(strcmp(entry->key, key) == 0){ //we update the previous value
            entry->value = value;
            return 1;
        }
        prev = entry;
        entry = prev->next;
    }
    // End of chain reached without a match, add new element at the end
    prev->next = ht_pair(key,value);
    hashTable->num_entries++;

    return 1;
}

int ht_get(ht_t *hashTable, const char* key, unsigned int *value, int sizeTable){
    unsigned int bucket = hash(key, sizeTable);

    entry_t *entry = hashTable->entries[bucket];

    if(entry == NULL){// That key does not exist in the table
        return 0;
    }
    while(entry!=NULL){
        if(strcmp(entry->key, key) == 0){
            *value = entry->value;
            return 1;
        }
        entry = entry->next;
    }
    // End of chain reached without a match
    return 0;
}

int ht_remove(ht_t * hashTable, const char *key, int sizeTable){
    unsigned int bucket = hash(key, sizeTable);

    entry_t *entry = hashTable->entries[bucket];

    if(entry == NULL){// That key does not exist in the table
        return 0;
    }
    entry_t *prev;
    while(entry!=NULL){
        if(strcmp(entry->key, key) == 0){
            if(entry == hashTable->entries[bucket]){
                hashTable->entries[bucket] = entry->next;
            }
            
            free(entry->key);
            free(entry);
            hashTable->num_entries--;
            
            return 1;
        }
        prev = entry;
        entry = entry->next;
    }
    // End of chain reached without a match
    return 0;
}

void ht_print(ht_t *hashTable, int sizeTable){
    int i = 0;
    entry_t *entry;
    for(; i < sizeTable; i++){
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
static void ll_free(entry_t *ll){
    if(ll == NULL){
        return;
    }else{
        ll_free(ll->next);
        free(ll->key);
        free(ll);
        return;
    }
}

void ht_free(ht_t *hashTable, int sizeTable){
    int i = 0;
    for(; i < sizeTable; i++){
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

// The idea is to mantain a hash table of size K
int containsDuplicateAtDistanceK(int *array, int arrayLength, int k){

    int sizeTable = k;
    ht_t *hashTable = ht_create(sizeTable);
    int i = 0;
    unsigned int value;
    char key[MAX_LENGTH_NUMBER+1], old_key[MAX_LENGTH_NUMBER+1]; // counts the '\0'
    for(; i < arrayLength; i++){
        sprintf(key, "%d", array[i]);
            
        if(ht_get(hashTable, key, &value, sizeTable) && ((i-value) <= k)){
            ht_free(hashTable, sizeTable);
            return 1;
        }
        if(!ht_set(hashTable, key, i, sizeTable)){
            sprintf(old_key, "%d", array[i-k]);
            if(!ht_remove(hashTable, old_key, sizeTable)){
                printf("Unexpected error in ht_remove()\n");
            }
        }
        ht_set(hashTable, key, i, sizeTable);
        ht_print(hashTable, sizeTable);
        printf("\n");
    }
    ht_free(hashTable, sizeTable);
    return 0;
}


int main(void) { 
   
  // keep this function call here
  // int A[] = {3, 3, 3, 3, 3, 3, 3, 8};
  int A[] = {99,1,19,99,99};
  int arrLength = sizeof(A) / sizeof(*A);

  int k = 2;

  if(containsDuplicateAtDistanceK(A, arrLength, k)){
    printf("There are two duplicates at distance at most %d.\n", k);
  }else{
    printf("There are no duplicates at distance at most %d.\n", k);
  }

  
  return 0;
    
}

// Complexity Analysis - Hash Table solution
// Time complexity : O(n). In the worst case, for each element in the array we are performing a
// get and/or a set operation, both of which take constant time (O(1)). Therefore, O(n).
// Space complexity: O(n). The space used by a hash table is linear with the number of elements in it

// Complexity Analysis - Sorting algortithm solution (not implemented here)
// Time complexity : O(n log(n)). Sorting is O(n log(n)) and sweeping is O(n). Therefore the time complexity
// is dominated by the sorting algorithm and therefore is O(n log(n))
// Space complexity: Space depends on the sorting implementation. In the case of 'heapsort' the 
// space complexity is O(1). 
// Space complexity: O(n). The space used by a hash table is linear with the number of elements in it