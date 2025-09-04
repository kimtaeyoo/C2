#include<stdio.h>

//각각의 숫자를 입력한 횟수와 공백의 횟수 그 외 나머지들의 횟수를 카운트함
int main (void) 
{
	int c, i, nwhite, nother; // nwhite=공백 nother= 숫자,공백 제외한 나머지
	int ndigit[10]; //숫자 각각의 횟수를 저장하는 배열

	nwhite = nother = 0;
	for (i=0; i<10; ++i) // ndigit 배열의 원소를 0으로 초기화
		ndigit[i] = 0;
	
	while ((c=getchar()) != EOF) {
		if ( c>= '0' && c <= '9') //0~9 의 숫자가 각각 몇번 나오는지
			++ndigit[c-'0']; //횟수를index 0~9에 저장
		else if ( c=='\n' || c==' ' || c== '\t')
			++nwhite;
		else
			++nother;
	}
	
	printf ("digits =");
	for (i=0; i<10; ++i)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n", nwhite, nother);
}

