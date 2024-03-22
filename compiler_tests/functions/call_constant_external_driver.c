#include <stdio.h>
int f();

int g()
{ return 20; }

int main()
{
    printf("Example function returned: %d\n", f());
    return !(f()==20);
}
