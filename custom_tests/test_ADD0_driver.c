#include <stdio.h>

int f(int x, int y);

int main()
{
    printf("Example function returned: %d\n", f(30,10));
    return !( 40 == f(30,10) );
}
