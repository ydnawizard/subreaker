#ifndef OPERATOR_H
#define OPERATOR_H

//XOR: Performs the XOR operation on two bits and returns result
int XOR(int bit1,int bit2)
{
	int outBit;
	if(bit1==bit2)
	{
		outBit=0;
	}else
	{
		outBit=1;
	}
	return outBit;
}

//hamming: Calculates hamming distance between two vectors
//hamming distance=#of matching components/#of components
float hammingBSCNoTouch(int* vec1,int* vec2,int dim)
{
	int same=0;
	for(int i=0;i<dim;i++)
	{
		if(vec1[i]==vec2[i])
		{
			same+=1;
		}
	}
	float hammingDistance=same/(float)dim;
	return hammingDistance;
}

void permuteBSCTouch(int** vec,int dim)
{
	int leader;
	for(int i=0;i<dim;i++)
	{
		if(i==(dim-1))
		{
			(*vec)[i]=leader;
		}else if(i==0)
		{
			leader=(*vec)[i];
			(*vec)[i]=(*vec)[i+1];
		}else
		{
			(*vec)[i]=(*vec)[i+1];
		}
	}
}

//bind: Does a bitwise XOR on two vectors
void bindBSCNoTouch(int** vecOut,int* vec1,int* vec2,int dim)
{
	(*vecOut)=(int*)malloc(dim*sizeof(int));
	for(int i=0;i<dim;i++)
	{
		(*vecOut)[i]=XOR(vec1[i],vec2[i]);
	}
}

void bindBSCTouch(int** vec1,int* vec2,int dim)
{
	for(int i=0;i<dim;i++)
	{
		(*vec1)[i]=XOR((*vec1)[i],vec2[i]);
	}
}

void bundleBSCTouch(int** vec1,int* vec2,int dim)
{
	int* tieBreaker;
	generateBSC(&tieBreaker,dim);
	for(int i=0;i<dim;i++)
	{
		if((*vec1)[i]!=vec2[i])
		{
			(*vec1)[i]=tieBreaker[i];
		}
	}
	free(tieBreaker);
}


//bundle: Does a thresholded-addition operation on two vectors
void bundleBSCNoTouch(int** vecOut,int* vec1,int* vec2,int dim)
{
	(*vecOut)=(int*)malloc(dim*sizeof(int));
	int* tieBreaker;
	generateBSC(&tieBreaker,dim);
	for(int i=0;i<dim;i++)
	{
		if(vec1[i]==vec2[i])
		{
			(*vecOut)[i]=vec1[i];
		}else
		{
			(*vecOut)[i]=tieBreaker[i];
		}
	}
	free(tieBreaker);
}



#endif
