#include <stdio.h>
float f(float x, float y, float z);

int main()
{
    printf("Example function returned: %d\n", f(2.0f,3.0f,4.0f));
    return !(f(2.0f,3.0f,4.0f)==14.0f);
}
