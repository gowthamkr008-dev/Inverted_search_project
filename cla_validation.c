#include "ISP.h"

status check_duplicate_in_file( f_list * head, char * fname)
{
  
  if(head == NULL)
  {
    return SUCCESS;
  }
  
  while(head != NULL)
  {
    
    if(strcmp(head->fname, fname) == 0)
    {
      return FAILURE;
    }
    head = head->link;
  }
  return SUCCESS;
}


status insert_first_for_database(f_list ** head, char * name)
{
  
  f_list * new =  malloc(sizeof(f_list));
  
  if(new == NULL)
  {
    return FAILURE;
  }
  
  new->fname = name;
  new->link  = *head;
  
  *head = new;
  return SUCCESS;

}


status cla_validation(int argv,char *argc[],f_list **head )
{
  if( (argv <= 1) )
  {
    return FAILURE;
  }
  
  int i,valid = 0;
  
  for(i = 1;i < argv; i++)
  {
    char *ext = strrchr(argc[i],'.');
    
    if(ext == NULL)
    {
      valid = 0;
      printf("Invalid file extension %s\n",argc[i]);
    }else
    {
      valid = 1;
    }
    
    if(valid == 1)
    {
      
      if(strcmp(ext,".txt") == 0)
      {
        valid = 1;
      }else
      {
        printf("Invalid file extension %s\n",argc[i]);
        valid = 0;
      }
    }
    
    FILE *fp;
    
    int file_open = 0;
    
    if(valid == 1)
    {
      fp = fopen(argc[i],"r");
      if(fp == NULL){
        printf("File dosen't open %s\n",argc[i]);
        valid = 0;
      }else
      {
        valid = 1;
        char ch = fgetc(fp);
        if(ch == '#')
        {
          fseek(fp,-1,SEEK_END);
          ch = fgetc(fp);
          
          if(ch == '#')
          {
              valid = 0;
              printf("backup file present ignore that ");
              fclose(fp);
            }
          }
        }
    }
    
    int pos;
    
    if(valid == 1)
    {
      
      fseek(fp,0,SEEK_END);
      pos = ftell(fp);
      valid = 1;
    }else
    {
      valid = 0;
    }
    
    if(valid == 1 && pos != 0)
    {
      valid = 1;
    }else
    {
      puts("Empty file");
      valid = 0;
    }
    
    if(valid == 1)
    {
      if(check_duplicate_in_file(*head,argc[i]) == FAILURE)
      {
        printf("Duplicate file %s\n",argc[i]);
        valid = 0;
      }else
      {
        valid = 1;
      }
    }
    
    if(valid == 1)
    {
      if(insert_first(head,argc[i])== FAILURE)
      {
        printf("Memory allocation failed\n");
        return FAILURE;
      }
    }
  }
  
  print_list(*head);
  
  if(*head == NULL)
  {
    printf("Enter valid file\n");
    return FAILURE;
  }
  
  return SUCCESS;
}

