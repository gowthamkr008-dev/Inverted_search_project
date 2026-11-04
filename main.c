#include"ISP.h"
static status file_validation(char *f_name);

int main(int argc,char *argv[])
{
  
  f_list * head = NULL;
  ht_arr arr[27];
  int i;
  char ch;
  
  for(i = 0;i < 27 ;i++)
    arr[i].mn_link = NULL;
  
  
  if(cla_validation(argc,argv,&head) == FAILURE)
  {
    printf("Cla validation failed\n");
    return FAILURE;
  }
  
  int db_choice =0;
  
  int choice;
  
  int creat_db =0;
  int up_db = 0;
  while(1)
  {
    
    printf("--------Menu--------\n");
    printf("1.Create Database\n2.Display Dadabase\n3.Search Database\n4.save database\n5.Updata database\n6.Delete Database\n7.Exit\n");
    printf("--------------------\n");
    printf("Enter your choice : ");
    
    scanf("%d",&choice);
    while((ch = getc(stdin) != '\n') &&  ch != EOF );
    printf("\n\n");
    switch (choice)
    {
      case 1:
      {
        if(up_db == 1 && head  != NULL){
          if(check_file_already_update(arr,&head) == FAILURE){
            return FAILURE;
          }

          if(head != NULL){
            creat_db = 0;
          }else{
            creat_db = 2;

          }

        }
        if(creat_db == 0){
        creat_db = 1;
        if(create_database(&head,arr) == FAILURE)
        {
          return FAILURE;
        }else if(creat_db == 2){
          printf("DATABASE ALREADY CREATED\n");
        }
        else
        {
         printf("\n\nDATABASE CREATED SUCCESFULLY");
        }
      }else{
        printf("Error: Data base already created\n");
      }
        break;
      }
      
      case 2:
      display(arr);
      break;
      
      case 3:
      {
        char search_data[50];
        printf("Enter a data You need to Search : ");
        scanf("%49s",search_data);
        while((ch = getc(stdin) != '\n') &&  ch != EOF );
        search_database(arr,search_data);
        break;
      }
      
      case 4:
      {
        printf("save database\n");
        char filename[20];
        printf("Enter a file name to save a database :");
        scanf("%19s",filename);
        while((ch = getc(stdin) != '\n') &&  ch != EOF );
        char *ext = strrchr(filename,'.');
        if(ext == NULL)
        {
          printf("file must be in .txt \n");
        }else if(strcmp(ext,".txt") == 0 )
        {
          if(save_database(arr,filename) == FAILURE)
          {
            return FAILURE;
          }else
          {
            printf("done");
          }
        }
        break;
      }
      
      case 5:
      {
        if(up_db == 0){
        char filename[20];
        char cho;
       
          printf("Enter a backup file name to update : ");
            scanf("%19s",filename);
            while((ch = getc(stdin) != '\n') &&  ch != EOF );
        if(file_validation(filename) == SUCCESS )
        {
          if( updata_database(arr,filename) == FAILURE)
          {
            return FAILURE;
          }
           up_db = 1;
           printf("Data base updated\n");
        }else
        {
          printf("Invalid file\n");
        }
      }else{
        printf("Update database is already done\n");
      }
        break;
      }
      case 6:
      {
        f_list *temp = NULL;
        free_memory(arr,&temp);
        creat_db = 0;
        up_db = 0;
        break;
      }

      case 7:
      free_memory(arr,&head);  
      return 0;
      
      default:
      printf("Invalid choice\n");
      break;
    }
    
    choice = 0;
    printf("\n\n");
  }

}
 

static status file_validation(char *fname)
{
  printf("File name is %s\n",fname);
  
  char *ext = strrchr(fname,'.');
  
  if(ext == NULL)
  {
    return FAILURE;
  }else if(strcmp(ext,".txt")== 0 )
  {
    FILE *fp = fopen(fname ,"r");
    if(fp == NULL)
    {
      return FAILURE;
    }
    char ch = fgetc(fp);
    
    if(ch == '#')
    {
      ch = '0';
      fseek(fp,-2,SEEK_END);
      ch = fgetc(fp);
      
      if(ch == '#')
      {
        fclose(fp);
        return SUCCESS;
      }
    }
    return FAILURE;
  }
}
 






