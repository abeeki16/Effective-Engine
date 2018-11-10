#include <stdio.h>
#include <string.h>

int main(void) {
	//takes in a string and concatenates "hello" to it, then prints it out
	//non-recursive, doesn't explode
	char buffer[80];
	scanf("%s", buffer);
	strcat(buffer, " hello");
	printf(buffer);
	printf("\n");
	return 0;
}
