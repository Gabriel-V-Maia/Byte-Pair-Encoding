#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#define INITIAL_CAPACITY 4

typedef struct {
    char pair[3];
} pair;

typedef struct {
    unsigned short value;
} token;


typedef enum {
    TYPE_INT,
    TYPE_TOKEN,
    TYPE_PAIR
} ValueType;

typedef struct {
    ValueType type;
    union {
        int i;
        token tok;
        pair pr;
    } value;
} Any;

typedef struct {
    Any* data;
    size_t size;
    size_t capacity;
} Vector;

typedef struct {
    int x;
    int y;
} point;


void init_vector(Vector* vec)
{
    vec->data = malloc(INITIAL_CAPACITY * sizeof(Any));
    if (!vec->data) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
}

void append_vector(Vector* vec, Any element)
{
    if (vec->size == vec->capacity)
    {
        vec->capacity *= 2;
        Any* new_data = realloc(vec->data, vec->capacity * sizeof(Any));
        if (!new_data) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        vec->data = new_data;
    }

    vec->data[vec->size++] = element;
}


void free_vector(Vector* vec) 
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

token tokenize_pair(pair Pair)
{
    token T;

    T.value =
        ((unsigned short)(unsigned char)Pair.pair[0] << 8) |
         (unsigned short)(unsigned char)Pair.pair[1];

    return T;
}

// MAP = {
//  p1 = {
//      x
//      y
//   }
// }
//


/*
 *
 * Denonimado inutil até segunda ordem
Vector mapPoints(Vector* points)
{
    Vector Map;

    for(int i=0;i > points->size;i++)
    {
    }


    return Map;
}

*/

// formula:
// d = sqrt( (p1.x - p2.x) - (p1.y - p2.y) )
double difference_between_points(point* p1, point* p2)
{
    double diff1 = p1->x - p2->x; 
    double diff2 = p1->y - p2->y;
    double d = sqrt(diff1 * diff1 + diff2 * diff2); 
    
    return d;
}



int main(void)
{
    const char str[] = "The quick brown fox jumps over the lazy dog";

    size_t str_size = sizeof(str) - 1;


    Vector tokens;
    init_vector(&tokens);

    Vector vocab;
    init_vector(&vocab);


    for (size_t i = 0; i + 1 < str_size; i++)
    {
        pair Pair;

        Pair.pair[0] = str[i];
        Pair.pair[1] = str[i + 1];
        Pair.pair[2] = '\0';

        Any a;
        a.type = TYPE_PAIR;
        a.value.pr = Pair;
        append_vector(&vocab, a);

        token T = tokenize_pair(Pair);

        Any b;
        b.type = TYPE_TOKEN;
        b.value.tok = T;
        append_vector(&tokens, b);
    }


    char input[1024];

    scanf("%s", &input);

    


    
    return 0;
}


