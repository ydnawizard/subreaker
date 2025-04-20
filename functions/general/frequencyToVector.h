#ifndef FREQUENCYTOVECTOR_H
#define FREQUENCYTOVECTOR_H

//CONVERT 4 DECIMAL PLACE FLOAT FREQUENCIES TO SINGULAR REPLICABLE AND REPRESENTATIVE HYPERVECTORS\\
//
//How this works: The seed hypervector is initialized in the main function and passed in. An array of 4 randomly generated
//context hypervectors is also intialized in the main function and passed in. An array of 4 copies of the seed hypervector
//is initialized in here. Each of these four seed hypervectors are permuted or shifted n times, where n is the value of th//e digit in the corresponding decimal place. These permuted hypervectors are then bound with their corresponding context
//hypervectors and then bundled together to create a hypervector to create a hypervector that is has components in 
//common with similar frequencies.
//
//
//Initialize vec array of size 4 (because we are dealing withfloats to 4 decimal places)
//with copies of the seed hypervector
void seedVectors(int*** vecs,int* seed,int dim)
{
	(*vecs)=(int**)malloc(4*sizeof(int*));
	for(int i=0;i<4;i++)
	{
		(*vecs)[i]=(int*)malloc(dim*sizeof(int));
		for(int j=0;j<dim;j++)
		{
			(*vecs)[i][j]=seed[j];
		}
	}
}

void generateContextVectors(int*** vecs,int dim)
{
	(*vecs)=(int**)malloc(4*sizeof(int*));
	for(int i=0;i<4;i++)
	{
		(*vecs)[i]=(int*)malloc(dim*sizeof(int));
		generateBSC(&(*vecs)[i],dim);
	}
}

//Grab values of each individual digit in float after decimal
void grabValues(int** values,float freq)
{
	char floatStr[16];
	(*values)=(int*)malloc(4*sizeof(int));
	sprintf(floatStr,"%f",freq);
	for(int i=2;i<6;i++)
	{ (*values)[i]=floatStr[i]-'0'; }
}

//Permute vectors based on value of it's corresponding decimal place value
void permuteSeedVectors(int*** vecs,float freq,int dim)
{
	int* values;
	grabValues(&values,freq);
	for(int i=2;i<6;i++)
	{
		for(int j=0;j<values[i];j++)
		{
			permuteBSCTouch(&(*vecs)[i-2],dim);
		}
	}
}

//Bind vectors with with context vectors 
void bindVectorsToContext(int*** vecs,int** contextVecs,int dim)
{
	int* contextVec;
	for(int i=0;i<4;i++)
	{
		bindBSCTouch(&(*vecs)[i],contextVecs[i],dim);
	}
}

void bundleVectorsWithSeed(int*** vecs,int* seed,int dim)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<i;j++)
		{
			bundleBSCTouch(&(*vecs)[i],seed,dim);
		}
	}
}

void bundleInfluence(int*** vecs,int dim)
{
	for(int i=0;i<4;i++)
	{
		for(int j=i;j<3;j++)
		{
			bundleBSCTouch(&(*vecs)[i+1],(*vecs)[i],dim);
		}
	}
}

 void bundleVectors(int** outVec,int** vecs,int dim)
{
	for(int i=0;i<3;i++)
	{
		bundleBSCNoTouch(&(*outVec),vecs[i],vecs[i+1],dim);
	}
}

void frequencyToVector(int** outVec,int*** contextVecs,int* seed,float freq,int dim)
{
	int** vecs;
	(*outVec)=(int*)malloc(dim*sizeof(int));
	seedVectors(&vecs,seed,dim);
	permuteSeedVectors(&vecs,freq,dim);
	bindVectorsToContext(&vecs,(*contextVecs),dim);
	bundleInfluence(&vecs,dim);
	bundleVectors(&(*outVec),vecs,dim);
	free(vecs);
}



#endif
