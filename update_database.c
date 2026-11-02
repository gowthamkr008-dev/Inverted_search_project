#include "ISP.h"


status updata_database(ht_arr arr[27],char *filename)
{
  int i; 
  
  for (i = 0; i < 27 ;i++)
  {
    if(arr[i].mn_link != NULL)
    {
      printf("Database is not Empty\n");
      return SUCCESS;
    }
  }
  
  FILE *fp = fopen(filename,"r");
  if(fp == NULL)
  {
    return FAILURE;
  }
  
}