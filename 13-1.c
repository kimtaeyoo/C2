#include <stdio.h>

int main(void)
{
	FILE *fp;
	char str[] = "0123456789";

	fp = fopen("data.txt", "w"); //data.txt가 없으면 생성, 존재하면 새로씀
	
	//str 문자열을 파일에 100만번 씀
	for (int i = 0; i<1000000; ++i)
		fputs(str, fp);

	return 0;
}
