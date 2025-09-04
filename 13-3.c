#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd1, fd2;
	int n;
	char buf[BUFSIZ]; //데이터를 임시로 저장할 버퍼

	//읽기 전용 파일 열기	
	fd1 = open("data.txt", O_RDONLY, 0);
	//쓰기 전용 파일 열기 없으면 파일 생성
	fd2 = open("3.txt", O_WRONLY | O_CREAT, 0644);
	
	//읽은 파일의 내용을 쓰는 파일에 복사(버퍼의 크기만큼 읽고쓰기 반복)
	while((n = read(fd1, buf, BUFSIZ)) > 0)
		if (write(fd2, buf, n) !=n)
			perror("write");
	return 0;
}
