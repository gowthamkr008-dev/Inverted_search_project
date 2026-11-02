#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <ctype.h>
  #include <stdio_ext.h>
 
typedef struct f_name{
  char * fname;
  struct f_name * link;
}f_list;

typedef struct sub_node{
  char *fname ;
  int w_count;
  struct sub_node * sn_link;
}sub_node;


typedef struct main_node{
  char *word;
  int f_cout;
  struct sub_node * sn_link;
  struct main_node * mn_link;
}main_node;


typedef struct ht_arr{
  int index;
  struct main_node *mn_link;
}ht_arr;

typedef enum status{
  FAILURE =-1,
  SUCCESS = 1,
  UPDATE_DB
}status;

/*function declerations*/
status cla_validation(int arg,char *argv[],f_list **);
status insert_first(f_list **,char * data);
status create_database(f_list **head,ht_arr arr[27]);
status save_database(ht_arr arr[27],char *filename);
status updata_database(ht_arr arr[27],char *filename);


void free_memory(ht_arr arr[27],f_list ** head);
void print_list(f_list * fname);
void display(ht_arr arr[27]); 
void search_database(ht_arr arr[27],char *word); 
