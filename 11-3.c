#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {

	int i,r;
	// 시드를 현재 시간으로 초기화 하여 매번 다른값을 생성
	srand((unsigned int) time(NULL));
	
	// 0~9 사이의 랜덤 정수 10개 출력
	for (i = 0;  i < 10; i++) {
		r = rand() % 10; // 0~9 사이의 정수
		printf("%d ",r);
	}
	printf("\n");
	return 0;
}
