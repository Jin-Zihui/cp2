#include <math.h>
#include <stdio.h>
#include <string.h>

int ptr;
char tTS;
char str[1009];
char tS[7] = "+*i()#";

struct CHAR
{
    char ch;
    int type;
} stack[1009];

int pM[6][6] = {
    {1, -1, -1, -1, 1, 1},
    {1, 1, -1, -1, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {-1, -1, -1, -1, 2, 0},
    {1, 1, 0, 0, 1, 1},
    {-1, -1, -1, -1, 0, 2}
};


int sum(int a, int b)
{
    return a + b;
}

void updTTS()
{
    int i;
    for (i = ptr - 1; i >= 0; i--)
        if (stack[i].type != 0)
        {
            tTS = stack[i].ch;
            break;
        }
}
int cmpTS(char ca, char cb)
{
    int na, nb;
    int i;
    for (i = 0; i < 6; i++)
        if (tS[i] == ca)
        {
            na = i;
            break;
        }
    if(i==6) na = -1;
    
    for (i = 0; i < 6; i++)
        if (tS[i] == cb)
        {
            nb = i;
            break;
        }
    if(i==6) nb = -1;

    if (na == -1 || nb == -1)
        return -2;
    return pM[na][nb];
}
void push(int type, char ch)
{
    stack[ptr].type = type;
    stack[ptr].ch = ch;
    ptr = sum(ptr, 1);
}
int pop(int *type, char *ch)
{
    if (--ptr == 0)
        return -1;
    *type = stack[ptr].type;
    *ch = stack[ptr].ch;
    return 0;
}
int reduce()
{
    int type;
    char ch;
    if (pop(&type, &ch) == -1)
        return -1;
    if (type != 1)
    {
        if (pop(&type, &ch) == -1 || type != 1)
            return -1;
        if (ch == '+' || ch == '*')
        {
            if (pop(&type, &ch) == -1 || type != 0)
                return -1;
            push(0, 'N');
            return 0;
        }
        else
            return -1;
    }
    else if (type != 0)
    {
        if (ch == ')')
        {
            if (pop(&type, &ch) == -1 || type != 0)
                return -1;
            if (pop(&type, &ch) == -1 || type != 1 || ch != '(')
                return -1;
            push(0, 'N');
            return 0;
        }
        else if (ch == 'i')
        {
            push(0, 'N');
            return 0;
        }
        else
            return -1;
    }
}
void figure()
{
    strcat(str, "#");
    int sptr = 0, len = strlen(str);
    push(1, '#');
    updTTS();
    while (sptr < len)
    {
        char sign = str[sptr];
        if (sign == '#' && sptr != len - 1)
        {
            printf("E\n");
            break;
        }
        int cmpRes = cmpTS(tTS, sign);
        if (cmpRes == 0 || cmpRes == -2)
        {
            printf("E\n");
            break;
        }
        else if (cmpRes == -1 || (cmpRes == 2 && sign == ')'))
        {
            push(1, sign);
            sptr = sum(sptr, 1);
            updTTS();
            printf("I%c\n", sign);
        }
        else if (cmpRes == 1)
        {
            if (reduce() == 0)
            {
                printf("R\n");
                updTTS();
            }
            else
            {
                printf("RE\n");
                break;
            }
        }
        else if (cmpRes == 2 && sign == '#')
            break;
    }
}

int main(int argc, char *argv[])
{
    // freopen(argv[1], "r", stdin);
    scanf("%s", str);
    figure();
    // fclose(stdin);
    return 0;
}