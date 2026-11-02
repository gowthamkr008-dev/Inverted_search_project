#include "ISP.h"


void display(ht_arr arr[27])
{
  main_node *temp;
  
  int gap =0,print =0,j =1,i;

  printf("%-5s  %-6s %-11s %-10s %-10s \n","Index","word" ,"file count","file name","word count" );
  
  for (i = 0 ; i < 27;i++)
  {
    if(arr[i].mn_link != NULL)
    {
      main_node * mn_temp = arr[i].mn_link;
      while(mn_temp != NULL)
      {
        print =0;
        gap = 15;
        printf("%-5d  %-8s %2d ",i,mn_temp->word,mn_temp->f_cout);
        sub_node *sn_temp = mn_temp->sn_link;
        
        while(sn_temp != NULL){
          if(print == 1){
            gap = 34;
          }
          printf(" %*s %5d\n",gap,sn_temp->fname,sn_temp->w_count);
          print =1;
          sn_temp = sn_temp->sn_link;
        }
        printf("\n");
        mn_temp = mn_temp->mn_link;
      }
    }
  }
}


