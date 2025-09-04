#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {

        int j,i,r;
	int arr[10]; //0~9의 숫자가 나왔는지 확인하기 위한배열
	int count = 0; //나온 숫자의 개수 카운트

	for(j=0; j<10; j++){ //0~9 인덱스의 값을 0으로 초기화
		arr[j] = 0;
	}

        // 시드를 현재 시간으로 초기화 하여 매번 다른값을 생성
        srand((unsigned int) time(NULL));
	
	while(1) { //break가 될때까지 반복
        // 0~9 사이의 랜덤 정수 10개 출력
        for (i = 0;  i < 10; i++) {
                r = rand() % 10; // 0~9 사이의 정수
                if(arr[r] == 0){ // 만약 나온적이 없는 숫자라면 출력					
			printf("%d ",r);
			arr[r] = 1; // 나온것을 체크
			count++; // 출력 갯수 체크
			if(count == 3) // 출력이 3개가 되면 그만함
				break;
        		}
		}
		if(count == 3) //출력이 3개가 되면 그만함
			break;
	}
        printf("\n");
        return 0;
}
