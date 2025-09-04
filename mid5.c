#include <stdio.h>

// 소수 30개를 출력하는 함수
int main(void)
{
        int prime;
        int i;
        int a; // 나누어 떨어질 때를 카운트하는 변수
	int count = 0; // 소수 출력 갯수를 세는 변수

        for ( prime = 1; count < 30; prime++) {
                for (i = 1; i <= prime; i++){
                        if(prime % i == 0)
                                a++;
                }
                if (a == 2){ // 나누어 떨어지는 경우가 1과 자기자신 두가지일때
                        printf("%d ", prime);
			count = count + 1;
			a = 0;
			if (count % 5 == 0)
				printf("\n");

		}
                else
                   a = 0;
        }
}

