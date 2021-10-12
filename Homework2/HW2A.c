#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK 100

typedef enum {false , true} bool;

typedef struct {
    char small;
    char large;
    // *Variable "operator"
    // used in ConvInfixToPostfix function
    char operator;
}Hexa_num;

typedef struct {
    Hexa_num items[MAX_STACK];
    int top;
}Stack;

/* Modify from here */
// if you need any user-defined function
/* Modify to here */
int GetPriority(char op) {
    if(op == '*' || op =='/') 
        return 2;
    else if(op == '+' || op == '-') 
        return 1;
    else    
        return 0;
}

bool ComPriority(char op1, char op2) {
    int op1_pr = GetPriority(op1);
    int op2_pr = GetPriority(op2);

    if(op1_pr >= op2_pr) 
        return true;
    else
        return false;
}

int IsDigit(char ch) {
    if(ch>=48 && ch<=57) 
        return 2;
    else if(ch >= 65 && ch <=70)
        return 1;
    else
        return 0;
}

int decideElem(int distinct, char exp) {

    int ret = 0;
    if(distinct == 2)
        ret = exp - '0';
    else if(distinct == 1) 
        ret = exp - 'A'+ 10;
    return ret;
}

char HexaToch(int num) {
    if(num>=0 && num<= 9) {
        return '0'+num;
    }
    else if(num>=10 && num<=15) {
        return 55+num;
    }
}

Hexa_num deciToHexa(int num) {
    Hexa_num ret;
    ret.small = HexaToch(num%16);
    num/=16;
    ret.large = HexaToch(num%16);
    return ret;
}

int elemTodeci(Hexa_num num) {
    char arr[2];
    arr[0] = num.large;
    arr[1] = num.small;
    int number[2];
    int ret = 0;
    for(int i = 0; i<2; i++) {
        if(IsDigit(arr[i]) == 2) {
            number[i] = arr[i]-'0';
        }
        else if(IsDigit(arr[i]) == 1) {
            number[i] = (arr[i]-65)+10;
        }
            
    }
    ret = number[0]*16+number[1];
    return ret;
}

Hexa_num add(Hexa_num b1,Hexa_num b2);
Hexa_num subtract(Hexa_num b1,Hexa_num b2);
Hexa_num multiply(Hexa_num b1,Hexa_num b2);
Hexa_num division(Hexa_num b1,Hexa_num b2);

void InitStack (Stack *pstack);
bool IsFull(Stack *pstack);
bool IsEmpty(Stack *pstack);
Hexa_num Peek(Stack *pstack);
void Push(Stack *pstack,Hexa_num item);
void Pop(Stack *pstack);
void ConvInfixToPostfix(char* exp,char* convExp, int len);
Hexa_num EvalPostfix(char* exp,int len);
void print_Hexa_num(Hexa_num result);

int main() {
    char infix_exp[100];
    char postfix_exp[100];
    Hexa_num result;
    scanf("%s",infix_exp);
    ConvInfixToPostfix(infix_exp,postfix_exp,strlen(infix_exp));
    printf("%s\n", postfix_exp);
    result = EvalPostfix(postfix_exp,strlen(postfix_exp));
    print_Hexa_num(result);
    return 0;
}

void InitStack(Stack *pstack) {
    pstack->top = -1;
}

bool IsFull(Stack *pstack) {
    return pstack->top == MAX_STACK-1;
}

bool IsEmpty(Stack *pstack) {
    return pstack->top == -1;
}

Hexa_num Peek(Stack *pstack) {
    if(IsEmpty(pstack))
        exit(1);
    return pstack->items[pstack->top];
}

void Push(Stack *pstack, Hexa_num item) {
    if(IsFull(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;
}

void Pop(Stack *pstack) {
    if(IsEmpty(pstack))
        exit(1);
    --(pstack->top);
}

void ConvInfixToPostfix(char* exp,char* convExp, int len) {
    Stack stack;
    int idx = 0;
    InitStack(&stack);

    for(int i = 0; i < len; i++) {
        if(IsDigit(exp[i])) 
            convExp[idx++] = exp[i];
        else {
            while(!IsEmpty(&stack) && ComPriority(Peek(&stack).operator, exp[i])) {
                convExp[idx++] = Peek(&stack).operator;
                Pop(&stack);
            }
            Hexa_num push_elem;
            push_elem.operator = exp[i];
            Push(&stack, push_elem);
        }
    }
    while(!IsEmpty(&stack)) {
        convExp[idx++] = Peek(&stack).operator;
        Pop(&stack);
    }

}

Hexa_num EvalPostfix(char* exp,int len) {
    Stack stack;
    Hexa_num op1, op2;
    int flag = 1, distinct;
    InitStack(&stack);
    for(int i = 0; i<len; i++) {
        distinct = IsDigit(exp[i]);
        if(distinct) {
            Hexa_num push_elem;
            if(flag) {
                push_elem.large = exp[i];
                flag = 0;
            }
            else {
                push_elem.small = exp[i];
                flag = 1;
                Push(&stack, push_elem);
            }
        }
        else {
            op2 = Peek(&stack); Pop(&stack);
            op1 = Peek(&stack); Pop(&stack);
            //printf("op1: %c%c\n", op1.large,op1.small);
            //printf("op2: %c%c\n", op2.large,op2.small);

            Hexa_num res;
            if(exp[i] == '+') 
                res = add(op1, op2);
            else if(exp[i] == '-')
                res = subtract(op1, op2);
            else if(exp[i] == '*')
                res = multiply(op1, op2);
            else if(exp[i] == '/')
                res = multiply(op1, op2);
            //printf("res: %c%c\n",res.large, res.small);
            Push(&stack, res);
        }
    }

    return Peek(&stack);
}

void print_Hexa_num(Hexa_num result) {
    printf("%c%c", result.large,result.small);
}

Hexa_num add(Hexa_num b1,Hexa_num b2) {
    int op1 = elemTodeci(b1);
    int op2 = elemTodeci(b2);
    int num = op1+op2;
    
    Hexa_num ret = deciToHexa(num);
    return ret;
}
Hexa_num subtract(Hexa_num b1,Hexa_num b2) {
    int op1 = elemTodeci(b1);
    int op2 = elemTodeci(b2);
    int num = op1-op2;
    
    Hexa_num ret = deciToHexa(num);
    return ret;
}
Hexa_num multiply(Hexa_num b1,Hexa_num b2) {
    int op1 = elemTodeci(b1);
    int op2 = elemTodeci(b2);
    int num = op1*op2;
    
    Hexa_num ret = deciToHexa(num);
    return ret;
}
Hexa_num division(Hexa_num b1,Hexa_num b2) {
    int op1 = elemTodeci(b1);
    int op2 = elemTodeci(b2);
    int num = op1/op2;
    
    Hexa_num ret = deciToHexa(num);
    return ret;
}

/* Modify from here */
// implementation of functions
/* Modify to here */