#ifndef __GREASY_H__
#define __GREASY_H__

#define X_MAX		(82)
#define Y_MAX		(62)
#define FILE_COUNTS (111)
#define GREASY_LOG mydebug(DEBUG_FILE_PTR, "[time:%s func:%s() line:%d]:", __TIME__, __func__, __LINE__);mydebug

void get_proc_opt(int argc, char *argv[]);

void init_src(void);

void deinit_src(void);

void draw_man(void);

void my_mvaddstr(int y, int x, char *str);

FILE * open_file(int file_num);

void calc_start_pos(int *x, int *y);

void show(void);

#endif // __GREASY_H__
