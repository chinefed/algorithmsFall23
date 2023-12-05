
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct Node node;
typedef struct Edge edge;

typedef struct Node
{
    int64_t idx;
    int64_t cost;
    int64_t flag;
    edge *edges;
} node;

typedef struct Edge
{
    node *child;
    edge *next;
} edge;

void initNode(node *myNode, int64_t idx, int64_t cost);
void addEdge(node *myNodeArray, int64_t u, int64_t v);
void freeNodeArray(node *myNodeArray, int64_t nNodes);
void fillTable(node *myNode, int64_t **dp, int64_t nNodes);
int64_t min(int64_t x, int64_t y);

int main(void)
{

    int64_t nTests;
    scanf("%" SCNd64, &nTests);

    for (int64_t i = 0; i < nTests; i++)
    {
        int64_t nNodes;
        scanf("%" SCNd64, &nNodes);

        node *nodeArray;
        nodeArray = (node *)malloc(nNodes * sizeof(node));

        int64_t cost;
        for (int64_t j = 0; j < nNodes; j++)
        {
            scanf("%" SCNd64, &cost);
            initNode(nodeArray + j, j, cost);
        }

        int64_t u, v;
        for (int64_t j = 0; j < nNodes - 1; j++)
        {
            scanf("%" SCNd64 "%" SCNd64, &u, &v);
            addEdge(nodeArray, u-1, v-1);
            addEdge(nodeArray, v-1, u-1);
        }

        int64_t **dp;
        dp = (int64_t **)malloc(nNodes * sizeof(int64_t *));
        for (int64_t j = 0; j < nNodes; j++)
            dp[j] = (int64_t *)calloc(2, sizeof(int64_t));

        fillTable(nodeArray, dp, nNodes);

        int64_t minVC = min(dp[0][0], dp[0][1]);
        printf("%" PRId64 "\n", minVC);

        freeNodeArray(nodeArray, nNodes);
        for (int64_t j = 0; j < nNodes; j++)
            free(dp[j]);
        free(dp);
    }

    return 0;
}

void initNode(node *myNode, int64_t idx, int64_t cost)
{
    myNode->idx = idx;
    myNode->cost = cost;
    myNode->flag = 0;
    myNode->edges = NULL;

    return;
}

void addEdge(node *myNodeArray, int64_t u, int64_t v)
{
    node *parent = myNodeArray + u;
    node *child = myNodeArray + v;

    edge *newEdge;
    newEdge = (edge *)malloc(sizeof(edge));
    newEdge->child = child;
    newEdge->next = (parent->edges == NULL) ? NULL : parent->edges;
    parent->edges = newEdge;

    return;
}

void freeNodeArray(node *myNodeArray, int64_t nNodes)
{
    for (int64_t i = 0; i < nNodes; i++)
    {
        edge *e = myNodeArray[i].edges;
        while (e != NULL)
        {
            edge *temp = e;
            e = e->next;
            free(temp);
        }
    }
    free(myNodeArray);

    return;
}

void fillTable(node *myNode, int64_t **dp, int64_t nNodes)
{

    dp[myNode->idx][0] = 0;
    dp[myNode->idx][1] = myNode->cost;
    myNode->flag = 1;

    if (myNode->edges == NULL)
        return;
    
    edge *e = myNode->edges;
    while (e != NULL)
    {
        if (!(e->child->flag))
        {
            fillTable(e->child, dp, nNodes);
            dp[myNode->idx][0] += dp[e->child->idx][1];
            dp[myNode->idx][1] += min(dp[e->child->idx][0], dp[e->child->idx][1]);
        }
        e = e->next;
    }

    return;
}

int64_t min(int64_t x, int64_t y)
{
    return (x < y) ? x : y;
} 