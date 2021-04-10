#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"cmatrix.h"

int main(){
	WINDOW *win = initscr();
	noecho();
	curs_set(FALSE);

	init_v_strings(win);
	init_taken();

	for(int i = 0; i < MAX_CHRS_DIS; ++i){
		generate_rand_v_string();
	}

	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	while(1){
		clear();
		fall_v_strings();
		print_v_strings();
		refresh();

		usleep(150000);
	}

	free_taken();
	endwin();
}
