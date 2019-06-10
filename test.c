#include <stdio.h>

int main()
{

	unsigned char c = 0x16;

	printf("left: %hx\n", (unsigned char)(c / 16));

	printf("right: %hx", (unsigned char)(c % 16));
}