/*******************************************************************************************************************************************************************************
Title     : Search Database 

Operation : The given input is take a first character in the given word as per the number find the word and display the content present in the database 

Input     : hash table ,word

Output    : Display the output in given the database 

***********************************************************************************************************************************************************************************/
#include"ISP.h"
void search_database(ht_arr arr[27],char *word)
{
  printf("\n");
  char ch = tolower(word[0]) - 'a';                                                /* in the given word take first character convert to lower the subtract the small a then get the index of the character  */
  int ind = ch;                                                                    /*the character assign to the integer */
  if(ind >= 0 && ind <= 25)                                                        /*if num is 0 to 25 asign the index there is a A to Z  */
  { 
    ind = ch;
  }else                                                                           /*other than the alphabet asign to the 26 index*/                                              
  {
    ind = 26;
  }
  
  int done = 0,j = 1;
  
  main_node * temp = arr[ind].mn_link;                                          /* take the temporary pointer for traverse */
  int print = 0,gap = 15;
   
  while(temp != NULL)                                                          /* Loop will run until pointer reachus to the NULL pointer  */
  {
    
    gap = 15;
    print = 0;
    
    if(strcasestr(temp->word,word))                                          /* compare the given word strig and word present in database  */
    {
      if(done == 0)                                                           /* done means print only one times */
      {
        printf("%-5s %-6s %-11s %-10s %-10s \n\n","Index","word" ,"file count","file name","word count" );
      }
      done = 1;
      
      printf("%-5d %-8s %2d ",j++,temp->word,temp->f_cout);                           /*print the word and file count */
      
      sub_node *sn_temp = temp->sn_link;                                     /*take a temporary pointer for tarvarsel */
      
      while(sn_temp != NULL)
      {
        if(print == 1)
        {
          gap = 27;
        }
        printf("%*s %5d\n",gap,sn_temp->fname,sn_temp->w_count);             /*printf th file name and word count */
        sn_temp = sn_temp->sn_link;                                         /*pointer moves to the next position */
        print = 1;
      }
    }
    printf("\n");
    temp = temp->mn_link;                                                   /*pointer moves to next position */                                           
  }
  
  if(done == 0)                                                             /* done is a zero consider the word not present in the database */
  {
    printf("Word \"%s\" not present in the database\n",word);
  }
}