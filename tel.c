#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include <ctype.h>

#define Max_tel 500 //최대 저장할 수 있는 엔트리 수
#define fixpage 10 //전화번호 리스트의 단위(10개씩)

typedef struct { //이름, 전화번호, 메모를 저장하는 구조체
    char name[30];
    char phone[20];
    char memo[50];
} Tel;

Tel tels[Max_tel]; //500개의 엔트리를 저장할 수 있는 구조체 배열
int tel_count = 0; //현재 엔트리 수

void dataload(void);
void datasave(void);
void list(WINDOW *win);
void search(WINDOW *win);
void add(WINDOW *win);
void delete(WINDOW *win);

//받은 문자가 공백으로만 되어있는지 알려주는 함수 
int is_only_whitespace(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) 
		return 0;
        str++;
    }
    return 1;
}

//메뉴에서 선택된 기능들로 전화번호부를 관리하는 프로그램
int main(void)
{	
	setlocale(LC_ALL, "");  // 한글 깨짐 방지
	
        initscr();
        cbreak();
        noecho();

        WINDOW *menuwin = newwin(15, 40, 1, 1); //메뉴창 정의
	box(menuwin, 0, 0);
	refresh();
        wrefresh(menuwin);

        keypad(menuwin, true); //menuwin 방향키 입력 허용
	
	//메뉴 항목 정의
        char *choices[5] = {"List", "Search", "Add", "Delete", "Exit"};
        int choice;
        int highlight = 0;
	
	dataload(); //data.txt의 정보를 저장
	

	while(1) {
		//방향키로 움직이는 메뉴 항목을 만듬
		mvwprintw(menuwin, 1, 1, "%s","Tel menu");
                for (int i = 0; i < 5; i++) { 
                        if (i == highlight)
                                wattron(menuwin, A_REVERSE);
                        mvwprintw(menuwin, i+4, 1, "%s",choices[i]);
                        wattroff(menuwin, A_REVERSE);
                }
                choice = wgetch(menuwin);
		//방향키로 선택된 색 반전을 조절함
                switch (choice) {
                        case KEY_UP:
                                highlight--;
                                if(highlight == -1)
                                        highlight = 0;
                                break;
                        case KEY_DOWN:
                                highlight++;
                                if(highlight == 5)
                                        highlight = 4;
                                break;
                        default:
                                break;
                }

                if (choice == 10) { //엔터로 선택한 기능을 하는 함수 호출 
         		if (highlight == 0) 
				list(menuwin);
                	else if (highlight == 1) 
				search(menuwin);
                	else if (highlight == 2)
			       	add(menuwin);
                	else if (highlight == 3)
			       	delete(menuwin);
			else if (highlight == 4)
        			break;                        		
       		 }	
	}
	//모든 기능이 끝나면 실행
	datasave(); //갱신된 전화번호부의 내용을 data.txt에 저장
	endwin(); //종료
	return 0;
}

//data.txt의 정보를 구조체와 구조체 배열로 저장해서 전화번호부 정보 저장
void dataload(void)
{
	FILE *fp = fopen("data.txt","r");

	char line[256];
	tel_count = 0;

    	while (fgets(line, sizeof(line), fp)) {
        	line[strcspn(line, "\n")] = '\0';  // 줄바꿈 제거
		// ':'로 나눠져있는 정보를 name, phone, memo로 분할해서 저장
        	char *name = strtok(line, ":");
        	char *phone = strtok(NULL, ":");
        	char *memo = strtok(NULL, ":");
	//각 엔트리의 name, phone, memo를 저장한 것을 구조체 배열에 복사
        if (name && phone) {
	    if (!memo) 
		    memo = "";  // memo가 NULL이면 빈 문자열로 처리	
            
	    strncpy(tels[tel_count].name, name, sizeof(tels[tel_count].name));
            strncpy(tels[tel_count].phone, phone, sizeof(tels[tel_count].phone));
            strncpy(tels[tel_count].memo, memo, sizeof(tels[tel_count].memo));
            
	    tel_count++;
        }
	//500개의 엔트리를 넘으면 저장하지않음
        if (tel_count >= Max_tel) 
		break;
    }

    fclose(fp);
}

//갱신된 전화번호부 정보로 data.txt를 수정
void datasave(void)
{
   FILE *fp = fopen("data.txt", "w");
    //각각 엔트리의 전화번호부 정보로 파일을 수정
    for (int i = 0; i < tel_count; ++i) {
        fprintf(fp, "%s:%s:%s\n", tels[i].name, tels[i].phone, tels[i].memo);
    }

    fclose(fp);
}

