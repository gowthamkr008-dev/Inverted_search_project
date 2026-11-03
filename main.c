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
  
  while(1)
  {
    
    printf("--------Menu--------\n");
    printf("1.Create Database\n2.Display Dadabase\n3.Search Database\n4.save database\n5.Updata database\n6.Delete Database\n7.Exit\n");
    printf("--------------------\n");
    printf("Enter your choice : ");
    
    scanf("%d",&choice);
    while((ch = getc(stdin) != '\n') &&  ch != EOF );
    
    switch (choice)
    {
      case 1:
      {
        if(create_database(&head,arr) == FAILURE)
        {
          return FAILURE;
        }else
        {
          puts("Database created");
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
        char filename[20];
        printf("Enter a backup file name to update : ");
        scanf("%19s",filename);
        while((ch = getc(stdin) != '\n') &&  ch != EOF );
        if(file_validation(filename) == SUCCESS )
        {
          printf("Start update database \n");
          if( updata_database(arr,filename) == FAILURE)
          {
            return FAILURE;
          }
        }else
        {
          printf("Invalid file\n");
        }
        break;
      }
      case 6:
      {
        f_list *temp = NULL;
        free_memory(arr,&temp);
        break;
      }

      case 7:
      free_memory(arr,&head);  
      return 0;
      
      default:
      printf("INvalid choice\n");
      break;
    }
    
    choice = 0;
    printf("\n\n");
  }

}
 

static status file_validation(char *f_name)
{
  printf("FIle name is %s\n",f_name);
  
  char *ext = strrchr(f_name,'.');
  
  if(ext == NULL)
  {
    return FAILURE;
  }else if(strcmp(ext,".txt")== 0 )
  {
    FILE *fp = fopen(f_name ,"r");
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
 






