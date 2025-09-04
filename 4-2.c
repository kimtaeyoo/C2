#include<stdio.h>
//myatoi: 배열을 int값으로 바꿔줌
int myatoi( char s[])
{
	int n, i;
	//문자값의 숫자를 int 값으로 바꿔줌 
	n=0;
	for(i=0; s[i]>='0' && s[i]<='9'; i++)
		n = n * 10 + (s[i] - '0');
	return n;
}
//myatoi의 대한 확인
int main(void)
{
	char str1[] = "1234";
	char str2[] = "4321";

	printf("str %s -> int %d\n", str1, myatoi(str1));
	printf("str %s -> int %d\n", str2, myatoi(str2));
	
	return 0;
}

