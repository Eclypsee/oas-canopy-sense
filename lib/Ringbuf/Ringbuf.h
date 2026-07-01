#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h> 
typedef struct Ringbuf
{
    int16_t oldest;
    int16_t newest;
    int16_t size;
    int *data;
} Ring;

/* Initialization and cleanup */
Ring *Ring_init(uint16_t size);
void Ring_clean(Ring *r);

/* Queue operations */
int Ring_enqueue(Ring *r, int num);
int Ring_dequeue(Ring *r, int *dat);
int Ring_peek(Ring *r, int *dat);

/* Status checks */
int Ring_isFull(Ring *r);
int Ring_isEmpty(Ring *r);

/* Debug */
void Ring_show(Ring *r);

#endif /* RINGBUF_H */