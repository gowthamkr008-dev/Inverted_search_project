/***************************************************************************************************************************************************************
Title    : Check file already update

Operation : when user call update file that time update the database then again try to create a database with the same file if give the wrong information so i use
            this function if updated database is any file present in the node it will deleted and bring the file is already present in the database

Input     : Hash table file name

Output    : SUCCESS  the every process is done retuen success
            FAILURE  when the file list is empty


***************************************************************************************************************************************************************/

#include "ISP.h"
static status delete_node(f_list **head, char *fname)
{
  if ((*head) == NULL)
  {
    return FAILURE;
  }

  if (strcmp((*head)->fname, fname) == 0)                                                    /*compare the irst node and file name */
  {

    f_list *temp = (*head)->link;                                                           /* it is equal take a backup of the next node*/
    free(*head);                                                                            /* delete the head node */
    *head = temp;                                                                           /* asign abackup ode to the head */
    return SUCCESS;
  }

  f_list *temp = (*head);                                                                    /*asign a temporary node for head*/

  while (temp->link != NULL)                                                                 /*check the node is null or not*/
  {
    if (strcmp(temp->link->fname, fname) == 0)                                               /*compare the file name is given and node filename */
    {
      f_list *stemp = temp->link;                                                           /*if equal delted the node */
      temp->link = temp->link->link;
      free(stemp);
      return SUCCESS;
    }

    temp = temp->link;                                                                      /*move to the next node for traverse */
  }
}

status check_file_already_update(ht_arr arr[27], f_list **head)                              /*check the file is already update or not */
{
  if (*head == NULL)                                                                        /* node is null  consider as the list is empty */
  {
    return FAILURE;
  }

  int i, file_del = 0;
  f_list *temp = *head;                                                                     /* asign a temporary node for traverse */

  for (i = 0; i < 27; i++)                                                                   /*check the every index of the variable */
  {
    if (arr[i].mn_link != NULL)                                                              /* the link not a null consider as some data in the node */
    {
      main_node *mn_temp = arr[i].mn_link;                                                    /*asign a temporary node  for tarverse for a main node */
      while (mn_temp != NULL)
      {
        sub_node *sn_temp = mn_temp->sn_link;                                                 /*asign a temporary node for trverse for a sub node */
        while (sn_temp != NULL)
        {
          temp = *head;                                                                       /* after traverse for next traverse reasign a head for next traverse  */
          while (temp != NULL)
          {
            if (strcmp(sn_temp->fname, temp->fname) == 0)                                     /* if sub node file name and file list file name compare is equal consider this file name is alreaady updated */
            {
              printf("%s Already Exist\n", temp->fname);
              if (delete_node(head, temp->fname) == SUCCESS)                                  /*call the function to delete the node */
              {
                file_del = 1;
                break;
              }
            }
            temp = temp->link;
          }
          sn_temp = sn_temp->sn_link;                                                                    /*move to next sub node to check the next subnode file name */
        }
        mn_temp = mn_temp->mn_link;
      }
    }
  }
  return SUCCESS;
}
