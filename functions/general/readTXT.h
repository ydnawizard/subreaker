#ifndef READER_H
#define READER_H


//Define TXT struct that gets passed out
struct TXT
{
	char* CHARACTERS;
	int CHARCOUNT;
	char** STRINGS;
	int STRINGCOUNT;
	char** LINES;
	int LINECOUNT;
};

//CHAR FIELD FUNCTIONS
void readCharToTXT(struct TXT* txt,char character,int charCount)
{
	txt->CHARACTERS=realloc(txt->CHARACTERS,(charCount+1)*sizeof(char));
	txt->CHARACTERS[charCount]=character;
}

void readCharsToTXT(struct TXT* txt,FILE* file)
{
	int charCount=0;
	char character;
	while((character=fgetc(file))!=EOF)
	{
		readCharToTXT(&(*txt),character,charCount);
		charCount+=1;
	}
	txt->CHARCOUNT=charCount;
}

//STRING FIELD FUNCTIONS
void readCharToString(char** string,char character,int charCount)
{
	(*string)=(char*)realloc((*string),(charCount+1)*sizeof(char));
	(*string)[charCount]=character;
}

void readStringToTXT(struct TXT* txt,char* string,int stringCount)
{
	txt->STRINGS=(char**)realloc(txt->STRINGS,(stringCount+1)*sizeof(char*));
	txt->STRINGS[stringCount]=(char*)malloc(strlen(string)*sizeof(char));
	strcpy(txt->STRINGS[stringCount],string);
}

void readStringsToTXT(struct TXT* txt,FILE* file)
{
	int stringCount=0;
	int charCount=0;
	char* string=malloc(sizeof(char));
	char character;
	while((character=fgetc(file))!=EOF)
	{
		if(character==' '||character=='\n')
		{
			readStringToTXT(&(*txt),string,stringCount);
			string=(char*)realloc(string,sizeof(char));
			memset(string,'\0',strlen(string));
			stringCount+=1;
			charCount=0;
		}else
		{
			readCharToString(&string,character,charCount);
			charCount+=1;
		}
	}
	txt->STRINGCOUNT=stringCount;
	free(string);
}

//LINE FIELD FUNCTIONS

void readCharToLine(char** line,char character,int charCount)
{
	(*line)=(char*)realloc((*line),(charCount+1)*sizeof(char));
	(*line)[charCount]=character;
}

void readLineToTXT(struct TXT* txt,char* line,int lineCount)
{
	txt->LINES=(char**)realloc(txt->LINES,(lineCount+1)*sizeof(char*));
	txt->LINES[lineCount]=(char*)malloc(strlen(line)*sizeof(char));
	strcpy(txt->LINES[lineCount],line);
}

void readLinesToTXT(struct TXT* txt,FILE* file)
{
	int lineCount=0;
	int charCount=0;
	char* line=malloc(sizeof(char));
	char character;
	while((character=fgetc(file))!=EOF)
	{
		if(character=='\n')
		{
			readLineToTXT(&(*txt),line,lineCount);
			memset(line,'\0',strlen(line));
			lineCount+=1;
			charCount=0;
		}else
		{
			readCharToLine(&line,character,charCount);
			charCount+=1;
		}
	}
	txt->LINECOUNT=lineCount;
	free(line);
}



//MAIN READ FUNCTION
void readTXT(struct TXT* txt,char* filePath)
{
	txt->CHARACTERS=(char*)malloc(sizeof(char));
	txt->STRINGS=(char**)malloc(sizeof(char*));
	txt->LINES=(char**)malloc(sizeof(char*));
	FILE* file=fopen(filePath,"read");
	readCharsToTXT(&(*txt),file);
	rewind(file);
	readStringsToTXT(&(*txt),file);
	rewind(file);
	readLinesToTXT(&(*txt),file);
}
	


#endif
