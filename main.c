#include <stdio.h>
#include <stdlib.h>
float fact(int n)
{
    int i,f=1;
    {

        for(i=n; i>0; i--)
        {
            f*=i;
        }
    }
    return f;
}
int main()
{
    float sum=0;
    int n,i;
    printf("Enter the number of terms:");
    scanf("%d",&n);
    for(i=0; i<2*n; i+=2)
    {
        sum+=pow(i+1,2)/fact(i);
    }
    printf("%f",sum);
    return 0;
}
