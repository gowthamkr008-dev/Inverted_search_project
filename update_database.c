#include "ISP.h"


status updata_database(ht_arr arr[27],char *filename)
{
  int i; 
  printf("File name %s\n",filename);
  for (i = 0; i < 27 ;i++)
  {
    if(arr[i].mn_link != NULL)
    {
      printf("Your Database should be Empty, but it's not.\n");
      return SUCCESS;
    }
  }
  
  FILE *fp = fopen(filename,"r");
  if(fp == NULL)
  {
    return FAILURE;
  }

  char ch;
  int count = 0;
  char buffer[2024];
  char data[100];
  char * str;
  while( fscanf(fp,"%[^\n]",buffer) == 1){
    str = strtok(buffer+1 , ";");
    // printf("%s\n",str);

    int ind = atoi(str);
    printf("%d ",ind);

    str = strtok(NULL,";");
    printf("%s\n",str);
   char *f = strtok(NULL,";");
    int count =  atoi(f);

    if(insert_last_main_node(&arr[ind].mn_link,str,count)== FAILURE){
      return FAILURE;
    }

   
    for(int i = 0; i < count;i++){
    main_node *mn_temp = arr[ind].mn_link;
    int equal = 0;

    char *f_name = strtok(NULL,";");
    printf("%s %s\n",str,f_name);
    while(mn_temp != NULL){
      if(strcasecmp(mn_temp->word,str) == 0){
        equal = 1;
        break;
      }
      mn_temp = mn_temp->mn_link;
    }
    if(equal == 1){
      if(insert_last_sub_node(&mn_temp->sn_link,f_name)== FAILURE ){
        return FAILURE;
      }
    }
    char *w = strtok(NULL,";");
    int wcount = atoi(w) ;
    mn_temp->sn_link->w_count = wcount;

  }

    


    fgetc(fp);
  }
  return SUCCESS;
}



/*
  // printf("%s\n",buffer);
    str = strtok( (buffer+1),";" );
    int ind = atoi(str);
    printf("%d\n",ind);
    str = strtok(NULL,";");
    printf("%s\n",str);
    // main_node *mn_temp = arr[ind].mn_link;
    
    if(insert_last_main_node(&arr[ind].mn_link,str)== FAILURE ){
      return FAILURE;
    }
    str = strtok(NULL,";");
    char * tempword = str;
    // printf("seprate count %s",str);
    int f_count = atoi(str);
    arr[ind].mn_link->f_cout = f_count;

    for(int i = 0;i < f_count;i++ ){
      str = strtok(NULL,";");
      main_node *temp = arr[ind].mn_link;
      sub_node *sn_temp = arr[ind].mn_link->sn_link;
      while(temp != NULL){
        if(strcasecmp(temp->word,tempword)== 0){
          sn_temp = sn_temp->sn_link;
        }
        temp = temp->mn_link;
      }
     
      if(insert_last_sub_node(&arr[ind].mn_link->sn_link,str) == FAILURE){
        return FAILURE;
      }
      str = strtok(NULL,";");
      int w_count = atoi(str);
      arr[ind].mn_link->sn_link->w_count = w_count;

    }

    fgetc(fp);



*/