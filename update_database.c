#include "ISP.h"


status updata_database(ht_arr arr[27],char *filename)
{
  
  int i;
  
  printf("File name %s\n",filename);
  
  for (i = 0; i < 27 ;i++)
  {
    if(arr[i].mn_link != NULL)
    {
      printf("Your Database should be Empty, but it's not.\n");
      return SUCCESS;
    }
  }
  
  FILE *fp = fopen(filename,"r");
  
  if(fp == NULL)
  {
    return FAILURE;
  }
  
  char ch;
  int count = 0,equal,wcount,ind;
  char buffer[2024];
  char data[100];
  char * str,* f,*f_name,*w;
  main_node *mn_temp;
  
  
  while( fscanf(fp,"%[^\n]",buffer) == 1)
  {
    
    str = strtok(buffer+1 , ";");
    
    ind = atoi(str);
    
    str = strtok(NULL,";");
    f = strtok(NULL,";");
    count =  atoi(f);
    
    if( insert_last_main_node(&arr[ind].mn_link,str,count)== FAILURE)
    {
      return FAILURE;
    }
    
    for(i = 0; i < count;i++)
    {
      
      mn_temp = arr[ind].mn_link;
      equal = 0;
      f_name = strtok(NULL,";");
      
      while(mn_temp != NULL)
      {
        if(strcasecmp(mn_temp->word,str) == 0)
        {
          equal = 1;
          break;
        }
        mn_temp = mn_temp->mn_link;
      }
      
      if(equal == 1)
      {
        if(insert_last_sub_node(&mn_temp->sn_link,f_name)== FAILURE )
        {
          return FAILURE;
        }
      }
      
      w = strtok(NULL,";");
      wcount = atoi(w) ;
      mn_temp->sn_link->w_count = wcount;
    }
    
    fgetc(fp);
  }
  
  fclose(fp);
  return SUCCESS;
}


