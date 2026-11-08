/***************************************************************************************************************************************************************
Title : free memory

Input : hash table , file list

Output : delete the database which is already update or create 

***************************************************************************************************************************************************************/
#include "ISP.h"
void free_memory(ht_arr arr[27],f_list ** head)   
{
  int db_del = 0;
  for (int i = 0; i < 27; i++)                                               /* loop will run in 27 times */
  {
    main_node *mn_temp = arr[i].mn_link;                                    /* take a temporary pointer */

    while (mn_temp != NULL)                                                 /* loop will run until temp reach to NULL*/
    {
      main_node *backup_mn = mn_temp;                                       /* take a backup for a deletion */
      sub_node *sn_temp = mn_temp->sn_link;                                  /*take a temporary pointer for traverse */
      db_del = 1;
      while (sn_temp != NULL)                                                 /*loop runs until pointer reach to null*/
      {
        sub_node *backup_sn = sn_temp;                                        /*take a backup to delete the node */
        sn_temp = sn_temp->sn_link;   
        free(backup_sn->fname);                                              /*free the memory */
        free(backup_sn);
      }
      
      mn_temp = mn_temp->mn_link;                                             /*pointer moves to next node */        
      free(backup_mn->word);                                                  /*free the memory */
      free(backup_mn);
    }
    arr[i].mn_link = NULL;                                                    /*asign a linke to null*/              
    }
    
    f_list *temp = *head;                                                     /*take a temporary pointer */
    
    while(temp  != NULL)                                                    /*loop runs until the pointer reach to null*/
    {
      f_list *backup = temp;
      temp = temp->link;
      free(backup);
    }
    
    *head = NULL;
    if(db_del == 1)
    {
      printf("DATABASE DELETED SUCCESFULLY\n");
    }
  }