/***************************************************************************************************************************************************************
Title     : Update Database 

Operation : user given file present in the database before saved after exit the program database deleted again it not possible to reuse so save database there 
            file use the file again it reusable file 

Input    : hashtable ,backup filename

***************************************************************************************************************************************************************/
#include "ISP.h"
status updata_database(ht_arr arr[27],char *filename)
{
  
  int i;
  
  for (i = 0; i < 27 ;i++)                                                  /* chek the database is empty or not empty  */
  {
    if(arr[i].mn_link != NULL)
    {
      printf("Your Database should be Empty, but it's not.\n");
      return  INVALID;
    }
  }
  
  FILE *fp = fopen(filename,"r");                                            /*open the given file in read mode */
  
  if(fp == NULL)
  {
    return FAILURE;
  }
  
  char ch;
  int count = 0,equal,wcount,ind;
  char buffer[2024];
  char data[100];
  char * str,* f,*f_name,*w;
  main_node *mn_temp;
  
  
  while( fscanf(fp,"%[^\n]",buffer) == 1)                                   /*loop run until EOF file appear */
  {                                                                         /* read from the file use scanf for oneline */
    
    str = strtok(buffer+1 , ";");                                          /*seprate the index */
    
    ind = atoi(str);                                                       /*convert string to the integer store in the index variable  */
    
    str = strtok(NULL,";");                                                /*seprate the word in the file store into the str*/
    f = strtok(NULL,";");                                                  /* seprate the file count */
    count =  atoi(f);                                                      /*convert the string to integer */
    
    if( insert_last_main_node(&arr[ind].mn_link,str,count)== FAILURE)     /* insert to the database string and count */
    {
      return FAILURE;
    }
    
    for(i = 0; i < count;i++)                                             /*asper the file count loop run */
    {
      
      mn_temp = arr[ind].mn_link;                                         /*take a temporary pointer for traverse */
      equal = 0;
      f_name = strtok(NULL,";");                                          /*seprate the filename */
      
      while(mn_temp != NULL)                                             
      {
        if(strcasecmp(mn_temp->word,str) == 0)                            /*check the word count is already present or not */
        {
          equal = 1;
          break;
        }
        mn_temp = mn_temp->mn_link;                                      /*traversel to the next pointer */
      }
      
      if(equal == 1)
      {
        if(insert_last_sub_node(&mn_temp->sn_link,f_name)== FAILURE )   /* insert the filename to the subnode */
        {
          return FAILURE;
        }
      }
      
      w = strtok(NULL,";");                                            /*extract the word count */
      wcount = atoi(w) ;                                               /* convert the string to integer */
      mn_temp->sn_link->w_count = wcount;                              /*insert to the word count */
    }
    
    fgetc(fp);                                                          /*take a new line character */
  }
  
  fclose(fp);                                                           /* close the file */
  return SUCCESS;
}


