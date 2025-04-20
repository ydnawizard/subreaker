#ifndef CONVERTER_H
#define CONVERTER_H

int charToIndex(char character)
{
	int index;
	for(int i=0;i<26;i++)
	{
		if(character==alpha[i])
		{
			index=i;
		}
	}
	return index;
}

float charToFrequency(char character)
{
	float freq;
	int index;
	index=charToIndex(character);
	freq=alphaFreq[index];
	return freq;
}

void stringToFrequencies(float** freqs,char* string)
{
	int letterCount;
	letterCount=strlen(string);
	(*freqs)=(float*)malloc(letterCount*sizeof(float));
	for(int i=0;i<letterCount;i++)
	{
		(*freqs)[i]=charToFrequency(string[i]);
	}
}

void stringsToFrequencies(float*** freqs,char** strings)
{
	int wordCount=0;
	while(strings[wordCount]!=NULL)
	{
		wordCount+=1;
	}
	(*freqs)=(float**)malloc(wordCount*sizeof(float*));
	for(int i=0;i<wordCount;i++)
	{
		(*freqs)[i]=(float*)malloc(strlen(strings[i])*sizeof(float));
		stringToFrequencies(&(*freqs)[i],strings[i]);
	}
}

 



#endif

