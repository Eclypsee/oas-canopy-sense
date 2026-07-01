#include <assert.h>
#include <stdio.h>
#include "Ringbuf.h"

int main(void)
{
    Ring *r = Ring_init(5);
    assert(r != NULL);

    int x;

    /* Initially empty */
    assert(Ring_isEmpty(r));
    assert(!Ring_isFull(r));
    assert(Ring_dequeue(r, &x) == -1);
    assert(Ring_peek(r, &x) == -1);

    /* Basic enqueue, peek, dequeue */
    assert(Ring_enqueue(r, 4) == 0);
    assert(Ring_enqueue(r, 14) == 0);
    assert(Ring_enqueue(r, 24) == 0);

    assert(Ring_peek(r, &x) == 0);
    assert(x == 4);

    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 4);

    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 14);

    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 24);

    assert(Ring_isEmpty(r));
    assert(!Ring_isFull(r));

    /* Fill completely */
    assert(Ring_enqueue(r, 1) == 0);
    assert(Ring_enqueue(r, 2) == 0);
    assert(Ring_enqueue(r, 3) == 0);
    assert(Ring_enqueue(r, 4) == 0);
    assert(Ring_enqueue(r, 5) == 0);

    assert(Ring_isFull(r));
    assert(Ring_enqueue(r, 6) == -1);

    Ring_show(r);
    printf("==============================\n");

    /* Remove two items */
    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 1);

    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 2);

    Ring_show(r);
    printf("==============================\n");

    assert(!Ring_isFull(r));
    assert(!Ring_isEmpty(r));

    /* Wrap-around enqueue */
    assert(Ring_enqueue(r, 6) == 0);
    assert(Ring_enqueue(r, 7) == 0);

    assert(Ring_isFull(r));

    Ring_show(r);
    printf("==============================\n");

    /* Verify FIFO order after wrap-around */
    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 3);

    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 4);

    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 5);

    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 6);

    assert(Ring_dequeue(r, &x) == 0);
    assert(x == 7);

    Ring_show(r);
    printf("==============================\n");
    
    assert(Ring_isEmpty(r));
    assert(!Ring_isFull(r));
    assert(Ring_dequeue(r, &x) == -1);
    assert(Ring_peek(r, &x) == -1);

    Ring_clean(r);

    puts("All tests passed!");
    return 0;
}