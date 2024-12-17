#include <stdio.h>
#include <stdlib.h>

// 定义供货信息结构体
struct tagSupplier
{
    int id;      // 商家编号
    float price; // 商品价格
    float score; // 用户评分
};

// 定义供货信息链表节点
struct tagSupplierNode
{
    struct tagSupplier data;      // 数据域，存放供货信息
    struct tagSupplierNode *next; // 指针域，指向下一个节点
};

// 定义供货信息链表
struct tagSupplierList
{
    struct tagSupplierNode *head; // 链表头指针
    struct tagSupplierNode *tail; // 链表尾指针
};

// 函数声明
void ReadDataFromFile(const char *filename, struct tagSupplierList *supplierList);
void SortByPrice(struct tagSupplierList *supplierList);

int main()
{
    // 创建供货信息链表
    struct tagSupplierList supplierList;
    supplierList.head = NULL;
    supplierList.tail = NULL;

    // 读取数据并输出链表内容
    ReadDataFromFile("Suppliers.txt", &supplierList);

    // 按价格排序并输出
    SortByPrice(&supplierList);

    return 0;
}

// 从文件中读取数据并存储到链表中
void ReadDataFromFile(const char *filename, struct tagSupplierList *supplierList)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    while (!feof(file))
    {
        struct tagSupplierNode *newNode = (struct tagSupplierNode *)malloc(sizeof(struct tagSupplierNode));
        if (fscanf(file, "%d %f %f", &(newNode->data.id), &(newNode->data.price), &(newNode->data.score)) == 3)
        {
            newNode->next = NULL;

            // 如果链表为空，设置头和尾指针为新节点
            if (supplierList->head == NULL)
            {
                supplierList->head = newNode;
                supplierList->tail = newNode;
            }
            else
            {
                // 否则将新节点链接到链表尾部，并更新尾指针
                supplierList->tail->next = newNode;
                supplierList->tail = newNode;
            }
        }
        else
        {
            free(newNode); // 释放未使用的节点
        }
    }

    fclose(file);

    // 输出链表内容
    struct tagSupplierNode *current = supplierList->head;
    while (current)
    {
        printf("ID: %d, Price: %.2f, Score: %.2f\n", current->data.id, current->data.price, current->data.score);
        current = current->next;
    }
}

// 按价格由低到高的原则进行选择排序
void SortByPrice(struct tagSupplierList *supplierList)
{
    if (supplierList->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    struct tagSupplierNode *current = supplierList->head;

    while (current != NULL)
    {
        struct tagSupplierNode *minNode = current;
        struct tagSupplierNode *temp = current->next;

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
