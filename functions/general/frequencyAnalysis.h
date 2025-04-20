#ifndef ANALYZER_H
#define ANALYZER_H


void countCipherChar(int** cipherCharCount,char character)
{
	(*cipherCharCount)[charToIndex(character)]+=1;
	//printf("%d %c \n",(*cipherCharCount)[charToIndex(character)],character);
}

void freqCalc(float** cipherFreqs,struct TXT* txt)
{
	(*cipherFreqs)=(float*)malloc(26*sizeof(float));
	int* cipherCharCount;
	cipherCharCount=(int*)malloc(26*sizeof(int));
	for(int i=0;i<txt->CHARCOUNT;i++)
	{
		countCipherChar(&(cipherCharCount),txt->CHARACTERS[i]);
	}
	for(int i=0;i<26;i++)
	{
		(*cipherFreqs)[i]=(float)cipherCharCount[i]/txt->CHARCOUNT;
	}
	free(cipherCharCount);
}

//Insertion-sort for cipherFreqs
void sortFreqs(float** sortedFreqs,float* cipherFreqs)
{
	int j;
	float key;
	(*sortedFreqs)=(float*)malloc(26*sizeof(float));
	memcpy((*sortedFreqs),cipherFreqs,26*sizeof(float));
	for(int i=1;i<26;i++)
	{
		key=(*sortedFreqs)[i];
		j=i-1;
		while(j>=0&&(*sortedFreqs)[j]>key)
		{
			(*sortedFreqs)[j+1]=(*sortedFreqs)[j];
			j=j-1;
		}
		(*sortedFreqs)[j+1]=key;
	}
}

int isDuplicateIndex(int* indexes,int index)
{
	int duplicate=0;
	for(int i=0;i<26;i++)
	{
		if(index==indexes[i])
		{
			duplicate=1;
		}
	}
	return duplicate;
}

void sortIndexes(int** indexes,float* sortedFreqs,float* cipherFreqs)
{
	(*indexes)=(int*)malloc(26*sizeof(int));
	for(int i=0;i<26;i++)
	{
		(*indexes)[i]=27;
	}
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			if(sortedFreqs[i]==cipherFreqs[j]&&isDuplicateIndex((*indexes),j)==0)
			{
				(*indexes)[i]=j;
			}
		}
	}
}


#endif
