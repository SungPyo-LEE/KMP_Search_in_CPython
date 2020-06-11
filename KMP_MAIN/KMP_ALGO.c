#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int knuthMorrisPratt(char* text, int textSize, int start, char* pattern, int patternSize);

void preprocess(char* pattern, int patternSize, int* border);

int knuthMorrisPratt(char* text, int textSize, int start, char* pattern, int patternSize)
{
	int i = start;
	int j = 0;
	int position = -1;
	int* border = (int*)calloc(patternSize+1, sizeof(int));
	preprocess(pattern, patternSize, border);
	while( i < textSize )
	{
		while( j >= 0 && text[i] != pattern[j] )
			j = border[j];
		i++;
		j++;
		if( j == patternSize )
		{
		position = i - j;
		break;
		}
	}
	free(border);
	return position;
}

void preprocess(char* pattern, int patternSize, int* border)
{
	int i = 0;
	int j = -1;
	border[0] = -1;
	while( i < patternSize )
	{
		while( j > -1 && pattern[i] != pattern[j] )
			j = border[j];
		i++;
		j++;
	border[i] = j;
	}
}

int main()
{
    char Text[] = "ABC ABCDAB ABCDABCDABDE";
    char Pattern[] = "AB";
    int P_size = strlen(Pattern);
    int n = strlen(Text);
    double Position = knuthMorrisPratt(Text, strlen(Text), 0, Pattern, P_size);
	printf("%f\n", Position+1);
    int i_1 = Position + 1;
	int first = i_1;
	Position =knuthMorrisPratt(Text, strlen(Text), i_1, Pattern, P_size);
	int i_2 = Position+1;
	printf("%d\n",first);
	i_1 = Position + 1;
	while (i_2 > first)
	{
		Position =knuthMorrisPratt(Text, strlen(Text), i_2+1, Pattern, P_size);
		int i_2 = Position+1;
		printf("%f\n", Position+1);
	}
	return 0;
}