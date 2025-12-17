#include <stdio.h>
void main()
{
    int a[10], b[10], *pa, *pb, i;
    
    pa = a;
    pb = b;
    for( i = 0; i < 3; i++, pa++, pb++){ 
        *pa = i;
        *pb = 2*i;
     }
    pa = &a[0];
    pb = &b[0];
    for ( i = 0; i < 3; i++, pa++, pb++){
        *pa = *pa + i;
        *pb = *pb + i;
     }
     printf("%d %d", *--pa, *--pb);  /* 输出的数字之间有一个空格 */
     
     return 0;
}