//전화번호부를 엔트리 이름으로 정렬하고 각 엔트리의 name, phone, memo를 보여줌
void list(WINDOW *win)
{
	//이름을 기준으로 오름차순 정렬 (버블 정렬)
    	for (int i = 0; i < tel_count - 1; ++i) {
        	for (int j = i + 1; j < tel_count; ++j) {
            	if (strcmp(tels[i].name, tels[j].name) > 0) {
                Tel temp = tels[i];
                tels[i] = tels[j];
                tels[j] = temp;
           	 }
        	}
    	}
	
	datasave(); //갱신된 전화번호부로 data.txt 파일을 수정
	
	//10개의 엔트리씩 한 페이지에 넣을때 필요한 전체 페이지 수
	int total_pages = (tel_count + fixpage - 1) / fixpage;
       	int page = 0;
	int highlight = 0;
	 
       	while (1) {
        	
		//한 페이지의 엔트리의 시작과 끝 인덱스
		int start = page * fixpage;
        	int end = start + fixpage;
        	if (end > tel_count)
			end = tel_count;
		
		//현재창을 지우고 전화번호부 이름 리스트를 출력함
		werase(win);
        	box(win, 0, 0);
        	mvwprintw(win, 0, 2, "Tel List Page %d/%d ", page + 1, total_pages);
		//방향키로 움직이는 정렬된 이름 목록을 출력함
		for (int i = start; i < end; ++i) {
           		 if (i == start + highlight)
                		wattron(win, A_REVERSE);
            		mvwprintw(win, i - start + 2, 2, "%-s", tels[i].name);
            		if (i == start + highlight)
                		wattroff(win, A_REVERSE);
        }
		mvwprintw(win, 12, 2, "[←] Prev  [→] Next  [↑↓] Move");
		mvwprintw(win, 13, 2, "[Enter] View  [q] Quit");	
		wrefresh(win); // 화면 갱신

		int ch = wgetch(win); //누른 키를 받음
		//werase(win);

		if (ch == 'q' || ch == 'Q') { //q를 누르면 메뉴창으로 나감
			werase(win); // 창을 지우고 반복문을 종료
			box(win, 0, 0);
			break;
		}//방향키로 색 반전을 조절하고 left, right는 페이지도 조절
        	else if (ch == KEY_DOWN && highlight < end - start - 1) 
			highlight++;
        	else if (ch == KEY_UP && highlight > 0) 
			highlight--;
        	else if (ch == KEY_RIGHT && page < total_pages - 1) {
            		page++;
            		highlight = 0;
        	}
        	else if (ch == KEY_LEFT && page > 0) {
            		page--;
            		highlight = 0;
        	}
		//엔터키로 이름을 선택하면 정보를 보여줌
		else if (ch == '\n') {
            		int selected = start + highlight;
            		// 현재창을 지우고 선택한 엔트리의 정보를 보여주는 창 생성
			werase(win);
            		box(win, 0, 0);
            		mvwprintw(win, 3, 2, "Name : %s", tels[selected].name);
            		mvwprintw(win, 5, 2, "Phone: %s", tels[selected].phone);
            		mvwprintw(win, 7, 2, "Memo : %s", tels[selected].memo);
            		mvwprintw(win, 12, 2, "Press any key to return");
            		wrefresh(win); // 화면 갱신
            		ch = getch(); //아무 키를 눌러 종료후 다시 리스트로 돌아감
		}

	}
	return;
}

