
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b);

int main()
{

    while (1)
    {

        // Get the knapsack capacity and the number of items
        int capacity, numberItems;
        if (scanf("%d%d", &capacity, &numberItems) != 2)
        {
            return 0;
        }

        // Get the value and weight of each item
        int *values, *weights;
        values = (int *)malloc((numberItems + 1) * sizeof(int));
        weights = (int *)malloc((numberItems + 1) * sizeof(int));
        for (int i = 1; i <= numberItems; i++)
        {
            int v, w;
            scanf("%d%d", &v, &w);
            values[i] = v;
            weights[i] = w;
        }

        // We declare the DP table
        int **dp;
        dp = (int **)malloc((numberItems + 1) * sizeof(int *));
        for (int i = 0; i <= numberItems; i++)
        {
            dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
        }

        // Base cases
        for (int i = 0; i <= numberItems; i++)
        {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= capacity; j++)
        {
            dp[0][j] = 0;
        }

        // Recursive cases
        for (int i = 1; i <= numberItems; i++)
        {
            for (int j = 1; j <= capacity; j++)
            {
                if (weights[i] > j)
                {
                    dp[i][j] = dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
                }
            }
        }

        free(values);

        // Traverse the DP table
        int i = numberItems;
        int j = capacity;
        int c = 0;
        int *indexes;
        indexes = (int *)malloc((numberItems + 1) * sizeof(int));
        while (i > 0 && j > 0)
        {
            if (dp[i][j] == dp[i - 1][j])
            {
                i--;
            }
            else
            {
                indexes[c] = i;
                j -= weights[i];
                i--;
                c++;
            }
        }

        free(weights);
        free(dp);

        // Print the indexes
        printf("%d\n", c);
        for (int i = 0; i < c; i++)
        {
            printf("%d ", indexes[i] - 1);
        }
        printf("\n");

        free(indexes);
    }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}