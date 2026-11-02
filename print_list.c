#include "ISP.h"

void print_list(f_list *head)
{
  
  if (head == NULL)
  {
    return ;
  }
  
  int i = 1;
  
  while(head)
  {
    printf("%d %s\n",i++,head->fname);
    head= head->link;
  }
  
  printf("\n");
}