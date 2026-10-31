#include"ISP.h"
/*

typedef struct sub_node{
  char *fname ;
  int w_count;
  struct sub_node * link;
}sub_node;


typedef struct main_node{
  char *word;
  int f_cout;
  struct sub_node * link;
  struct main_node * link;
}main_node;


typedef struct ht_arr{
  int index;
  struct main_node *link;
}ht_arr;
   */



int main(int argc,char *argv[]){

  f_list * head = NULL;
  ht_arr arr[27];
  
  for(int i = 0;i < 27 ;i++){
    arr[i].mn_link = NULL;
  }



  if(cla_validation(argc,argv,&head) == FAILURE){
    printf("Cla validation failed\n");
    return FAILURE;
  }else{
    puts("Done\n\n");
  }

  if(create_database(&head,arr) == FAILURE){
    return FAILURE;
  }


  







}
