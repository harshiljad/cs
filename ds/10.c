#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

#define MAX 50

struct cstack{
    char st[MAX];
    int top;
};

struct istack{
    int st[MAX];
    int top;
};

void initcstack(struct cstack* s){
    s->top = -1;
}

void pushc(struct cstack* s, char val){
    if(s->top < MAX-1)
        s->st[++s->top] = val;
}

char popc(struct cstack* s){
    if(s->top == -1)
        return '\0';
    return s->st[s->top--];
}

char peekc(struct cstack* s){
    if(s->top == -1)
        return '\0';
    return s->st[s->top];
}

void initistack(struct istack* s){
    s->top = -1;
}

void pushi(struct istack* s, int val){
    if(s->top < MAX-1)
        s->st[++s->top] = val;
}

int popi(struct istack* s){
    if(s->top == -1)
        return 0;
    return s->st[s->top--];
}

int precedence(char op){
    switch(op){
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return 0;
}

void infixtopostfix(char infix[], char postfix[]){
    struct cstack s;
    initcstack(&s);

    int i = 0, k = 0;
    char ch;

    while((ch = infix[i++]) != '\0'){
        if(isalnum(ch)){
            postfix[k++] = ch;
        }
        else if(ch == '('){
            pushc(&s, ch);
        }
        else if(ch == ')'){
            while(peekc(&s) != '(')
                postfix[k++] = popc(&s);
            popc(&s);
        }
        else{
            while(precedence(peekc(&s)) >= precedence(ch))
                postfix[k++] = popc(&s);
            pushc(&s, ch);
        }
    }

    while(s.top != -1)
        postfix[k++] = popc(&s);

    postfix[k] = '\0';
}

int applyoperator(int a, int b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

int evaluatePostfix(char postfix[]){
    struct istack s;
    initistack(&s);

    for(int i = 0; postfix[i] != '\0'; i++){
        char ch = postfix[i];

        if(isdigit(ch)){
            pushi(&s, ch - '0');
        }
        else{
            int b = popi(&s);
            int a = popi(&s);
            pushi(&s, applyoperator(a, b, ch));
        }
    }
    return popi(&s);
}

int main(){
    char infix[MAX], postfix[MAX];
    int choice;

    while(1){
        printf("\n1.Infix to Postfix");
        printf("\n2.Evaluate Postfix");
        printf("\n3.Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter Infix Expression: ");
                scanf("%s", infix);
                infixtopostfix(infix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;

            case 2:
                printf("Evaluation Result: %d\n", evaluatePostfix(postfix));
                break;

            case 3:
                exit(0);
        }
    }
}
