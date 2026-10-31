#include "ISP.h"
static status insert_last_main_node(main_node ** node,char *word ){
  // main_node * temp = *node;
  // printf("insert main node %s\n",word);
   main_node  *new = malloc(sizeof(main_node));
  if(new == NULL){
    return FAILURE;
  }
   new->word = malloc(sizeof(main_node));
   if(new->word == NULL){
      return FAILURE;
    }
    strcpy(new->word,word );
    new->f_cout = 1;
    new->mn_link = NULL;
    new->sn_link = NULL;
    
        if(*node == NULL){
          *node = new;
          return SUCCESS;
        }
    main_node *temp = *node;
  while(temp->mn_link != NULL){
    temp = temp->mn_link;
  }
  temp->mn_link = new;
  return SUCCESS;
}

static status insert_last_sub_node(sub_node ** node,char*fname){
  // printf("insert subnode %s\n",fname);
    sub_node  *new = malloc(sizeof(sub_node));
  if(new == NULL){
    return FAILURE;
  }
   new->fname = malloc(sizeof(main_node));
   if(new->fname == NULL){
      return FAILURE;
    }
    strcpy(new->fname,fname );
    new->w_count = 1;
    new->sn_link = NULL;
    if(*node == NULL){
          *node = new;
          return SUCCESS;
          }
    sub_node *temp = *node;
  while(temp->sn_link != NULL){
    temp = temp->sn_link;
  }
  temp->sn_link = new;
  return SUCCESS;
}
 
  
  
static void display(ht_arr arr[27]){
  main_node *temp;
  int gap =0,print =0;
  int j =1;
  printf("%-5s  %-6s %-11s %-10s %-10s \n","Index","word" ,"file count","file name","word count" );
 for (int i = 0 ; i < 27;i++){
  if(arr[i].mn_link != NULL){
    main_node * mn_temp = arr[i].mn_link;
    while(mn_temp != NULL){
      print =0;
      gap = 15;
      printf("%-5d  %-8s %2d ",j++,mn_temp->word,mn_temp->f_cout);
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


status create_database(f_list **head,ht_arr arr[27]){
  f_list * temp = *head;
  int i = 0;

  while(temp != NULL)
  {
    // printf("file %d %s\n",i++,temp->fname );
    FILE * fp  = fopen(temp->fname,"r");
    if(fp == NULL)
    {
      return FAILURE;
    }

    char buffer[256];
    int ind;
    /* loop will scan until end of the file*/
    int updone = 0;

    while(fscanf(fp, "%s",buffer) == 1)
    {
      updone = 0;
      // printf("file data %s\n",buffer);
      char ch = tolower(buffer[0]) - 'a';
      ind = ch;
      if(ind >= 0 && ind <= 25){
        ind = ch;
      }else{
        ind = 26;
      }
      sub_node *sn_temp;
      main_node *mn_temp;

      if(arr[ind].mn_link == NULL){                                           /* when main node has null that time execute */
        if(insert_last_main_node(&arr[ind].mn_link,buffer)== FAILURE ){
          return FAILURE;
        }else{
          if(insert_last_sub_node(&arr[ind].mn_link->sn_link,temp->fname)== FAILURE ){
            return FAILURE;
          }else{
            updone = 1;
          }
        }
      }

      mn_temp = arr[ind].mn_link;
      while(mn_temp != NULL){
        if(strcasecmp(mn_temp->word,buffer) == 0  && updone == 0){                            /* word equal no need to create a mani node */
          sn_temp = mn_temp->sn_link;
          while(sn_temp != NULL){
            if(strcmp(sn_temp->fname , temp->fname)== 0 ){                                   /* words and files are equal increment the word count */
              // printf("%s increase word count\n",temp->fname);
                  sn_temp->w_count += 1;
                  updone = 1;
                  break;
            }
            sn_temp= sn_temp->sn_link;
          }
          if(updone == 0){                                                                     /* word are equal but file not present */
            if(insert_last_sub_node( &mn_temp->sn_link ,temp->fname)== FAILURE ){
              return FAILURE;
            }else{
              mn_temp->f_cout += 1;
              updone =1;
            }
          }
        }
        if(mn_temp->mn_link == NULL){
          break;
        }
        mn_temp = mn_temp->mn_link;
      }

      if(updone == 0){
        // printf("insert main node word not present %s\n",buffer);                                                                 /* word are not present insert new node */
        if(insert_last_main_node(&mn_temp->mn_link,buffer)== FAILURE ){
          return FAILURE;
        }else{
          if(insert_last_sub_node(&mn_temp->mn_link->sn_link,temp->fname) == FAILURE){
            return FAILURE;
          }else{
            // mn_temp->mn_link->f_cout +=1;
            // mn_temp->f_cout +=1;
            updone =1;
          }
        }
      }

    }
    fclose(fp);
    // printf("%s done\n",temp->fname);
    temp = temp->link;
  }

 display(arr);
  return SUCCESS;
}


/*
  char ch;
    char buffer[256];
    int index;
    while(fscanf(fp,"%s",buffer) == 1)
    {
      printf("%s\n",buffer);
      char low = tolower(buffer[0]);
      index = low - 97;
      main_node *mn_temp = arr[index].mn_link;
      if(mn_temp == NULL){
        printf("insert first\n");
        if(insert_last_main_node(&arr[index].mn_link,buffer)== FAILURE){
          return FAILURE;
        }else{
          printf("done\n");
        }
      }
      while(mn_temp != NULL){
       if(strcasecmp(mn_temp->word,buffer)== 0){   /* word equal 
          sub_node * sn_temp = mn_temp->sn_link;
          int done =0;
          while (sn_temp != NULL)
          {
            if(strcmp(sn_temp->fname,temp->fname)== 0){   /* file name equal increace the  
              sn_temp->w_count += 1;
              done =1;
              break;
            }
            sn_temp = sn_temp->sn_link;
          }
          if(done == 0){
            mn_temp->f_cout += 1;
            puts("create a subnode");
           if( insert_last_sub_node( &mn_temp->sn_link,temp->fname) == FAILURE){
              return FAILURE;
            }else{
              puts("done");
            }
          } 
        }else{
          puts("word not equal create a new main node ");
          if(insert_last_main_node(&arr[index].mn_link,buffer)== FAILURE){             word not present in the main node  create a new node 
            return FAILURE;
          }else{
            puts("done");
          }
        }
        mn_temp = mn_temp->mn_link;
      }

    
    };
    printf("\n");
    fclose(fp);
    temp = temp->link;

  }



*/


/*


  
  sub_node *temp = *node ;
  while(temp != NULL){
    temp = temp->sn_link;
  }
  sub_node *new = malloc(sizeof(sub_node));
  if(new == NULL){
    return FAILURE;
  }
  new->fname = malloc( (strlen(fname) * sizeof(char)) );
  if(new->fname== NULL){
    return FAILURE;
  }
  strcpy(new->fname,fname);
  new->sn_link = NULL;
  new->w_count = 1;
  temp = new;
  return SUCCESS;

}

*/