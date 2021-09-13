#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "greasy.h"

FILE *DEBUG_FILE_PTR;

static int MUSIC_FLAG;

void get_proc_opt(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i) {
		if (*argv[i] == '-') {
			
			char *str = argv[i] + 1;
			while (*str != '\0') {
				switch (*str++) {
					case 'm': MUSIC_FLAG = 1;	break;		// 开启背景音乐
					default:					break;
				}
			}
		}
	}
}

void init_src(void)
{
	initscr();							// 它返回一个指向stdscr结构的指针
	signal(SIGINT, SIG_IGN);			// 忽略ctrl+c信号
	noecho();							// 设置非回显模式
	curs_set(0);						// 将把光标置为不可见
	nodelay(stdscr, TRUE);				// 终端将被设置为非阻塞模式
	leaveok(stdscr, TRUE);				// 不使用光标，节省光标移动所需要的时间
	scrollok(stdscr, FALSE);			// 即使新输入字符，光标也保留在当前位置
}

void deinit_src(void)
{
	mvcur(0, COLS - 1, LINES - 1, 0);	// 将物理光标移动到指定的行和列
	endwin();							// 释放stdscr结构
}

FILE * open_file(int file_num)
{
	FILE *fp = NULL;
	char filename[64] = { 0 };
	sprintf(filename, "./resource/output_file_txt/%d.txt", file_num + 1);
	fp = fopen(filename, "r");

	return fp;
}

void show(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0) {			// fork err
		return;
	}
	else if (0 == pid) {	// parent
		init_src();
		draw_man();
		waitpid(0, NULL, 0);
		deinit_src();
	}
	else {					// child
		if(1 == MUSIC_FLAG)
			execlp("mpg123", "mpg123", "./resource/music.mp3", NULL);
		exit(0);
	}
}

void draw_man(void)
{
	FILE *fp = NULL;
	int x_start_pos = 0, y_start_pos = 0;
	char line_str[128] = { 0 };
	int line_counts = 0;

	// 轮询文件
	for (int file_num = 0; file_num < FILE_COUNTS; file_num++)
	{
		clear();
		fp = open_file(file_num);
		if(NULL == fp)	continue;

		calc_start_pos(&x_start_pos, &y_start_pos);

		// 轮询文件的每一行
		memset(line_str, 0, sizeof(line_str));
		for (line_counts = 0; NULL != (fgets(line_str, sizeof(line_str), fp)); line_counts++) {
			my_mvaddstr(y_start_pos + line_counts, x_start_pos, line_str);
			memset(line_str, 0, sizeof(line_str));
		}

		getch();						// 从键盘读取一个字符 阻塞
		refresh();						// 重绘屏幕
		fclose(fp);
		usleep(135000);
	}

	return;
}

void calc_start_pos(int *x, int *y)
{
	int x_pos = 0, y_pos = 0;
	if (NULL == x || NULL == y)
		return;

	if (Y_MAX >= LINES)
		y_pos = 0;
	else
		y_pos = (LINES - Y_MAX) / 2;

	if (X_MAX >= COLS)
		x_pos = 0;
	else
		x_pos = (COLS - X_MAX) / 2;

	*x = x_pos;
	*y = y_pos;
	return;
}

void my_mvaddstr(int y, int x, char *str)
{
	for (; *str != '\0'; ++str, ++x)
		if (mvaddch(y, x, *str) == ERR) //用*str填充(x,y)
			return;
	return;
}

int main(int argc, char *argv[])
{
	get_proc_opt(argc, argv);

	show();

	return 0;
}