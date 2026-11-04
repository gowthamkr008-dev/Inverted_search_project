#include "ISP.h"
static status delete_node(f_list **head,char *fname){
 if( (*head) == NULL){
        return FAILURE;
    }
    if( strcmp((*head)->fname,fname )== 0){
        f_list *temp = (*head)->link;
        free(*head);
        *head = temp;
        return SUCCESS;
    }
    f_list *temp = (*head);
    while(temp->link != NULL){
        if( strcmp(temp->link ->fname,fname ) == 0){
           f_list * stemp = temp->link;
           temp->link = temp->link->link;
           free(stemp);
           return SUCCESS;
        }
        printf("\n");
        temp = temp->link;
      }
}




status check_file_already_update(ht_arr arr[27],f_list **head)
{

int i,file_del = 0 ;
f_list *temp = *head;
   for (i = 0 ; i < 27;i++)
  {
    if(arr[i].mn_link != NULL)
    {
      main_node * mn_temp = arr[i].mn_link;
      while(mn_temp != NULL)
      {
        sub_node *sn_temp = mn_temp->sn_link;
        
        while(sn_temp != NULL){
          temp = *head;
          while(temp != NULL){
            if( strcmp(sn_temp->fname,temp->fname) == 0 ){
              printf("%s Already Exist\n",temp->fname);
              if(delete_node(head,temp->fname) == SUCCESS ){
              file_del = 1;
              break;
            }
          }
          temp =temp->link;
        }
         
          sn_temp = sn_temp->sn_link;
        }
        mn_temp = mn_temp->mn_link;
      }
    }
  }

  return SUCCESS;
}



/*

check the filename if equal the update is already done 

*/