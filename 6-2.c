#include<stdio.h>
// v[i] 와 v[j] 의 값을 서로 바꿔주는 함수
void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;

}
// pivot의 값으로 왼쪽에 작은값 오른쪽에 큰값이 오게 재귀적으로 수행하여 정렬하는 함수 
void qsort(int v[], int left, int right) // left = 시작 인덱스, right = 끝 인덱스
{
	int i, last;
	void swap(int v[], int i, int j);

	if (left >= right) // 정렬할 범위가 1개 이하 이면 리턴
		return;
	swap(v, left, (left + right)/2); // 중간값을 맨앞으로 가져와 pivot 설정
	last = left; // last = pivot 보다 작은 값의 마지막 인덱스를 저장
	for (i = left+1; i <= right; i++) //순회하며 pivot 보다 작은 값을 앞으로 이동
		if(v[i] < v[left])
			swap (v, ++last, i);
	swap(v, left, last); // pivot 보다 작은값이 왼쪽에 있게됨
	qsort(v, left, last-1); // 왼쪽 부분 정렬
	qsort(v, last+1, right); // 오른쪽 부분 정렬
}

int main(void)
{
	int m[] = {12, 3, 4, 6, 10, 9, 56, 0, 54, 13, 7, 30};
	int n = sizeof(m)/sizeof(int); // 리스트 원소의 개수

	printf("Before Sort\n"); // 정렬 전 출력 
	for (int i = 0; i<n; ++i)
		printf("%d ", m[i]);
	putchar('\n');

	qsort(m, 0, n-1); // 정렬

	printf("After Sort\n"); // 정렬 후 출력
        for (int i = 0; i<n; ++i)
                printf("%d ", m[i]);
        putchar('\n');

	return 0;
}

