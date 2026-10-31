#include "ISP.h"
extern  int status_of_input;

status check_duplicate_in_file( f_list * head,char * fname){
  if(head == NULL){
    return SUCCESS;
  }

  while(head != NULL){
    if(strcmp(head->fname,fname) == 0){
      return FAILURE;
    }
    head = head->link;
  }
  return SUCCESS;
}


status cla_validation( int argv,char * argc[],f_list ** head)
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
    
    // printf("file validation %d\n",valid);
    
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
    
    // printf("file validation %d\n",valid);
    
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
        char ch = fgetc(fp);
        printf("%c\n",ch);
        if(ch == '#'){
          fseek(fp,-1,SEEK_END);
          ch = fgetc(fp);
          printf("%c\n",ch);
          if(ch == '#'){
            status_of_input = UPDATE_DB;
          }
        }
        file_open =1;
        valid = 1;
      }
    }

    // printf("file opening %d\n",valid);
    int pos;
   if(valid == 1){
     fseek(fp,0,SEEK_END);
    pos = ftell(fp);
    valid =1;
   }else{
    valid =0;
   }
    if(valid == 1 && pos != 0){
      valid = 1;
    }else{
      puts("Empty file");
      valid =0;
    }

    if(file_open){
      fclose(fp);
    }
    // printf("file empty %d\n",valid);
      if(valid == 1){
    if(check_duplicate_in_file(*head,argc[i]) == FAILURE){
      printf("Duplicate file %s\n",argc[i]);
      valid = 0;
    }else{
      valid =1;
    }
  }

  // printf("everything valid %d\n",valid);
   if(valid == 1){
  if(insert_first(head,argc[i])== FAILURE){
    printf("Memory allocation failed\n");
    return FAILURE;
  }
}
}
print_list(*head);
  
if(*head == NULL){
  printf("Enter valid file\n");
  return FAILURE;
}

  return SUCCESS;
}

