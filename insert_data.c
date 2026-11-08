

#include "ISP.h"
status insert_last_main_node(main_node ** node,char *word ,int f_count)
{
  
  main_node  *new = malloc(sizeof(main_node));
  
  if(new == NULL)
  {
    return FAILURE;
  }
  
  new->word = malloc(sizeof(main_node));
  
  if(new->word == NULL)
  {
    return FAILURE;
  }
  
  strcpy(new->word,word );
  new->f_cout = f_count;
  new->mn_link = NULL;
  new->sn_link = NULL;
  
  if(*node == NULL)
  {
    *node = new;
    return SUCCESS;
  }
  
  main_node *temp = *node;
  
  while(temp->mn_link != NULL)
  {
    temp = temp->mn_link;
  }
  temp->mn_link = new;
  return SUCCESS;
}

status insert_last_sub_node(sub_node ** node,char*fname)
{
  sub_node  *new = malloc(sizeof(sub_node));
  
  if(new == NULL)
  {
    return FAILURE;
  }
  
  new->fname = malloc(sizeof(main_node));
  
  if(new->fname == NULL)
  {
    return FAILURE;
  }
  
  strcpy(new->fname,fname );
  new->w_count = 1;
  new->sn_link = NULL;
  if(*node == NULL)
  {
    *node = new;
    return SUCCESS;
  }
  
  sub_node *temp = *node;
  
  while(temp->sn_link != NULL)
  {
    temp = temp->sn_link;
  }
  
  temp->sn_link = new;
  return SUCCESS;
}



status insert_first(f_list ** head, char * name)
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
