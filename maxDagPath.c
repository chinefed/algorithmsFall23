
#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;
typedef struct Edge edge;
typedef struct NodeList nodeList;

void initNode(node *myNode, int label, node *parent, node *child);
void initEdge(edge *myEdge, node *toNode, edge *parent, edge *child);
void initNodeList(nodeList *myNodeList);
void addNode(nodeList *myNodeList, int label);
void addEdge(node *myNode, node *toNode);
void moveNodeAtHead(nodeList *myNodeList, node *myNode);
void freeNodeList(nodeList *myNodeList);
void freeEdgeList(node *myNode);
void dfs(nodeList *myNodeList, node *myNode);
void topologicalSort(nodeList *myNodeList);
int longestPath(nodeList *myNodeList, node *myNode);

typedef struct Node
{
    int label;
    edge *E;
    node *parent;
    node *child;
    int maxPath;
    node *maxChild;
    char color;
} node;

typedef struct Edge
{
    node *toNode;
    edge *parent;
    edge *child;
} edge;

typedef struct NodeList
{
    node *head;
} nodeList;

void initNode(node *myNode, int label, node *parent, node *child)
{
    myNode->label = label;
    myNode->E = NULL;
    myNode->parent = parent;
    myNode->child = child;
    myNode->maxPath = 0;
    myNode->maxChild = NULL;
    myNode->color = 1;
}

void initEdge(edge *myEdge, node *toNode, edge *parent, edge *child)
{
    myEdge->toNode = toNode;
    myEdge->parent = parent;
    myEdge->child = child;
}

void initNodeList(nodeList *myNodeList)
{
    myNodeList->head = NULL;
}

void addNode(nodeList *myNodeList, int label)
{
    node *newNode;
    newNode = (node *)malloc(sizeof(node));
    initNode(newNode, label, NULL, myNodeList->head);
    if (myNodeList->head != NULL)
        (myNodeList->head)->parent = newNode;
    myNodeList->head = newNode;
}

void addEdge(node *myNode, node *toNode)
{
    edge *newEdge;
    newEdge = (edge *)malloc(sizeof(edge));
    initEdge(newEdge, toNode, NULL, myNode->E);
    if (myNode->E != NULL)
        (myNode->E)->parent = newEdge;
    myNode->E = newEdge;
}

void moveNodeAtHead(nodeList *myNodeList, node *myNode)
{
    if (myNode == myNodeList->head)
        return;

    if (myNode->parent != NULL)
        (myNode->parent)->child = myNode->child;

    if (myNode->child != NULL)
        (myNode->child)->parent = myNode->parent;

    myNode->parent = NULL;
    myNode->child = myNodeList->head;
    myNodeList->head = myNode;
}

void freeNodeList(nodeList *myNodeList)
{
    node *n = myNodeList->head;
    while (n != NULL)
    {
        node *temp = n->child;
        freeEdgeList(n);
        free(n);
        n = temp;
    }
}

void freeEdgeList(node *myNode)
{
    edge *e = myNode->E;
    while (e != NULL)
    {
        edge *temp = e->child;
        free(e);
        e = temp;
    }
}

void dfs(nodeList *myNodeList, node *myNode)
{
    if (myNode->color != 1)
        return;

    myNode->color = 2;
    edge *e = myNode->E;
    while (e != NULL)
    {
        dfs(myNodeList, e->toNode);
        e = e->child;
    }

    myNode->color = 3;
    moveNodeAtHead(myNodeList, myNode);
}

void topologicalSort(nodeList *myNodeList)
{
    node *n = myNodeList->head;
    while (n != NULL)
    {
        dfs(myNodeList, n);
        n = n->child;
    }
}

int longestPath(nodeList *myNodeList, node *myNode)
{
    if (myNode->maxPath != 0)
        return myNode->maxPath;

    int maxPath = 1;
    node *maxChild = NULL;
    edge *e = myNode->E;
    while (e != NULL)
    {
        int path = longestPath(myNodeList, e->toNode) + 1;
        if (path > maxPath)
        {
            maxPath = path;
            maxChild = e->toNode;
        }
        e = e->child;
    }
    myNode->maxPath = maxPath;
    myNode->maxChild = maxChild;

    return maxPath;
}

int main(void)
{

    int numberNodes;
    int numberEdges;
    scanf("%d%d", &numberNodes, &numberEdges);

    node **nodePtrMap;
    nodePtrMap = (node **)malloc((numberNodes + 1) * sizeof(node *));

    nodeList nodes;
    initNodeList(&nodes);

    for (int i = 1; i <= numberNodes; i++)
    {
        addNode(&nodes, i);
        nodePtrMap[i] = nodes.head;
    }

    for (int i = 0; i < numberEdges; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(nodePtrMap[u], nodePtrMap[v]);
    }

    topologicalSort(&nodes);

    node *n = nodes.head;
    while (n != NULL)
    {
        longestPath(&nodes, n);
        n = n->child;
    }

    int longestPath = 0;
    node *longestPathHead = NULL;
    n = nodes.head;
    while (n != NULL)
    {
        if (n->maxPath > longestPath)
        {
            longestPath = n->maxPath;
            longestPathHead = n;
        }
        n = n->child;
    }

    printf("%d\n", longestPath);
    n = longestPathHead;
    while (n != NULL)
    {
        printf("%d ", n->label);
        n = n->maxChild;
    }

    freeNodeList(&nodes);
    free(nodePtrMap);
}
