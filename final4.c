#include<stdio.h>
//소인수 분해를 출력하는 프로그램
int main(void)
{
	int x;

        scanf("%d", &x); // 숫자를 입력 받음

        int i = 2;
	//출력 받은 숫자의 소인수분해 하여 출력
        while (x > 1) {
                if (x % i == 0) { // 소인수 출력
                        printf("%d ", i);
                        x /= i;
			if(x > 1) //소인수 분해가 끝나면 * 출력안함
				printf("* ");
                } else {
                        i++;
                }
        }
        printf("\n");
}
