#include "ISP.h"


status create_database(f_list **head,ht_arr arr[27])
{
  
  f_list * temp = *head;
  int i = 0;
  
  while(temp != NULL)
  {
    FILE * fp  = fopen(temp->fname,"r");
    
    if(fp == NULL)
    {
      return FAILURE;
    }
    
    char buffer[1024];
    int ind;
    int updone = 0;
    
    while(fscanf(fp, "%1023s",buffer) == 1)
    {
      updone = 0;
      char ch = tolower(buffer[0]) - 'a';
      ind = ch;
      if(ind >= 0 && ind <= 25)
      {
        ind = ch;
      }else
      {
        ind = 26;
      }
      sub_node *sn_temp;
      main_node *mn_temp;

      if(arr[ind].mn_link == NULL)
      {                                                                         /* when main node has null that time execute */
        if(insert_last_main_node(&arr[ind].mn_link,buffer,1)== FAILURE )
        {
          return FAILURE;
        }else
        {
          if(insert_last_sub_node(&arr[ind].mn_link->sn_link,temp->fname)== FAILURE )
          {
            return FAILURE;
          }else
          {
            updone = 1;
          }
        }
      }

      mn_temp = arr[ind].mn_link;
      while(mn_temp != NULL)
      {
        if(strcasecmp(mn_temp->word,buffer) == 0  && updone == 0)
        {                                                                /* word equal no need to create a mani node */
          sn_temp = mn_temp->sn_link;
          while(sn_temp != NULL){
            if(strcmp(sn_temp->fname , temp->fname)== 0 )
            {                                                            /* words and files are equal increment the word count */
              sn_temp->w_count += 1;
              updone = 1;
              break;
            }
            sn_temp= sn_temp->sn_link;
          }
          
          if(updone == 0)
          {                                                                     /* word are equal but file not present */
            if(insert_last_sub_node( &mn_temp->sn_link ,temp->fname)== FAILURE )
            {
              return FAILURE;
            }else
            {
              mn_temp->f_cout += 1;
              updone =1;
            }
          }
        }
        if(mn_temp->mn_link == NULL)
        {
          break;
        }
        mn_temp = mn_temp->mn_link;
      }

      if(updone == 0)
      {                                                                           /* word are not present insert new node */
        if(insert_last_main_node(&mn_temp->mn_link,buffer,1)== FAILURE )
        {
          return FAILURE;
        }else
        {
          if(insert_last_sub_node(&mn_temp->mn_link->sn_link,temp->fname) == FAILURE)
          {
            return FAILURE;
          }else
          {
            updone =1;
          }
        }
      }

    }
    fclose(fp);
    temp = temp->link;
  }
  return SUCCESS;
}

