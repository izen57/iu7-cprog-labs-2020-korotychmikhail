#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	int pod = (n - 1) / 36 + 1;
	int etag = (n - 1) % 36 / 4 + 1;
	printf("%d %d", pod, etag);
	return 0;
}