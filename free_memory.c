#include "ISP.h"

void free_memory(ht_arr arr[27],f_list ** head)
{
  
  for (int i = 0; i < 27; i++)
  {
    main_node *mn_temp = arr[i].mn_link;
    
    while (mn_temp != NULL)
    {
      main_node *backup_mn = mn_temp;
      sub_node *sn_temp = mn_temp->sn_link;
      while (sn_temp != NULL)
      {
        sub_node *backup_sn = sn_temp;
        sn_temp = sn_temp->sn_link;   
        free(backup_sn->fname);
        free(backup_sn);
      }
      
      mn_temp = mn_temp->mn_link;        
      free(backup_mn->word);
      free(backup_mn);
    }
    arr[i].mn_link = NULL;               
    }
    
    f_list *temp = *head;
    
    while(temp  != NULL)
    {
      f_list *backup = temp;
      temp = temp->link;
      free(backup);
    }
    
    *head = NULL;
  }