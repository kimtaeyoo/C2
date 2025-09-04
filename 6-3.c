#include<stdio.h>

// fibonacci 수열을 재귀적으로 계산하는 함수
int fibonacci(int n)
{
	if (n==1)
		return 1;
	if (n==2)
		return 1;

	return fibonacci(n-1) + fibonacci(n-2);
}

// fibonacci(1) ~ fibonacci(20) 까지의 값을 출력
int main(void)
{
	int i;
	int n = 20;

	for (i=1; i<n+1; i++)
		printf("F%d = %d\n",i ,fibonacci(i));

	return 0;
}
