#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define max 300000

//doesnt work but whatever// 

// Struct to hold the expected close brace character and a pointer to the next element.
int x= 0;
struct element {
    char close[max];
    int top;
    //struct element* next;
};

struct element e;
void push (char);
void pop();


int main(int argc, char* argv[])
{
    e.top= -1; 
    char exp[150000];
    int i= 0;
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    //bool balanced = true;

    char buff;
    while ( fscanf(fp, "%c", &buff)==1 ) {
    }
    while(exp[i]!='#')
    {
        if((exp[i]=='(')||(exp[i]=='[')||(exp[i]=='{'))
            push(exp[i]);
        else if((exp[i]==')')||(exp[i]==')')||(exp[i]=='}'))
        {
            if (exp[i]==')')
            {
                if (e.close[e.top]=='(')
                    pop();
                else
                {
                    printf("no");
                    break;
                }
            }
            if (exp[i]==']')
            {
                if (e.close[e.top]=='[')
                    pop();
                else 
                {
                    printf("no");
                    break;
                }
            }
            if (exp[i]=='}')
            {
                if(e.close[e.top]=='{')
                    pop();
                else{
                    printf("no" );
                    break;
                }
            }
            
        }
    i++;
    }
    
    if (e.top== -1)
        printf(" yes ");
    else
        printf("no");
    fclose(fp);
    
    return 0;
}
void push (char item)
{
    if (e.top==(max-1))
        printf (" ");
    else
    {
        e.top= e.top +1;
        e.close[e.top]= item;
    }
}
void pop()
{
    if (e.top== -1)
    {
        printf (" ");
    }
    else
    {
        printf(" ");
        e.top= e.top - 1;
    }
}

    //bool balanced = true;

    //char buff;
    //while ( fscanf(fp, "%c", &buff)==1 ) {
    //}

    //printf ( balanced ? "yes" : "no" );
    //fclose(fp);
    //eturn 0;



//./balanced tests/test0.txt
// <({})>  ({<>(){}})   YESSSS
// ({)      <<>[<()>]   NOOOOO

