
#include <stdio.h>
#include <stdlib.h>

typedef struct Event
{
    int interval; // Interval ID
    int key;      // Event key
    int demand;   // Demand
    char type;    // Begin (1) or end (0)
} event;

void initEvent(event *myEvent, int interval, int key, int demand, char type);
void merge(event *myArray, int left, int mid, int right);
void mergeSort(event *myArray, int left, int right);

int main(void)
{

    int nTestCases;
    scanf("%d", &nTestCases);

    for (int i = 0; i < nTestCases; i++)
    {
        int nIntervlas;
        scanf("%d", &nIntervlas);
        event *events;
        events = (event *)malloc(2 * nIntervlas * sizeof(event));
        int k = 0;
        for (int j = 0; j < nIntervlas; j++)
        {
            int left, right, demand;
            scanf("%d%d%d", &left, &right, &demand);
            initEvent(&events[k], j, left, demand, 1);
            k++;
            initEvent(&events[k], j, right, demand, 0);
            k++;
        }

        mergeSort(events, 0, k - 1);

        int *begSolutionSize;
        begSolutionSize = (int *)malloc(nIntervlas * sizeof(int));
        int solutionSize = 0;
        for (int j = 0; j <= (k - 1); j++)
        {
            if (events[j].type == 1)
                begSolutionSize[events[j].interval] = solutionSize;
            else
            {
                int c = solutionSize - begSolutionSize[events[j].interval];
                if (c < events[j].demand)
                    solutionSize += events[j].demand - c;
            }
        }
        printf("%d\n", solutionSize);
        free(events);
        free(begSolutionSize);
    }
}

void initEvent(event *myEvent, int interval, int key, int demand, char type)
{
    myEvent->interval = interval;
    myEvent->key = key;
    myEvent->demand = demand;
    myEvent->type = type;
}

void merge(event *myArray, int left, int mid, int right)
{
    int s1, s2;
    event *temp1, *temp2;
    s1 = mid - left + 1;
    s2 = right - mid;
    temp1 = (event *)malloc(s1 * sizeof(event));
    temp2 = (event *)malloc(s2 * sizeof(event));
    for (int i = 0; i < s1; i++)
        temp1[i] = myArray[left + i];
    for (int j = 0; j < s2; j++)
        temp2[j] = myArray[mid + 1 + j];

    int i, j, k;
    i = j = 0;
    k = left;
    while ((i < s1) && (j < s2))
    {
        if (temp1[i].key < temp2[j].key || (temp1[i].key == temp2[j].key && temp1[i].type >= temp2[j].type))
        {
            myArray[k] = temp1[i];
            i++;
        }
        else
        {
            myArray[k] = temp2[j];
            j++;
        }
        k++;
    }

    while (i < s1)
    {
        myArray[k] = temp1[i];
        i++;
        k++;
    }
    while (j < s2)
    {
        myArray[k] = temp2[j];
        j++;
        k++;
    }

    free(temp1);
    free(temp2);
}

void mergeSort(event *myArray, int left, int right)
{
    if (right > left)
    {
        int mid = (left + right) / 2;
        mergeSort(myArray, left, mid);
        mergeSort(myArray, mid + 1, right);
        merge(myArray, left, mid, right);
    }
}