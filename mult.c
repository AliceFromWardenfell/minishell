#include "executor.h"

int		main(void)
{
	int		m1;
	int		m2;

	//printf("Enter first multiplier: ");
	scanf("%d", &m1);
	//printf("Enter second multiplier: ");
	scanf("%d", &m2);
	printf("%d * %d = %d\n", m1, m2, m1 * m2);
	return (0);
}