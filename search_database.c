#include"ISP.h"

void search_database(ht_arr arr[27],char *word)
{
  char ch = tolower(word[0]) - 'a';
  int ind = ch;
  if(ind >= 0 && ind <= 25)
      {
        ind = ch;
      }else
      {
        ind = 26;
      }
      int done =0;

  main_node * temp = arr[ind].mn_link;
  int print =0,gap = 15;
  
  while(temp != NULL){
    gap = 15;
    print = 0;
    if(strcasestr(temp->word,word)){
      if(done == 0){
      printf("%-6s %-11s %-10s %-10s \n","word" ,"file count","file name","word count" );
      }
      done =1;
     
       printf("%-8s %2d ",temp->word,temp->f_cout);
       sub_node *sn_temp = temp->sn_link;
        
        while(sn_temp != NULL){
          if(print == 1){
            gap = 27;
          }
          printf("%*s %5d\n",gap,sn_temp->fname,sn_temp->w_count);
          sn_temp = sn_temp->sn_link;
          print = 1;
        }
       
      }
       temp = temp->mn_link;
  }
if(done == 0){
  printf("Word \"%s\" not present in the database\n",word);
}
}