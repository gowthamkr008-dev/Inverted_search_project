/***************************************************************************************************************************************************************
Title     : Create database 

Operation : Given file to create and save to hash table in the to asve the word,file count ,file name ,word count in the present file

Input     : file list ,hash table

Output    : SUCCESS   when every process is done 
            FAILURE   refurn the failure file doesnot open or any allocation failure 



***************************************************************************************************************************************************************/


#include "ISP.h"
status create_database(f_list **head,ht_arr arr[27])
{
  if(*head == NULL)                                                              /* when user give some file it already updated that time user press the create database if file already created delete the node then delete a database then create a database if null it means file name will be deleted in the node  */
  {
    printf("FILE LIST IS EMPTY\n");
    return FAILURE;
  }

  printf("\n");
  f_list * temp = *head;
  int i = 0;
  
  while(temp != NULL)                                                        /*do untile file list every file need to rear*/
  {
    FILE * fp  = fopen(temp->fname,"r");                                     /* open the file in read mode */
    
    if(fp == NULL)                                                          /* file doesnot open return null*/
    {
      return FAILURE;
    }
    
    char buffer[1024];
    int ind;
    int updone = 0;
    
    while(fscanf(fp, "%1023s",buffer) == 1)                                 /*read the string from the file untile the space appear */
    {
      updone = 0;
      char ch = tolower(buffer[0]) - 'a';                                   /* take first character from the string to store word in the index*/
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
          if(insert_last_sub_node(&arr[ind].mn_link->sn_link,temp->fname)== FAILURE )  /* insert the file name and word count */
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
    fclose(fp);                                                                /*close the file */
    printf("SUCCESS : Created file %s\n",temp->fname);
    temp = temp->link;                                                          /* temp is file name moves to next file */
  }

  return SUCCESS;
}

