#include<stdio.h>

// cp: copy files and directories
int main(int argc, char *argv[]) 
{
	FILE *infp, *outfp;
	int c;

	infp = fopen(argv[1], "r"); // intp: 입력한 첫번째 파일 열기
	outfp = fopen(argv[2], "w"); // outfp: 입력한 두번째 파일 열기
	
	//첫번째 파일의 내용을 두번째 파일에 복사
	while ((c = getc(infp)) != EOF) 
	       	putc(c , outfp);

	fclose(infp);
	fclose(outfp);
	
	return 0;
}
