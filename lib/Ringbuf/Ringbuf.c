
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
    int* arr = malloc(sizeof(int)*r->size);
    if(!arr)return;
    int asdf = Ring_return(r, arr);
    if(asdf!=0){
        for(int i=0;i<asdf;i++)
            printf("%d\n", arr[i]);
    }
    free(arr);
}

int Ring_return(Ring *r, int*array){//gets the ring buffer array in fifo order, returns size of data
    if(Ring_isEmpty(r)) return 0;
    int idx = 0;
    uint16_t i = r->oldest;
    while(i!=r->newest){
        array[idx]=r->data[i];
        i=(i+1)%r->size;
        idx++;
    }
    array[idx]=r->data[r->newest];
    return idx+1;
}

void Ring_clean(Ring*r){
    if(!r)return;
    free(r->data);
    free(r);
}