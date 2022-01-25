// thread test 2 :
#include "types.h"
#include "stat.h"
#include "user.h"

int stack[4096] __attribute__ ((aligned (4096))); 
int x = 0;
void printTest(void* args) {
    for(int i = 0; i < *(int*) args ; i++)
        printf(1, "hello for the %dth time\n", i+1);
}

int main(int argc, char *argv[]) {
    int argument = 8;
    int tid = threadCreator(&printTest, (void*)&argument);
    if (tid < 0)
        printf(1, "error\n");
    
    threadWait();
    printf(1, "thread id is : %d\n", tid);
    exit();
}