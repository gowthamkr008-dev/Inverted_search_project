#include"ISP.h"
 int status_of_input;
int main(int argc,char *argv[])
{
  f_list * head = NULL;
  ht_arr arr[27];
  int i;
  f_list * update_db_file = NULL;
  



  for(i = 0;i < 27 ;i++)
    arr[i].mn_link = NULL;

  


  if(cla_validation(argc,argv,&head,&update_db_file) == FAILURE)
  {
    printf("Cla validation failed\n");
    return FAILURE;
  }


  if(status_of_input == 0){
    printf("all file no ackup file \n");
    printf("Display Menu\n1.Create Database\n2.Display Dadabase\n3.Search Database\n4.save database\n5.Updata database\n7.Exit\nEnter a choice : ");
  }else{
    printf("update database file present\n");
  }
  
  // printf("\n");
  int choice;
  while(1){

    scanf("%d",&choice);
    __fpurge(stdout);
    switch (choice)
    {
    case 1:
     if(create_database(&head,arr) == FAILURE)
  {
    return FAILURE;
  }else{
    puts("Database created");
  }
  break;

  case 2:
    display(arr);
  break;
  
  case 3:
    {
      char search_data[50];
      scanf("%49s",search_data);
      search_database(arr,search_data);
      break;
    }
    
  case 7:
    return 0;
    default:
      break;
    }
  }
 




  







}
