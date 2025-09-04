#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd1, fd2;
	int n;
	char c; //문자를 하나씩 처리

	//읽기 전용 파일 열기
	fd1 = open("data.txt", O_RDONLY, 0);
	//쓰기 전용 파일 열기 없으면 파일 생성
	fd2 = open("2.txt", O_WRONLY | O_CREAT, 0644); 
	
	//읽은 파일의 내용을 쓰는 파일에 복사(1바이트 씩 읽고쓰기 반복)
	while ((n = read(fd1, &c, 1)) > 0)
		if (write(fd2, &c, 1) != 1)
			perror("write");
	return 0;
}
