#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BUFFER 512
int Border[MAX_BUFFER];

void Preprocess(char* Pattern, int PatternSize)
{
	int i = 0;
	int j = -1;
	
	Border[0] = -1;
	while (i < PatternSize)
	{
		while(j>-1 && Pattern[i] != Pattern[j])
            j = Border[j];
        i++;
        j++;

        Border[i] = j;
    }
}

double KMP(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
    int i = Start;
    int j = 0;
    double Position = -1;
    Preprocess(Pattern, PatternSize);

    while(i < TextSize)
    {
        while(j>=0 && Text[i] != Pattern[j])
            j = Border[j];
        i++;
        j++;
        if (j == PatternSize)
        {
            Position = (double)i - (double)j;
            break;
        }
    }
    return Position;
}

int main()
{
	double *vector;
    char Text[] = "ABC ABCDAB";
    char Pattern[] = "ABC";
    int P_size = strlen(Pattern);
    int n = strlen(Text);
    double Position = KMP(Text, strlen(Text), 0, Pattern, P_size);
    int i = 0;
	int cnt = 0;
    while (i < n)
    {
        double Position = KMP(Text, strlen(Text), i, Pattern, P_size);
        printf("%lf, %s \n", Position, Text);
		if (Position + P_size > i || i == 0)
		{
			i = Position + P_size;
			cnt += 1;
		}
		else
			break;
    }
	vector = (double*)malloc(sizeof(double) * cnt - 1);
	i = 0;
    while (i < n)
    {
        double Position = KMP(Text, strlen(Text), i, Pattern, P_size);
        //printf("%lf, %s \n", Position, Text);
		if (Position + P_size > i || i == 0)
		{
			i = Position + P_size;
			vector[i]=Position;
		}
		else
			break;
    }
	int j = sizeof(vector)/sizeof(double);
	for (int i =0; i<j; ++i)
		printf("%lf", vector[i]);
	free(vector);
    return 0;
}