//이름을 입력받아서 찾은 엔트리의 전화번호부의 정보를 보여줌
void search(WINDOW *win)
{
    echo(); //입력이 보이게함
    char keyword[30];
    //전 창을 지우고 이름을 입력받음
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Search phone number");
    mvwprintw(win, 3, 2, "Name : ");
    wgetnstr(win, keyword, sizeof(keyword) - 1);
    noecho(); //다시 입력을 안보이게함

    //입력받은 문자가 공백으로만 되어있거나 입력이 없을 경우 메뉴창으로 돌아감
    if (strlen(keyword) == 0 || is_only_whitespace(keyword)) {
	    werase(win); //현재 창을 지우고 에러 메세지 출력
	    box(win, 0, 0);
            mvwprintw(win, 5, 2, "Search keyword error:");
	    mvwprintw(win, 6, 2, "cannot be empty or whitespace only.");
	    mvwprintw(win, 12, 2, "Press any key to return to menu...");
            wrefresh(win);
            getch();
	    werase(win);
            box(win, 0, 0);
            return; //지우고 메뉴창으로 돌아감
    }
    
    Tel searchs[Max_tel]; //찾은 엔트리들을 저장하는 구조체 배열
    int search_count = 0; //찾은 엔트리 수
    for (int i = 0; i < tel_count; ++i) {
	    //입력받은 문자가 들어있는 이름을 가진 엔트리 정보 저장
        if (strstr(tels[i].name, keyword)) {
            searchs[search_count++] = tels[i];
        }
    } 
    if (search_count == 0) { //입력받은 문자가 들어가는 이름의 엔트리가 없을 때 
	    werase(win); //현재 창을 지우고 에러 메세지 출력
	    box(win, 0, 0);
	    mvwprintw(win, 5, 2, "Not found: '%s'", keyword);
	    mvwprintw(win, 12, 2, "Press any key to return to menu...");
	    wrefresh(win);
	    getch();
	    werase(win);
	    box(win, 0, 0);
	    return; //지우고 메뉴창으로 돌아감
    }
   	//10개의 엔트리씩 한 페이지에 넣을때 필요한 전체 페이지 수
    	int total_pages = (search_count + fixpage - 1) / fixpage;
    	int page = 0;
    	int highlight = 0;
	
	while (1) {
		
		//한 페이지의 엔트리의 시작과 끝 인덱스
                int start = page * fixpage;
                int end = start + fixpage;
		if (end > search_count)
                        end = search_count;
		//현재창을 지우고 찾은 엔트리 이름 리스트를 출력함
                werase(win);
                box(win, 0, 0);
                mvwprintw(win, 0, 2, "Search List Page %d/%d ", page + 1, total_pages);
		//방향키로 움직이는 찾은 이름 목록을 출력함
		for (int i = start; i < end; ++i) {
                         if (i == start + highlight)
                                wattron(win, A_REVERSE);
                        mvwprintw(win, i - start + 2, 2, "%-s", searchs[i].name);
                        if (i == start + highlight)
                                wattroff(win, A_REVERSE);
        	}
		mvwprintw(win, 12, 2, "[←] Prev  [→] Next  [↑↓] Move");
                mvwprintw(win, 13, 2, "[Enter] View  [q] Quit");
                wrefresh(win); // 화면 갱신

                int ch = wgetch(win); // 누른 키를 받음

                if (ch == 'q' || ch == 'Q') { //q를 누르면 메뉴창으로 나감
                        werase(win); // 창을 지우고 반복문을 종료
		       	box(win, 0, 0); 
                        break;
                }//방향키로 색 반전을 조절하고 left, right는 페이지도 조절
                else if (ch == KEY_DOWN && highlight < end - start - 1)
                        highlight++;
                else if (ch == KEY_UP && highlight > 0)
                        highlight--;
                else if (ch == KEY_RIGHT && page < total_pages - 1) {
                        page++;
                        highlight = 0;
                }
		else if (ch == KEY_LEFT && page > 0) {
                        page--;
                        highlight = 0;
                }
		//엔터키로 이름을 선택하면 정보를 보여줌
                else if (ch == '\n') {
                        int selected = start + highlight; //선택한 엔트리의 saerchs 인덱스
			// 현재창을 지우고 선택한 엔트리의 정보를 보여주는 창 생성
                        werase(win);
                        box(win, 0, 0);
                        mvwprintw(win, 3, 2, "Name : %s", searchs[selected].name);
                        mvwprintw(win, 5, 2, "Phone: %s", searchs[selected].phone);
                        mvwprintw(win, 7, 2, "Memo : %s", searchs[selected].memo);
                        mvwprintw(win, 12, 2, "Press any key to return");
                        wrefresh(win); //화면 갱신
                        ch = getch(); //아무 키를 눌러 종료후 다시 리스트로 돌아감
                }

        }		
	return;
}

