#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algo.h"

int main(int argc, char* argv[])
{
	int asset = 0;
	int retcode = 0;
	float lambda;
	//int *p = &asset;
	FILE* pInput;
	char buf[10000];
	float *covariance, *mean, *upperbound, *lowerbound, *x;
	if(argc != 2){
	  printf("Usage: port.exe datafilename");
	}

	pInput = fopen(argv[1],"r");
	if(pInput == 0)
	  {
	    printf("Error opening file\n");
	    return(-1);
	  }
	//Get Number of assets
	fgets(buf, sizeof(buf), pInput);
	char* tok = strtok(buf,",");
	tok = strtok(NULL,",");
	asset = atoi(tok);


	//Initiate covariance matrix
	covariance = (float *)calloc(asset*asset, sizeof(float));
	int i, j;

	//Read Covariance matrix
	for (i = 0; i < asset; i++)
	  {
	    fgets(buf, sizeof(buf),pInput);
	    tok = strtok(buf,",");
	    for(j = 0; j < asset; j++)
	      {
		tok = strtok(NULL,",");
		covariance[i*asset+j] = atof(tok);
	      }
	  }
	
	//Initiate Other vectors
	mean = (float *)calloc(asset, sizeof(float));
	upperbound = (float *)calloc(asset, sizeof(float));
	lowerbound = (float *)calloc(asset, sizeof(float));
	x = (float *)calloc(asset, sizeof(float));
	//Get Mean
	fgets(buf, sizeof(buf),pInput);
	tok = strtok(buf,",");
	for (i = 0; i < asset; i++)
	  {
	    tok = strtok(NULL,",");
	    mean[i] = atof(tok);
	  }

	//Get Upperbound
	fgets(buf, sizeof(buf), pInput);
	tok = strtok(buf,",");
	for (i = 0; i < asset; i++)
	  {
	    tok = strtok(NULL,",");
	    upperbound[i] = atof(tok);
	    //printf("%f",upperbound[i]);
	  }

	//Get Lowerbound
	fgets(buf, sizeof(buf), pInput);
	tok = strtok(buf,",");
	for (i = 0; i < asset; i++)
	  {
	    tok = strtok(NULL,",");
	    lowerbound[i] = atof(tok);
	  }


	fgets(buf, sizeof(buf), pInput);
	tok = strtok(buf,",");
	tok = strtok(NULL,",");
	lambda = atof(tok);
	fclose(pInput);
	
	algorithm(asset, lowerbound, upperbound, lambda, mean, covariance, x);
	for(i = 0; i < asset; i++)
	  {
	    printf("%f\n",x[i]);
	  }
	free(mean);
	free(covariance);
	free(upperbound);
	free(lowerbound);
	free(x);
	return(0);
	
}
