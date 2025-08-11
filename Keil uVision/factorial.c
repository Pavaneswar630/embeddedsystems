#include <reg51.h>

void main() {
    unsigned int i;
    unsigned char num = 12; 
    unsigned long factorial = 1;

    for (i = 1; i <= num; i++) {
        factorial *= i;
    }
    P0 = (unsigned char)(factorial & 0xFF);           
    P1 = (unsigned char)((factorial >> 8) & 0xFF);
    P2 = (unsigned char)((factorial >> 16) & 0xFF);
    P3 = (unsigned char)((factorial >> 24) & 0xFF);   
    while(1); 
}