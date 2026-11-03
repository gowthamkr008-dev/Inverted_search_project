#include "ISP.h"

status save_database(ht_arr arr[27],char *filename)
{
  
  FILE *fp = fopen(filename,"w");
  
  if(fp == NULL)
  {
    
    perror("ERROR ");
    return FAILURE;
  }
  
  main_node *temp;
  
  for(int i = 0; i < 27;i++ )
  {
    
    temp = arr[i].mn_link;
    
    while(temp != NULL)
    {
      
      fprintf(fp, "#%d;%s;%d;",i,temp->word,temp->f_cout);
      sub_node *sn_temp = temp->sn_link;
      while(sn_temp != NULL)
      {
        fprintf(fp,"%s;%d;",sn_temp->fname,sn_temp->w_count);
        sn_temp =sn_temp->sn_link;
      }
      
      fprintf(fp,"#\n");
      temp = temp->mn_link;
    }
  }
  fclose(fp);
  return SUCCESS;

}