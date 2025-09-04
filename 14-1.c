#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tel { //이름, 번호, 메모를 가지는 구조체 생성
    char name[30];
    char phone[20];
    char memo[50];
};

int main(void) {
	
	FILE *fp;
	char line[100];
	struct Tel tels[100]; //Tel 구조체 배열
	int count = 0; //tels의 count
	
	//파일 열기
	fp = fopen("data.txt", "r");
	
	//한 줄씩 읽기 반복
    	while (fgets(line, sizeof(line), fp)) {
        
        line[strcspn(line, "\n")] = '\0'; //줄끝 개행 제거

        // ":" 을 기준으로 나눔
        char *name = strtok(line, ":");
        char *tel  = strtok(NULL, ":");
        char *memo = strtok(NULL, "");
	
	// 구조체 배열에 저장
        if (name && tel && memo) {
            strcpy(tels[count].name, name);
            strcpy(tels[count].phone, tel);
            strcpy(tels[count].memo, memo);
            count++;
        }
    }

    fclose(fp); //파일 닫기

    // 구조체 배열 출력
    printf("%-s %-13s %-s\n","이름","전화","메모");
    for (int i = 0; i < count; i++)
	    printf("%-s %-s %-s\n",tels[i].name, tels[i].phone, tels[i].memo);

    return 0;

}