//name, phone, memo를 입력 받아서 전화번호부에 추가함
void add(WINDOW *win)
{	
    if(tel_count >= Max_tel) { //500개의 엔트리가 가득찼을 때
	    werase(win); //화면을 지우고 에러 화면 출력
    	    box(win, 0, 0);
	    mvwprintw(win, 5, 2, "Tel is full");
	    mvwprintw(win, 8, 2, "Press any key to return");
	    wrefresh(win);
	    getch(); // 아무키나 입력받고 메뉴창으로 돌아감
	    werase(win);
	    box(win, 0, 0);
	    return;
    }
    echo(); //입력이 보임
    char name[30], phone[20], memo[50]; //입력 받을 수 있는 각각의 크기
    //창을 지우고 name, phone, memo를 입력 받는 창을 만듬
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Add new phone number");
    mvwprintw(win, 3, 2, "Name : ");
    wgetnstr(win, name, sizeof(name) - 1);
    mvwprintw(win, 5, 2, "Phone: ");
    wgetnstr(win, phone, sizeof(phone) - 1);
    mvwprintw(win, 7, 2, "Memo : ");
    wgetnstr(win, memo, sizeof(memo) - 1);
    noecho(); //다시 입력이 보이지 않음

    //입력받은 이름이나 번호가 공백으로만 되어있거나 입력이 없을 경우 메뉴창으로 돌아감
    if ((strlen(name) == 0 || is_only_whitespace(name)) || (strlen(phone) == 0 || is_only_whitespace(phone))) {
            werase(win); //현재 창을 지우고 에러 메세지 출력
            box(win, 0, 0);
            mvwprintw(win, 5, 2, "Name or Phone keyword error:");
            mvwprintw(win, 6, 2, "cannot be empty or whitespace only.");
            mvwprintw(win, 12, 2, "Press any key to return to menu...");
            wrefresh(win);
            getch();
            werase(win);
            box(win, 0, 0);
            return; //지우고 메뉴창으로 돌아감
    }

    //입력받은 정보로 구조체 배열에 저장	     
    strncpy(tels[tel_count].name, name, sizeof(tels[tel_count].name));
    strncpy(tels[tel_count].phone, phone, sizeof(tels[tel_count].phone));
    strncpy(tels[tel_count].memo, memo, sizeof(tels[tel_count].memo));
    tel_count++;

    datasave(); //갱신된 전화번호부로 data.txt 파일을 수정

    mvwprintw(win, 10, 2, "added successfully!");
    mvwprintw(win, 12, 2, "Press any key to return to menu...");
    wrefresh(win);
    getch(); // 아무런 키나 입력을 받아 메뉴로 돌아감
    werase(win);
    box(win, 0, 0);
    return;
}

