#include <stdint.h>
#include <stdlib.h>
#include <string.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;

// TODO: Thread definations
// typedef void (*TThreadEntery)(void *);
// typedef uint32_t *TThreadContext;

// void OtherThreadFunction(void *);
// TThreadContext 

// Memory allocation definations
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint32_t *CartridgeStatus = (volatile uint32_t *)(0x4000001C);
typedef void (*FunctionPtr)(void);

int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 11;
    int countdown =1;

    char *Buffer = malloc(32);
    strcpy(Buffer, "Os Starting ...");
    strcpy((char *)VIDEO_MEMORY, Buffer);

    while (1) {
        if (*CartridgeStatus & 0x1) {
            FunctionPtr Fun = (FunctionPtr)((*CartridgeStatus) & 0xFFFFFFFC);
            Fun();
        }
    }

    return 0;
}

extern char _heap_base[];
extern char _stack[];

char *_sbrk(int numbytes) {
    static char *heap_ptr = NULL;
    char *base;

    if(heap_ptr == NULL) {
        heap_ptr = (char *)&_heap_base;
    }

    if ((heap_ptr + numbytes) <= _stack)
    {
        base = heap_ptr;
        heap_ptr += numbytes;
        return (base);
    } else {
        return NULL;
    }
    
}
