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

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Vector;

typedef struct {
    int x;
    int y;
} point;


void init_vector(Vector* vec) 
{
    vec->data = malloc(INITIAL_CAPACITY * sizeof(int));
    if (vec->data == NULL) {
        perror("Failed to allocate memory for vector");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
}

void append_vector(Vector* vec, token element) 
{
    if (vec->size == vec->capacity) 
    {
        size_t new_capacity = vec->capacity * 2;
        int* new_data = realloc(vec->data, new_capacity * sizeof(int));
        if (new_data == NULL) 
        {
            perror("Failed to reallocate memory for vector");
            exit(EXIT_FAILURE);
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size] = element.value;
    vec->size++;
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

    for (size_t i = 0; i + 1 < str_size; i++)
    {
        pair Pair;

        Pair.pair[0] = str[i];
        Pair.pair[1] = str[i + 1];
        Pair.pair[2] = '\0';

        token T = tokenize_pair(Pair);
        append_vector(&tokens, T);

    }
    
    return 0;
}


