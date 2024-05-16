#ifndef __Goop__
#define __Goop__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#ifdef PICO_BUILD
#include "pico/stdlib.h"
#endif

extern void *_THAT_;
#define _(OBJ) (_THAT_=OBJ, (OBJ->class))
#define __(OBJ) (_THAT_=OBJ, (OBJ->class->super))
#define $(OBJ) (_THAT_=OBJ, (OBJ->class->statics))
#define G_METHOD(TYPE, NAME) TYPE (*NAME)

#define G_CALLOC(N, TYPE) ((TYPE *)calloc(N, sizeof(TYPE)))
#define G_MALLOC(TYPE) ((TYPE *)malloc(sizeof(TYPE));
#define G_REALLOC(PTR, N, TYPE) ((TYPE *)realloc(PTR, N * sizeof(TYPE)))
#define G_MEMMOVE(DEST, SRC, N, TYPE) memmove(DEST, SRC, N * sizeof(TYPE));
#define G_EQUALS(a,b) (goop_equals(a,b))
#define G_CAST(TYPE, NAME, FROM) TYPE *NAME = (TYPE *) FROM
#define G_FORWARD(NAME) typedef struct NAME NAME;
#define G_DEBUG 
#define G_TRACE
#define G_PRINTF printf

typedef void Goop;
extern void *Goop_ERROR;
extern int Goop_IERROR;

extern bool goop_equals(void *a, void *b);

#endif // __Goop__