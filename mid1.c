#include <stdio.h>

// 2진수를 10진수로 바꾸는 함수
int binaryToDecimal(const char *binary, int len)
{
        int decimal = 0;

        for (int i = 0; i < len; i++) {
                if(binary[i] == '0' || binary[i] == '1')
                        decimal = decimal * 2 + (binary[i] - '0');
        }
        return decimal;
}

// 2진수를 입력받아서 16진수를 출력하는 프로그램
int main(void)
{

        int c;
        int i= 0;
        int decimal;
        char binary[100]; // 2진수를 저장하는 배열

        while((c = getchar()) != EOF){
               if (c=='\n'){
                binary[i] = '\0'; // 문자열 만들기
                decimal = binaryToDecimal(binary, i);
                printf("%X\n", decimal);
                i = 0;
               } else {
                      binary[i++] = c;
               }
        }

        return 0;
}

