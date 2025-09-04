#include<stdio.h>
// shellsort: int v[0] 부터 int v[n-1] 까지 오름차순으로 정렬한다.
void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	for (gap = n/2; gap>0; gap /= 2) //숫자 간의 gap은 1/2씩 줄임
			//gap만큼 떨어져있는 두 수를 비교해 큰값이 더 작은 index
			//에 있다면 서로 바꾸고 다시 전 단계로 돌아가서 비교함  
		for (i=gap; i<n; i++)
			for (j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}
// 주어진 배열이 정렬되기 전과 정렬된 후를  보여줌
int main(void)
{
	int a[] = {9, 6, 10, 4, 2, 3, 1, 7, 11};
	int i;
	int l = sizeof(a)/sizeof(int); // a의 원소의 수
	
	// 정렬되기전 a의 정렬 순서 출력
	printf("Before sort\n"); 
	for (i=0; i<l; ++i)
		printf("%4d", a[i]);
	putchar('\n');

	shellsort(a, l); // a를 정렬시킴
	
	// 정렬된 후 a의 정렬 순서 출력
	printf("After sort\n");
        for (i=0; i<l; ++i)
                printf("%4d", a[i]);
        putchar('\n');

	return 0;
}

