#ifndef EXACT_COVER_ALGORITHMS_H
#define EXACT_COVER_ALGORITHMS_H

#include "vector.h"

void printfVectorInt(const char * premessage, VectorInt * vec);
void printfVectorVectorInt(const char * premessage, VectorVectorInt * vec);
void scanfVectorInt(int size, VectorInt * vec);
void scanfVectorVectorInt(int lin, int col, VectorVectorInt * vec);
static inline int max(int a, int b)
{
    return a > b ? a : b;
}
static inline int min(int a, int b)
{
    return a < b ? a : b;
}
typedef int (*Comparator)(const void *, const void *);

int intLessComparator(const void * a, const void * b);

long long int gcd(long long int a, long long int b);

int findNextPower(int n);

static inline bool areStringsEquall(const char * a, const char * b)
{
    return strcmp(a, b) == 0;
}
//idk where to place it
void printfComplex(const complex double *c);
Complex scanfComplex();
VectorComplex scanfVectorComplex();

int power(int a, int n);
int powerOfTwo(int n);

//bool equalComplex(const complex double *a, const complex double *b);
enum Sign_enum
{
    PLUS,
    MINUS,
    STOP
};
typedef enum Sign_enum Sign;

bool equal(double a, double b);


#endif //EXACT_COVER_ALGORITHMS_H
