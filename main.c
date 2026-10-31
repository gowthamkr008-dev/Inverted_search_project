#include"ISP.h"
 int status_of_input;
int main(int argc,char *argv[])
{
  f_list * head = NULL;
  ht_arr arr[27];
  int i;
  



  for(i = 0;i < 27 ;i++)
    arr[i].mn_link = NULL;
    
  if(cla_validation(argc,argv,&head) == FAILURE)
  {
    printf("Cla validation failed\n");
    return FAILURE;
  }
  if(status_of_input == 0){
    printf("all file no ackup file \n");
  }else{
    printf("update database file present\n");
  }
  
  if(create_database(&head,arr) == FAILURE)
  {
    return FAILURE;
  }




  







}
