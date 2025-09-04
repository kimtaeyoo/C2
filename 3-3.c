#include<stdio.h>
#define MAXLINE 1000 //입력값의 최댓값 1000

int mygetline(char line[], int maxline); 
void copy(char to[], char from[]);

int main(void) // 입력받은 가장 긴 문장을 출력함
{
	int len; // 입력 받은 문장의 길이
	int max; // 입력 받은 가장 긴 문장의 길이 
	char line[MAXLINE]; // 입력 받은 문장을 저장
	char longest[MAXLINE]; // 입력 받은 가장 긴 문장을 저장

	max=0;
	while ((len = mygetline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line); //가장 긴 문장을 복사
		}
	if (max > 0) // 문장이 있으면 출력
		printf("%s", longest);
	return 0;
}

//mygetline = 입력 받은 문장을 s에 저장하고 문장의 길이를 리턴함
int mygetline( char s[], int lim) 
{
	int c, i;
       
	for (i=0; i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0'; // 문자열로 저장
	return i; // 길이 리턴
}

//copy = from에 있는 값을 to에 저장함
void copy ( char to[], char from[])  
{
	int i;

	i=0;
	while ((to[i] = from[i]) != '\0') // 문자열 끝까지 복사
		++i; }
