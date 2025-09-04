#include <stdio.h>
#include<string.h>

void myqsort(char *v[], int left, int right);
void writelines(char *lineptr[], int nlines);
void swap(char *v[], int i, int j);

int main(void)
{
       char *a[] = {"bach", "handel", "mozart", "beethoven", "brahms", "chopin"};
       int n = sizeof(a) / sizeof(char *);

       printf("\nBefore sort\n"); // 역정렬 전 출력
       writelines(a,n);

       myqsort(a, 0, n-1);

       printf("\nAfter sort.\n"); // 역정렬 후 출력
       writelines(a, n);

       return 0;

}

//qsort: 사전적으로 문자를 역정렬하는 함수
void myqsort(char *v[], int left, int right)
{
        int i, last;
        void swap(char *v[], int i, int j);

        if (left >= right) // 정렬할 범위가 1개 이하 이면 리턴
                return;
        swap(v, left, (left + right)/2); // 중간값을 맨앞으로 가져와 pivot 설정
        last = left; // last = pivot 보다 작은 값의 마지막 인덱스를 저장
        for (i = left+1; i <= right; i++) //순회하며 pivot 보다 큰값을 앞으로 이동
                if(strcmp(v[i], v[left]) > 0)
                        swap (v, ++last, i);
        swap(v, left, last); // pivot 보다 큰값이 왼쪽에 있게됨
        myqsort(v, left, last-1); // 왼쪽 부분 정렬
        myqsort(v, last+1, right); // 오른쪽 부분 정렬
}

// swap: v[i] 와 v[j]의 값을 서로 바꿔주는 함수
void swap(char *v[], int i, int j)
{
        char *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;

}

//writeline: write output line
void writelines(char *lineptr[], int nlines)
{
        int i;

        for (i = 0; i < nlines; i++)
                printf("%s\n" ,lineptr[i]);

}

