#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "main.h"


int main()
{
	int dim=20000;
	initRand();
	int* seed;
	generateBSC(&seed,dim);
	int** contextVecs;
	generateContextVectors(&contextVecs,dim);
	int* vec;
	frequencyToVector(&vec,&contextVecs,seed,.0516,dim);
	int* vec2;
	frequencyToVector(&vec2,&contextVecs,seed,.0007,dim);
	int* vec3;
	frequencyToVector(&vec3,&contextVecs,seed,.0510,dim);
	printf("%f \n",hammingBSCNoTouch(vec,vec2,dim));
	printf("%f \n",hammingBSCNoTouch(vec,vec3,dim));
	struct TXT txt;
	readTXT(&txt,"./resources/subCipher.txt");
}
