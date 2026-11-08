/***************************************************************************************************************************************************************
Title : CLA validation

Operation : in the project take a input as through the command line argument in tha command line arrgument is valid or not check here 

Input     : argument count,argument variable,list node 

Output    : SUCCESS  the user given proper argument is valid
            FAILURE  the user given improper argument is invalid or memory allocation failure
          





***************************************************************************************************************************************************************/
#include "ISP.h"
status check_duplicate_in_file( f_list * head, char * fname)                              /* check the duplicate when user give single file multiple times */
{
  
  if(head == NULL)                                                                       
  {
    return SUCCESS;
  }
  
  while(head != NULL)                                                                     /* loop will run until the head points to the NULL */
  {
    
    if(strcmp(head->fname, fname) == 0)                                                   /*compare every node and given file name */
    {
      return FAILURE;
    }
    head = head->link;                                                                     /*move to net node for comparition */
  }
  return SUCCESS;
}


status insert_first_for_database(f_list ** head, char * name)                              /*insert a data to flist for use of database */
{
  
  f_list * new =  malloc(sizeof(f_list));                                                   /*dynamically allocate the memory */
  
  if(new == NULL)
  {
    return FAILURE;
  }
  
  new->fname = name;                                                                       /*asign a name to the node */
  new->link  = *head;
  
  *head = new;
  return SUCCESS;

}


status cla_validation(int argc,char *argv[],f_list **head )
{
  if( (argc <= 1) )                                                                      /*user gives only one argument consider a invalid input */
  {
    return FAILURE;
  }
  
  int i,valid = 0;
  
  for(i = 1;i < argc; i++)                                                              /*loop will run until argument count */
  {
    char *ext = strrchr(argv[i],'.');                                                  /*extract the extension from the given argment */
    
    if(ext == NULL)                                                                    /*the strrchr is return null consider there is not a proper extension */
    {
      printf("Invalid Extension ");
      valid = 2;
    }else
    {
      valid = 1;
    }
    
    if(valid == 1)     
    {
      if(strcmp(ext,".txt") == 0)                                                    /*compare the before extracted extension after only .txt of any other character after this if there it is invalid extension*/
      {
        valid = 1;
      }else
      {
        printf("Invalid Extension ");
        valid = 2;
      }
    }
    
    FILE *fp;
    
    int file_open = 0;
    
    if(valid == 1)
    {
      fp = fopen(argv[i],"r");                                                           /* open file in the read mode */
      if(fp == NULL){                                                                    /*fopen return NULL consider there is no file in the directory */
        printf("file not present in the directory ");
        valid = 0;
      }else
      {
        valid = 1;
        char ch = fgetc(fp);                                                              /*geth the first from the file */
        if(ch == '#')
        {
          ch = '0';
          fseek(fp,-2,SEEK_END);                                                           /*move the file pointer to the last before character */
          ch = fgetc(fp);                                                                   /*get the character the character */
          
          if(ch == '#')                                                                     /*the last character is # it is a backup file no use in to create a database the file has been ignored */                                                                   
          {
              file_open = 1;
              valid = 0;
              printf("Backup file Present Ignored ");
              fclose(fp);
            }
          }
        }
    }
    
    int pos;
    
    if(valid == 1)
    {
      fseek(fp,0,SEEK_END);                                                             /*file pointer moves to the end */
      pos = ftell(fp);                                                                  /*get the position of the file */
      valid = 1;
    }else
    {
      valid = 0;
    }
    
    if(valid == 1 && pos != 0)                                                             /*the position is zero consider the fie is empty */
    {
      valid = 1;
    }else if(file_open == 0 && valid != 0)
    {
      printf("Empty file ");
      valid = 0;
    }
    
    if(valid == 1)
    {
      if(check_duplicate_in_file(*head,argv[i]) == FAILURE)                               /*check the file is already present or not if present there is no duplicate */
      {
        printf("Duplicate file ");
        valid = 0;
      }else
      {
        valid = 1;
      }
    }
    
    if(valid == 1)
    {
      if(insert_first(head,argv[i])== FAILURE)                                              /*insert the file */
      {
        printf("Memory allocation failed\n");
        return FAILURE;
      }else{
        printf("File \"%s\" validated Succesfully ",argv[i]);
      }
    }
    if(valid == 0){
      printf(" \"%s\" INVALID FILE ",argv[i]);
    }
    printf("\n");
  }
  printf("\n");
  return SUCCESS;
}

