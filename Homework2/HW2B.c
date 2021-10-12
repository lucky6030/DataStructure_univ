#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK 100

typedef enum {false, true} bool;
typedef char Data;

typedef struct {
    Data items[MAX_STACK];
    int top;
} Stack;

void InitStack(Stack *pstack) {
    pstack->top = -1;
}

bool IsFull(Stack *pstack) {
    return pstack->top == MAX_STACK-1;
}

bool IsEmpty(Stack *pstack) {
    return pstack->top == -1;
}

Data Peek(Stack *pstack) {
    if(IsEmpty(pstack)) 
        exit(1);
    return pstack->items[pstack->top];
}

void Push(Stack *pstack, Data item) {
    if(IsFull(pstack)) 
        exit(1);
    pstack->items[++(pstack->top)] = item;
}

void Pop(Stack *pstack) {
    if(IsEmpty(pstack)) 
        exit(1);
    --(pstack->top);
}

int main() {
    char input[102];
    char compare[102];
    scanf("%s", input);
    
    Stack stack;
    InitStack(&stack);
    char ch;

    for(int i = 0; i<strlen(input); i++) {
        Push(&stack, input[i]);
    }
    int idx = 0;
    while(!IsEmpty(&stack)) {
        ch = Peek(&stack);
        compare[idx++] = ch;
        printf("%c", ch);
        Pop(&stack);
    }   

    int cnt =0;
    for(int i = 0; i<strlen(input); i++) {
        if(input[i] == '*' || compare[i] == '*')
            continue;
        if(input[i] != compare[i]) {
            cnt++;
        }
        
    }
            
    printf("\n%d", cnt);
}