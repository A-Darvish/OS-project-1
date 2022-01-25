#include "types.h"
#include "stat.h"
#include "user.h"

#define PAGESIZE 4096

int threadCreator(void (*fn) (void *), void *arg) {

    // allocating 2 page sizes for fptr in father's heap :
    void *fptr = malloc(2 * (PAGESIZE));
    void *stack;

    // allocation failed:
    if(fptr == 0)
        return -1;
    
    // checking if fptr is page alingned :
    int mod = (uint)fptr % PAGESIZE;
    if (mod == 0) 
        stack = fptr;
    else
        stack = fptr + (PAGESIZE - mod);

    int tid = threadCreate((void*)stack);
    
    // thread creation failed :
    if (tid<0)
        printf(1, "thread creation failed!\n");
    else if(tid == 0) {
        // function execution :
        (fn)(arg);
        // free memory when done :
        free(stack);
        exit();
    }
    return tid;
}