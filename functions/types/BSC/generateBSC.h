#ifndef GENERATOR_H
#define GENERATOR_H

//Generates a seed for the pseudo random number generator
//Should be called before calling any hypervector generators
int initRand(){
	srand(time(NULL));
}



//Generates a binary spatter code hypervector
int generateRandBit()
{
	int randBit;
	randBit=rand()%2;
	return randBit;
}

//generateBSC: Generates a new binary spatter code (BSC) hypervector
//of dim dimensions
void generateBSC(int** vec,int dim)
{
	(*vec)=(int*)malloc(dim*sizeof(int));
	for(int i=0;i<dim;i++)
	{
		(*vec)[i]=generateRandBit();
	}
}

#endif
