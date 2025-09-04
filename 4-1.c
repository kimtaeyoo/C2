#include<stdio.h>
//데이터 타입의 크기를 확인하는 프로그램
int main(void)
{
	printf("char %d \n",(int)sizeof(char)); // char의 데이터 크기
	printf("short %d \n",(int)sizeof(short)); // short의 데이터 크기
	printf("int %d \n",(int)sizeof(int)); // int의 데이터 크기
	printf("long %d \n",(int)sizeof(long)); // long의 데이터 크기
	printf("float %d \n",(int)sizeof(float)); // float의 데이터 크기
	printf("double %d \n",(int)sizeof(double)); // double의 데이터 크기
	printf("long double %d \n",(int)sizeof(long double)); 
	// long double의 데이터 크기
	return 0;
}

