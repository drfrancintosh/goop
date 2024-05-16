#ifndef __GString__
#define __GString__

#include "GObj.h"

// forward references 
G_FORWARD(GString);

// constants

// members & methods
#define GString_MEMBERS \
    GObj_MEMBERS \
    char *s; \
    int length; \

// NOTE: Methods with a "$" expect a char * argument (or return a char *)
/**
 * proposed methods
strcpy: Copy one string to another
strncpy: Copy a specified number of characters from one string to another
strcat: Concatenate two strings
strncat: Concatenate a certain amount of characters of one string to another
strcmp: Compare two strings
strncmp: Compare a specified number of characters between two strings
strlen: Return the length of a string
strchr: Locate the first occurrence of a character in a string
strrchr: Locate the last occurrence of a character in a string
strstr: Locate a substring in a string
strspn: Get the length of a prefix substring containing only characters from a specified set
strcspn: Get the length of a prefix substring containing none of the characters from a specified set
strpbrk: Locate the first occurrence in a string of any of the characters in another string
strtok: Tokenize a string based on a delimiter
strerror: Get pointer to error message string
*/
#define GString_METHODS \
    GObj_METHODS \
    G_METHOD(void, set$)(char *s); \
    G_METHOD(char *, get$)(); \
    G_METHOD(GString *, toLower)(); \
    G_METHOD(GString *, toUpper)(); \
    G_METHOD(GString *, substr)(int start, int end); \
    G_METHOD(bool, equals)(GString *s); \
    G_METHOD(int, strcmp)(GString *s); \
    G_METHOD(int, length)(); \

// class structs
typedef struct GStringClass {
    GObjClass *super;
    GObjStatics *statics;
    GString_METHODS
} GStringClass;

typedef struct GString {
    GStringClass *class;
    GString_MEMBERS
} GString;

// constructors
extern GString *GString_new(void);
extern GString *GString_new_full(Goop *this, char *name, int max, int extent);

// class init
extern GStringClass *GStringClass_init(char *name, GStringClass *class);

#endif // __GString__