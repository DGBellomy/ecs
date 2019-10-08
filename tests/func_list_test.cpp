#include <stdio.h>

typedef void (*sysFuncPtr)(int);

void dothis(int x)
{
    printf("dothis: %d\n", x + 2);
}

void dothat(int x)
{
    printf("dothat: %d\n", x * 2);
}

void testFuncs()
{
    sysFuncPtr* funcs;
    funcs = new sysFuncPtr[5];
    printf("sizeof funcs: %lu\n", sizeof(funcs));


    funcs[0] = dothis;
    funcs[1] = dothat;

    for (int i = 0; i < 2; ++i)
    {
        printf("sizeof funcPtr %d: %lu\n", i, sizeof(funcs[i]));
        funcs[i](2);
    }
}

int main()
{
    testFuncs();

    return 0;
}
