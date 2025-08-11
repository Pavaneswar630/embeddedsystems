#include <reg51.h> void main ( )
{
unsigned char sum=0; unsigned char i;
for (i=1; i<=10; i++)
{
sum = sum + i;

}
ACC=sum; P0=sum;
}