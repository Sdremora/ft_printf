
#include <stdio.h>
#include <math.h>
#include <wchar.h>


int main(void)
{
    union {
        long double			num;
        unsigned char	byte[sizeof(long double)];
    } un;
    int mask = 1;
    unsigned char    buf[sizeof(un.num) * 8];

    un.num = -123456789012345678901236.0;
    int n = 0;
    int i = 0;
    while (n < sizeof(un.num) * 8)
    {
        buf[n] = (un.byte[i] & mask) > 0 ? 1 : 0;
        mask = mask << 1;
        n++;
        if (n % 8 == 0)
        {
            i++;
            mask = 1;
        }
    }
    n = sizeof(un.num) * 8 - 1;
    while (n >= 0)
    {
        printf("%c", buf[n] + '0');
        if (n % 8 == 0)
            printf(" ");
        n--;
    }
    printf("\n");

}