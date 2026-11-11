/***************************************************************************************************************************************************************
Name            : K R GOWTHAM

Project Title   : Inverted Search

Description     : An inverted index is an index data structure storing a mapping from content, such as words or numbers, to its locations in a database file, 
                or in a document or a set of documents. The purpose of an inverted index is to allow fast full text searches, at a cost of increased processing
                when a document is added to the database. The inverted file may be the database file itself, rather than its index. It is the most popular data
                structure used in document retrieval systems, used on a large scale for example in search engines. The purpose of this project is to implement 
                the inverted search using Hash Algorithms.

Input           : ./a.out <file names extension of the txt format>


Operation       : Create a database 
                  Display database 
                  Search database 
                  Save database 
                  Update database
                  Delete database

Output          : SUCCESS 
                  FAILURE
****************************************************************************************************************************************************************/


#include"ISP.h"
static status file_validation(char *f_name); 

int main(int argc,char *argv[])
{
  
  f_list * head = NULL;                               /*to save the file name */
  ht_arr arr[27];                                     /*to store the words inside the file */
  int i;
  char ch;
  
  
  for(i = 0;i < 27 ;i++)                                /*hashtable has using the with linked list to initialize the zero */
    arr[i].mn_link = NULL;
    
    
  if(cla_validation(argc,argv,&head) == FAILURE)         /* check the user give proper input or not throw the comman line argument  */
  {
    printf("CLA Validation Failed \n");
    printf("./a.out <file name with extension in \".txt\"> \n");
    goto error;
  }
  
  int db_choice = 0, choice, creat_db = 0 , up_db = 0;

  while(1)                                                          /* do the operation untile user press exit number */
  {
    printf("--------Menu-----------\n");
    printf("1.Create Database\n2.Display Dadabase\n3.Search Database\n4.save database\n5.Update database\n6.Exit\n");
    printf("-----------------------\n");
    printf("Enter your choice : ");
    
    scanf("%d",&choice);                                               /* choose the choose what to do the search */
    while((ch = getc(stdin) != '\n') &&  ch != EOF );                 /*clear the input buffer after scanf read  */
    printf("-----------------------\n");
    switch (choice)
    {
      case 1:                                                            /* create a database */
      {
          if(up_db == 1 && head  != NULL)                                /* before creating the database user update dabase check the file name is already update or not */
          {
            if(check_file_already_update(arr,&head) == FAILURE)         /*use this function file is already in the database */
            {
               goto error;
            }
            
            if(head != NULL)                                            /* after checking the file head is null it means all files already updated  */
            {
              creat_db = 0;
            }else
            {
              creat_db = 2;
            }
          }
          
          if(creat_db == 0)                                            /*only one time will be created a database */
          {
            creat_db = 1;
            if(create_database(&head,arr) == FAILURE)                    /* create a database use the createdatabase fuctions */
            {
               goto error;
            }else if(creat_db == 2)                                      /*create database is already created to comes here */
            {
              printf("DATABASE ALREADY CREATED\n");
            }
            else
            {
              printf("\nDATABASE CREATED SUCCESFULLY\n");
            }
          }else                                                          /* when user first time press 1 it create a database then user press 1 it show the database is already created */
          {
            printf("ERROR : DATABASE ALEADY CREATED\n");
          }
          break;
        }
      
      case 2:                                                             /* use to display the all file data file name word count file count */
          display(arr);
          break;
      
      case 3:                                                              /* search the data */
      {
          char search_data[50];
          printf("Enter a word You need to Search : ");
          scanf("%49s",search_data);
          while((ch = getc(stdin) != '\n') &&  ch != EOF );
          search_database(arr,search_data);
          break;
      }
      
      case 4:                                                              /* save the database to the txt file */
      {
          char filename[20];
          printf("Enter a file name to save a database :");
          scanf("%19s",filename);
          while((ch = getc(stdin) != '\n') &&  ch != EOF );
          printf("\n");
          char *ext = strrchr(filename,'.');                                /* check the user give the valid file or not */
          if(ext == NULL)
          {
            printf("file must be in .txt \n");
          }else if(strcmp(ext,".txt") == 0 )
          {
            if(save_database(arr,filename) == FAILURE)
            {
               goto error;
            }else
            {
              printf("DATABASE SAVED SUCCESFULLY\n");
            }
          }
          break;
      }
      
      case 5:                                                          /* update the file before create the save ed file */
      {
         if(up_db == 0)
         {
            char filename[20];
            char cho;
            printf("Enter a backup file name to update : ");
            scanf("%19s",filename);
            while((ch = getc(stdin) != '\n') &&  ch != EOF );
            if(file_validation(filename) == SUCCESS )                   /* check the file validation user give the proper file */
            {
                int status_file; 
                if( (status_file = updata_database(arr,filename)) == FAILURE)           /* update the data base file to the database */
                {
                  goto error;
                }else if(status_file == SUCCESS) {
                  up_db = 1;
                  printf("DATABASE UPDATE SUCCESFULLY\n");
                }
              }else
              {
                printf("Invalid file\n");
              }
            }else
            {
              printf("UPDATE DATABASE ALREADY DANE!\n");
            }
            break;
          }
      case 6:                                                          /* exit the program */
          free_memory(arr,&head);  
          return 0;
      
      default:
          printf("Invalid choice\n");
          break;
    }
    
    choice = 0;                                                     /* user give the other than the numbers it take the older value to do the operation */
    printf("\n");
  }



error:
free_memory(arr,&head);
return FAILURE;

}
 

static status file_validation(char *fname)                             /* file validation */
{
  char *ext = strrchr(fname,'.');                                     /* seprate the file name to .txt */
  
  if(ext == NULL)                                                     /* inbuit return null it means file name not contain any .txt */
  {
    return FAILURE;
  }else if(strcmp(ext,".txt")== 0 )                                   /* check after . it contain only txt or it contain otherthan .txt example .txtdss*/
  {
    FILE *fp = fopen(fname ,"r");                                      /* open the file in read mode */
    if(fp == NULL)
    {
      return FAILURE;
    }
    char ch = fgetc(fp);                                               /* get the first character of the file*/
    
    if(ch == '#')                                                      /* the first character is # it means it is backup file and check the last char file */
    {
      ch = '0';
      fseek(fp,-2,SEEK_END);                                          /*last character newline move to last befors character */
      ch = fgetc(fp);                                                 /*get the character */
      
      if(ch == '#')                                                   /*that character is # it is the backup file */
      {
        fclose(fp);                                                   /*close the file */
        return SUCCESS;
      }
    }
    return FAILURE;
  }
}
 






