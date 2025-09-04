#include<stdio.h>

// factorial 계산을 재귀적으로 수행하는 함수
unsigned long long factorial(int n) 
//팩토리얼의 계산값이 많이 커지기 때문에 unsigned long long 타입으로 리턴
{
	if ( n == 1 )
		return 1;

	return n * factorial(n-1);
}

//1! ~ 20!의 값을 출력
int main(void)
{
	int i;
	int n = 20;

	for (i = 1; i < n+1; i++)
		printf("%d ! = %lld\n", i, factorial(i));

	return 0;
}

