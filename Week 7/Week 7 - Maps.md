# Week 7 - Maps

## Team

Team name: Oleksandr
Date:

Members
Oleksandr Kuprii

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             |  Oleksandr    |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              |  Oleksandr    |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. |  Oleksandr    |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   |    Oleksandr  |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion.

### Activity 1: The ctype header file

The **ctype.h** header file of the C Standard Library declares several functions that are useful for testing and mapping characters.

```c
This function checks whether the passed character is alphanumeric.
int isalnum(int c)
```

```c
This function checks whether the passed character is alphabetic.
int isalpha(int c)    
```

```c
This function checks whether the passed character is decimal digit.
int isdigit(int c)
```

```c
This function checks whether the passed character is lowercase letter.
int islower(int c)
```

```c
This function checks whether the passed character is an uppercase letter.
int isupper(int c)
```

```c
This function checks whether the passed character is printable.
int isprint(int c)
```

```c
This function checks whether the passed character is a punctuation character.
int ispunct(int c)
```

```c
This function checks whether the passed character is white-space.
int isspace(int c)
```

### Activity 2: Count letters in a string

```c
unsigned long countLetters(unsigned long counts[static 26], const char* str){
    unsigned long count = 0;

    for (unsigned long i = 0; i < strlen(str); i++) {
        if (isalpha(str[i])) {
            counts[tolower(str[i]) - 'a']++;
            count++;
        }
    }

    return count;
}

int main(void){
	unsigned long counts[26] = {0};
	const char* text = "The Quick Brown Fox Jumps Over The Lazy Dog.";
	unsigned long total = countLetters(&counts[0], text);
	assert(35 == total);
	printCounts(&counts[0], false, true);
}
```

### Activity 3: Recognizing languages

```c
const char* makeSignature(unsigned long counts[static 26]){
    static char signature[7];

    // Loop 6 times to find 6 characters
    for (int i = 0; i < 6; i++) {
        unsigned long max = 0; // save the maximum count
        int index_max; // save the position of the maximum count in the array

        // For every character count in counts
        for (int j = 0; j < 26; j++) {
            if (counts[j] > max) {  // If the count is bigger than the current maximum
                bool flag = true;
                
                // Check if this character is not already in signature
                for (int k = 0; k < i; k++) {
                    if (signature[k] == (char)('a' + j)) {
                        // The character is already in the signature
                        flag = false;
                    }
                }
                
                // Update the variables if the character was not found in the signature
                if (flag) {
                    max = counts[j];
                    index_max = j;
                }
            }
        }

        // Add the character to the signature
        signature[i] = (char) ('a' + index_max);
    }

    signature[6] = '\0';
    return &signature[0];
}

int main(void) {
    unsigned long counts1[26] = {15,3,4,5,16,6,7,8,9,7,6,3,2,11,14,1,2,12,13};
	unsigned long counts2[26] = {16,4,7,5,20,7,4,3,14,5,9,1,2,18,6,12,9,13,9,15};
	assert(strcmp("eaosrn", makeSignature(counts1)) == 0);
	assert(strcmp("enatir", makeSignature(counts2)) == 0);
}
```

| File       | Signature | Language |
| ---------- | --------- | -------- |
| alice0.txt | etaoin    | en       |
| alice1.txt | iantes    | fi       |
| alice2.txt | eaionr    | it       |
| alice3.txt | enisra    | de       |



### Activity 4: Find out: dictionaries around us

1. A dictionary of words
2. Saving students' grades
3. The calendar of birthdays
4. The list of phone contacts
5. The prices of flats in the house

### Activity 5: Find out: dictionaries in other languages

**Python**
dict - datatype
dict[key] = value - insert a key-value pair
delete dict[key] - delete a key
key in dict.keys() - check if a key exists
dict[key] - retrieve the value associated with a key

**C#**
Dictionary<TKey,TValue> - datatype
Add(TKey key, TValue value) - insert a key-value pair
Remove(TKey key) - delete a key
ContainsKey(TKey key) - check is a key exists
dict[key] - retrieve the value associated with a key

### Activity 6: The ensureCapacity function

```c
bool _ensureCapacity(counter_t* counter, const size_t minimumCapacity){
    size_t new_capacity = counter->capacity;
    while (minimumCapacity > new_capacity){
        new_capacity = new_capacity * GROWTH_FACTOR + 1;
    }

    if (new_capacity > counter->capacity){
        pair_t *ptr = realloc(counter->data, new_capacity * sizeof(pair_t));
        if (ptr != NULL) {
            counter->data = ptr;
            counter->capacity = new_capacity;
            return true;
        }
    }
    return false;
}
```

### Activity 7: insertAt function

```c
bool _insertAt(counter_t* counter, const size_t index, const char* key, unsigned long value) {
    ...
}

int main() {
	counter_t counter;
	initCounter(&counter, 0);
	insert(&counter, "Bob", 3);
	insert(&counter, "Dave", 4);
	insert(&counter, "Alice", 5);
	insert(&counter, "Eva", 3);
	insert(&counter, "Charlie", 7);
	assert(strcmp(counter.data[0].key, "Alice") == 0);
	assert(counter.data[0].value == 5);
	assert(strcmp(counter.data[1].key, "Bob") == 0);
	assert(counter.data[1].value == 3);
	assert(strcmp(counter.data[2].key, "Charlie") == 0);
	assert(counter.data[2].value == 7);
	assert(strcmp(counter.data[3].key, "Dave") == 0);
	assert(counter.data[3].value == 4);
	assert(strcmp(counter.data[4].key, "Eva") == 0);
	assert(counter.data[4].value == 3);
	assert(counter.size == 5);
	assert(counter.capacity >= counter.size);
	destroyCounter(&counter);
}
```

Record your answer here

### Activity 8: Increment function
```c
unsigned long increment(counter_t* counter, const char* key) {
    ...
}

int main(void) {
	counter_t counter;
	initCounter(&counter, 0);
	increment(&counter, "Alice");
	increment(&counter, "Alice");
	increment(&counter, "Alice");
	increment(&counter, "Bob");
	increment(&counter, "Bob");
	assert(counter.size == 2);
	assert(counter.data[0].value == 3);
	assert(counter.data[1].value == 2);
	destroyCounter(&counter);
}
```

### Activity 9: Find out: function `strtok`

The function `strtok` breaks string into a series of tokens using the delimiter.


### Activity 10: How many words?

Record your answer here

## Looking back

### What we've learnt

Formulate at least one lesson learned.

### What were the surprises

Fill in...

### What problems we've encountered

Fill in...

### What was or still is unclear

Fill in...

### How did the group perform?

How was the collaboration? What were the reasons for hick-ups? What worked well? What can be improved next time?





> Written with [StackEdit](https://stackedit.io/).
