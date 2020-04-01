#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s env_var\n", argv[0]);
		exit(1);
	}
	
	char *ptr = getenv(argv[1]);
	if (ptr != NULL)
	{
		printf("Estimated address: %p\n", ptr);
		return 0;
	} else {
		printf("Error finding env_var\n");
		exit(1);
	}
}
