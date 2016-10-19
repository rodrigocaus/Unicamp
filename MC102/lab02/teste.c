#include <stdio.h>

int main ()
{
	float f = 6.3;
	int i = 3;
	int j = f/i;
	if ((f/(double)i) > j)
		j++;
	printf("%d", j);
	return 0;
}