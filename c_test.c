#include <stdio.h>

int main(void) {
	int prime = 543;

	prime = prime - (100 * (prime/100));

	printf("%d", prime);

}
