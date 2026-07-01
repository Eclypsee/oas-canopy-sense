
#include "Ringbuf.h"

Ring*Ring_init(uint16_t size){
    if(size<1)return NULL;//implementation requires at least 1 slots
    Ring*r = malloc(sizeof(*r));
    if(!r)return NULL;

    r->oldest = -1;
    r->newest = -1;
    r->size = size;
    r->data = malloc(sizeof(*r->data)*size);
    if(!r->data){free(r);return NULL;}

    return r;
}

int Ring_isFull(Ring*r){
    return ((r->newest+1)%r->size==r->oldest);
}

int Ring_isEmpty(Ring*r){
    return r->oldest == -1;
}

int Ring_enqueue(Ring*r,int num){
    if(Ring_isFull(r)) return -1;//full
    if(Ring_isEmpty(r)) r->oldest = 0;
    r->newest = (r->newest+1)%r->size;
    r->data[r->newest] = num;
    return 0;
}

int Ring_dequeue(Ring *r, int*dat){
    if(Ring_isEmpty(r)) return -1;//empty
    *dat = r->data[r->oldest];//fifo
    if(r->newest==r->oldest){//exactly one element
        r->newest = -1;
        r->oldest = -1;//cleear queue
    }else{
        r->oldest = (r->oldest+1)%r->size;
    }
    return 0;
}

int Ring_peek(Ring*r, int*dat){
    if(Ring_isEmpty(r))return -1;
    *dat = r->data[r->oldest];
    return 0;
}

void Ring_show(Ring *r){
    if(Ring_isEmpty(r)) return;
    uint16_t i = r->oldest;
    while(i!=r->newest){
        printf("%d\n", r->data[i]);
        i=(i+1)%r->size;
    }
    printf("%d\n", r->data[r->newest]);
}
void Ring_clean(Ring*r){
    if(!r)return;
    free(r->data);
    free(r);
}