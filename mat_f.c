#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"cmatrix.h"

#define random_int(MIN,MAX) (rand()%(MAX-MIN+1)+MIN)

static v_string *v_strings[MAX_CHRS];
static v_string *v_string_ptr[MAX_CHRS];
static char *taken;

static int MAX_X = 80;
static int MAX_Y = 40;

void init_taken(){
	taken = (char *) malloc(sizeof(char) * MAX_X);
}

void free_taken(){
	free(taken);
	for(int i = 0; i < MAX_STR; ++i){
		if(v_string_ptr[i] != NULL){
			free(v_string_ptr[i]);
		}
	}
}

void init_v_strings(WINDOW *win){
	for(int i = 0; i < MAX_CHRS; ++i){
		v_strings[i] = NULL;
		v_string_ptr[i] = (v_string *) malloc(sizeof(v_string)*MAX_CHRS);
	}
	getmaxyx(win, MAX_Y, MAX_X);
}

void random_num_str(char *str, int n){
	char *i;
	if(n > MAX_STR) return;
	for(i = str; i < (str + n); ++i){
		*i = rand()%('9'-'0'+1) + '0';
	}	
	*++i = '\0';
}

v_string *generate_rand_v_string(){
	int x, y, len;
	v_string **i;

	while((x = random_int(0, MAX_X))>=0 && *(taken+x) != 0) ;  /* generate random row that is not taken */
	if(*(taken+x) == 1){
		x = random_int(0, MAX_X); /* if every row is taken then generate random one */
	}

	*(taken+x) = 1; /* mark chosen row as taken */
	
	len = random_int(MIN_STR, MAX_STR-1);
	y = -random_int(len, MAX_STR);
	v_string temp = {.x=x, .y=y, .passed=0};
	random_num_str(temp.string, len);
 	/* create a temporary v_string */
	
	for(i = v_strings; *i != NULL; ++i) ; /* check for an empty slot in v_strings */
	if(*i!=NULL){
		return NULL;	 /* if the is no empty slot return NULL */
	} 
	*i = v_string_ptr[i-v_strings]; /* make *i point to the corresponding heap-allocated pointer in v_string_ptr */
	**i = temp;
	
	return *i;
}

void print_v_strings(){
	for(int i = 0; i<MAX_CHRS; ++i){
		if(v_strings[i]!=NULL){
			attron(COLOR_PAIR(1));
			for(int j = 0; v_strings[i]->string[j] != '\0' && v_strings[i]->y <= MAX_Y; ++j){
				mvaddch(v_strings[i]->y+j, v_strings[i]->x, v_strings[i]->string[j]);
			}
			attroff(COLOR_PAIR(1));
		}
	}
}

void fall_v_strings(){
	for(int i = 0; i<MAX_CHRS; ++i){
		if(v_strings[i]==NULL) continue; 
		v_strings[i]->y+=1; /* fall */
		if(v_strings[i]->passed==0 && ((int)(v_strings[i]->y+strlen(v_strings[i]->string))>MAX_Y)){ /* checks whether 
						the bottom of the string has reached the bottom of the window */
			*(taken+v_strings[i]->x) = 0; /* unmarks v_string as taken */
			v_strings[i]->passed = 1;
			generate_rand_v_string();
		}
		if(v_strings[i]->passed==1 && v_strings[i]->y>MAX_Y){
			v_strings[i]=NULL; /* sets v_strings[i] to null if the top of the string has passed the bottom */
		}
	}
}
