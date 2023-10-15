
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int x, int y);
int cutCost(int cut, int i, int j);

int main(void)
{
    int length, numCuts;
    scanf("%d%d", &length, &numCuts);
    numCuts += 2; // we consider also the endpoint of the plank

    int *cuts;
    cuts = (int *)malloc(numCuts * sizeof(int));
    cuts[0] = 0;
    for (int i = 1; i < numCuts-1; i++)
    {
        scanf("%d", &cuts[i]);
    }
    cuts[numCuts-1] = length;

    int **dp;
    dp = (int **)malloc(numCuts * sizeof(int *));
    for (int i = 0; i < numCuts; i++)
    {
        dp[i] = calloc(numCuts, sizeof(int));
    }

    for (int i = numCuts-2; i >= 0; i--)
    {
        for (int j = i + 1; j < numCuts; j++)
        {
            int minTotCost = 0;
            for (int k = i + 1; k < j; k++)
            {
                int totCost = cutCost(cuts[k], cuts[i], cuts[j]) + dp[i][k] + dp[k][j];
                if ((INT_MAX - totCost) > minTotCost)
                    minTotCost = INT_MAX - totCost;
            }
            dp[i][j] = (minTotCost == 0) ? 0 : (INT_MAX - minTotCost);
        }
    }
    
    printf("%d", dp[0][numCuts-1]);

    free(cuts);
    for (int i = 0; i < numCuts; i++)
    {
        free(dp[i]);
    }
    free(dp);
}

int max(int x, int y)
{
    return (x > y) ? x : y;
}

int cutCost(int cut, int i, int j)
{
    return max(cut - i, j - cut);
}