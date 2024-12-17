#include <stdio.h>
#include <stdlib.h>

struct tagSupplier
{
    int id;
    float price;
    float score;
};
// 侧重指向表节点
typedef struct tagSupplierNode
{
    struct tagSupplier data;
    struct tagSupplierNode *next;
} Node;
// 侧重指向链表
typedef struct tagSupplierList
{
    Node *head;
    Node *tail;
} *tagSupplierList;

void ReadDataFromFile(char *filename, tagSupplierList supplierList);
void SortByPrice(tagSupplierList supplierList);

int main()
{
    tagSupplierList supplierList = (tagSupplierList)malloc(sizeof(tagSupplierList));
    supplierList->head = NULL;
    supplierList->tail = NULL;
    ReadDataFromFile("Suppliers.txt", supplierList);
    SortByPrice(supplierList);
    return 0;
}

void ReadDataFromFile(char *filename, tagSupplierList supplierList)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("error!\n");
        exit(-1);
    }
    struct tagSupplier dataArray[100];
    int count = 0;
    while (!feof(fp) && count < 100)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        if (fscanf(fp, "%d %f %f", &(node->data.id), &(node->data.price), &(node->data.score)) == 3)
        {
            node->next = NULL;
            if (supplierList->head == NULL)
            {
                supplierList->head = node;
                supplierList->tail = node;
            }
            else
            {
                supplierList->tail->next = node;
                supplierList->tail = node;
            }
            printf("ID: %d, Price: %.2f, Score: %.2f\n", node->data.id, node->data.price, node->data.score);
        }
        else
        {
            free(node);
        }
    }
}
void SortByPrice(tagSupplierList supplierList)
{
    if (supplierList->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    Node *current = supplierList->head;

    while (current != NULL)
    {
        Node *minNode = current;
        Node *temp = current->next;

        while (temp != NULL)
        {
            // 找到价格最小的节点
            if (temp->data.price < minNode->data.price)
            {
                minNode = temp;
            }
            temp = temp->next;
        }

        // 交换数据
        struct tagSupplier tempData = current->data;
        current->data = minNode->data;
        minNode->data = tempData;

        current = current->next;
    }

    // 输出排序后的链表内容
    printf("\nSorted by Price:\n");
    current = supplierList->head;
    while (current != NULL)
    {
        printf("ID: %d, Price: %.2f, Score: %.2f\n", current->data.id, current->data.price, current->data.score);
        current = current->next;
    }
}