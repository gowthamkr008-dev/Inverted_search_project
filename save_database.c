/**********************************************************************************************************************************************************
Title     : Save the database

Operation : Save the database to the txt file for the feature use no everytime to create a database ittake time once create database before going out to save 
            the program to the txt file

Input     : hashtable ,filename

output    : SUCCESS   when return success it means database saves succesfully
            FAILURE   file doesn't open return the failure



***********************************************************************************************************************************************************/

#include "ISP.h"
status save_database(ht_arr arr[27],char *filename)                                  /*save the database */
{
  
  FILE *fp = fopen(filename,"w");                                                    /* open the file mode in the write mode */
  
  if(fp == NULL)                                                                      
  {
    
    perror("ERROR ");
    return FAILURE;
  }
  
  main_node *temp;
  
  for(int i = 0; i < 27;i++ )                                                       /*loop run in 27 times */
  {
    
    temp = arr[i].mn_link;                                                          /*take a temporary pointer for traverse */
    
    while(temp != NULL)                                                            /*loop run temp pointer reaches to null*/
    {
      
      fprintf(fp, "#%d;%s;%d;",i,temp->word,temp->f_cout);                         /*use print function to write a data to the file */
      sub_node *sn_temp = temp->sn_link;                                           /*take a subnode temporary variable to write a file name */
      while(sn_temp != NULL)
      {
        fprintf(fp,"%s;%d;",sn_temp->fname,sn_temp->w_count);                        /*use print function to write a data to the file */
        sn_temp =sn_temp->sn_link;
      }
      
      fprintf(fp,"#\n");
      temp = temp->mn_link;                                                         /*moves to next pointer */
    }
  }
  fclose(fp);                                                                      /*close the file */
  return SUCCESS;

}