//이름을 입력받아서 찾은 엔트리의 전화번호부의 정보를 보여주고 엔트리의 삭제를 결정
void delete(WINDOW *win)
{
	echo(); //입력을 보이게 함
    	char keyword[30];
	//전 창을 지우고 이름을 입력받는 창을 만듬
    	werase(win);
    	box(win, 0, 0);
    	mvwprintw(win, 1, 2, "Delete phone number");
    	mvwprintw(win, 3, 2, "Name : ");
    	wgetnstr(win, keyword, sizeof(keyword) - 1);
    	noecho(); //다시 입력이 안보임
		 
	//입력받은 문자가 공백으로만 되어있거나 입력이 없을 경우 메뉴창으로 돌아감
        if (strlen(keyword) == 0 || is_only_whitespace(keyword)) {
        werase(win); //현재 창을 지우고 에러 메세지 출력
        box(win, 0, 0);
        mvwprintw(win, 5, 2, "Search keyword error:");
        mvwprintw(win, 6, 2, "cannot be empty or whitespace only.");
        mvwprintw(win, 12, 2, "Press any key to return to menu...");
        wrefresh(win);
        getch();
        werase(win);
        box(win, 0, 0);
        return; //지우고 메뉴창으로 돌아감
        }

    	Tel searchs[Max_tel]; //찾은 엔트리들을 저장하는 구조체 배열
	int tel_idx[Max_tel]; //찾은 엔트리가 tels에 몇번째 인덱스에 있는지 저장 하는 배열
       	int search_count = 0; // 찾은 엔트리의 수
    	for (int i = 0; i < tel_count; ++i) {
		 //입력받은 문자가 들어있는 이름을 가진 엔트리 정보 저장 및 인덱스 저장
       		 if (strstr(tels[i].name, keyword)) {
            		searchs[search_count] = tels[i];
			tel_idx[search_count] = i;
            		search_count++;
        	}
    	}
   	 if (search_count == 0) { //입력받은 문자가 들어가는 이름의 엔트리가 없을 때
		 werase(win); //현재 창을 지우고 에러 메세지 출력
           	 box(win, 0, 0);
            	 mvwprintw(win, 5, 2, "No contact found with name '%s'", keyword);
            	 mvwprintw(win, 12, 2, "Press any key to return to menu...");
            	 wrefresh(win);
            	 getch();
		 werase(win);
		 box(win, 0, 0);
            	 return; // 지우고 메뉴창으로 돌아감
	 }
	 
	 int page = 0;
         int highlight = 0;
	
         while (1) {
		 //10개의 엔트리씩 한 페이지에 넣을때 필요한 전체 페이지 수
         	 int total_pages = (search_count + fixpage - 1) / fixpage;
		 //한 페이지의 엔트리의 시작과 끝 인덱스
		 int start = page * fixpage;
                 int end = start + fixpage;
		 if (end > search_count)
			 end = search_count;
		 //현재창을 지우고 찾은 엔트리 이름 리스트를 출력함 
		 werase(win);
                 box(win, 0, 0);
                 mvwprintw(win, 0, 2, "Delete List Page %d/%d ", page + 1, total_pages);
		 //방향키로 움직이는 찾은 이름 목록을 출력함
                 for (int i = start; i < end; ++i) {
			 if (i == start + highlight)
				 wattron(win, A_REVERSE);
                         mvwprintw(win, i - start + 2, 2, "%-s", searchs[i].name);
                         if (i == start + highlight)
				 wattroff(win, A_REVERSE);
        		}
                 mvwprintw(win, 12, 2, "[←] Prev  [→] Next  [↑↓] Move");
                 mvwprintw(win, 13, 2, "[Enter] View  [q] Quit");
                 wrefresh(win); //화면 갱신

                 int ch = wgetch(win); // 누른 키를 받음

                 if (ch == 'q' || ch == 'Q') { //q를 누르면 메뉴창으로 나감
      			 werase(win); // 창을 지우고 반복문을 종료
			 box(win, 0, 0);
			 break;
                 }//방향키로 색 반전을 조절하고 left, right는 페이지도 조절
		 else if (ch == KEY_DOWN && highlight < end - start - 1)
			 highlight++;
                 else if (ch == KEY_UP && highlight > 0)
                         highlight--;
                 else if (ch == KEY_RIGHT && page < total_pages - 1) {
                         page++;
                         highlight = 0;
                 } 
                 else if (ch == KEY_LEFT && page > 0) {
                         page--;
                         highlight = 0;
                 }//엔터키로 이름을 선택하면 정보를 보여줌
		 else if (ch == '\n') {
                         int selected = start + highlight; //선택한 엔트리의 saerchs 인덱스
			 int del_idx = tel_idx[selected]; //선택한 엔트리의 tels의 인덱스
			 // 현재창을 지우고 선택한 엔트리의 정보를 보여주고 
			 // 삭제를 결정하는 창 생성
                         werase(win);
                         box(win, 0, 0);
                         mvwprintw(win, 3, 2, "Name : %s", tels[del_idx].name);
                         mvwprintw(win, 5, 2, "Phone: %s", tels[del_idx].phone);
                         mvwprintw(win, 7, 2, "Memo : %s", tels[del_idx].memo);
                         mvwprintw(win, 12, 2, "Press 'q' to return or 'd' to delete");
                         wrefresh(win);
                         
			 while(1) {
				 ch = getch();
				 //q를 누르면 찾은 리스트 창으로 돌아감
                		 if (ch == 'q'|| ch == 'Q')
					 break;
				 //d를 누르면 tels 배열에서 삭제
                		 if (ch == 'd'|| ch == 'D') {
					 for (int j = del_idx; j < tel_count - 1; ++j){
						 tels[j] = tels[j + 1];
				 	}
					tel_count--;
					//삭제된 파일로 재검색
					search_count = 0;
					for (int i = 0; i < tel_count; ++i) {
    						if (strstr(tels[i].name, keyword)) {
        						searchs[search_count] = tels[i];
        						tel_idx[search_count] = i;
        						search_count++;
    						}
					}
                    		 	datasave();//갱신된 전화번호부로 data.txt파일을 수정
                    		 	mvwprintw(win, 10, 2, "delete successfully!");
                    		 	wrefresh(win);
                    		 	ch = getch();
                                 	//q를 누르면 찾은 리스트 창으로 돌아감
                                 	if (ch == 'q'|| ch == 'Q')
						break;
				 }
			}
		 }

	 }
	return;
}
