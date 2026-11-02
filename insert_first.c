#include"ISP.h"

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