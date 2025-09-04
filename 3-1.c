#include<stdio.h>

#define IN 1 	// 단어 안일때
#define OUT 0	// 단어 밖일때

// 입력받은 것의 characters, word, line의 수를 세는 프로그램
int main(void)
{
	int c, nl, nw, nc, state; // nl=line, nw=word, nc=character  

	state = OUT;
	nl = nw = nc = 0;
	while ((c=getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if ( state == 0 ){
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d\n" , nl, nw ,nc);
}


