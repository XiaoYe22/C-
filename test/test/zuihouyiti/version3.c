#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 商家信息结构体
typedef struct tagSupplier
{
    int id;      // 商家编号
    float price; // 商品价格
    float score; // 用户评分
} Supplier;

// 链表节点结构体
typedef struct tagSupplierList
{
    Supplier data;                // 节点数据
    struct tagSupplierList *next; // 指向下一个节点的指针
} SupplierList;

// 创建带头节点的链表（返回头节点指针）
SupplierList *createList()
{
    SupplierList *head = (SupplierList *)malloc(sizeof(SupplierList));
    if (head == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    head->next = NULL; // 头节点的 next 指针为 NULL
    return head;
}

// 创建一个新的商家信息节点
SupplierList *createNode(Supplier supplier)
{
    SupplierList *newNode = (SupplierList *)malloc(sizeof(SupplierList));
    if (newNode == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    newNode->data = supplier;
    newNode->next = NULL;
    return newNode;
}

// 向链表末尾添加节点
void appendNode(SupplierList *head, Supplier supplier)
{
    SupplierList *newNode = createNode(supplier);
    if (newNode == NULL)
        return;
    SupplierList *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next; // 遍历到链表末尾
    }
    temp->next = newNode; // 将新节点添加到链表末尾
}

// 读取文件并将数据存储到链表
int ReadDataFromFile(SupplierList *head, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("无法打开文件！\n");
        return -1;
    }

    Supplier supplier;
    while (fscanf(file, "%d %f %f", &supplier.id, &supplier.price, &supplier.score) == 3)
    {
        appendNode(head, supplier);
    }

    fclose(file);
    return 0;
}

// 输出链表中的数据
void printList(SupplierList *head)
{
    SupplierList *temp = head->next; // 跳过头节点，开始遍历实际数据
    while (temp != NULL)
    {
        printf("商家编号: %d\n", temp->data.id);
        printf("商品价格: %.2f\n", temp->data.price);
        printf("用户评分: %.2f\n", temp->data.score);
        printf("-----------------------------\n");
        temp = temp->next;
    }
}

// 按价格进行选择排序
void SortByPrice(SupplierList *head)
{
    if (head == NULL || head->next == NULL)
        return;

    SupplierList *i, *j;
    Supplier tempData;
    for (i = head->next; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->data.price > j->data.price)
            {
                // 交换数据
                tempData = i->data;
                i->data = j->data;
                j->data = tempData;
            }
        }
    }

    // 打印排序后的数据
    printf("按价格排序后的商家数据：\n");
    printList(head);
}

// 按照用户调查结果生成推荐列表
void Recommend(SupplierList *head)
{
    if (head == NULL || head->next == NULL)
        return;

    SupplierList *temp = head->next;
    int count = 0;
    float totalPrice = 0.0;

    // 计算所有商家的价格总和
    while (temp != NULL)
    {
        totalPrice += temp->data.price;
        count++;
        temp = temp->next;
    }

    float avgPrice = totalPrice / count;

    // 打印推荐商家
    printf("根据用户调查结果推荐商家：\n");
    temp = head->next;
    while (temp != NULL)
    {
        if (temp->data.price < avgPrice)
        {
            // 价格低于平均价格，推荐
            printf("商家编号: %d, 商品价格: %.2f, 用户评分: %.2f\n", temp->data.id, temp->data.price, temp->data.score);
        }
        else
        {
            // 价格高于平均价格，推荐评分高的商家
            if (temp->data.score > 9.0)
            {
                printf("商家编号: %d, 商品价格: %.2f, 用户评分: %.2f\n", temp->data.id, temp->data.price, temp->data.score);
            }
        }
        temp = temp->next;
    }
}

// 释放链表的所有节点
void freeList(SupplierList *head)
{
    SupplierList *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 主函数
int main()
{
    SupplierList *supplierList = createList(); // 创建带头节点的链表

    // 读取数据并存储到链表
    const char *filename = "Suppliers.txt"; // 假设数据文件为Suppliers.txt
    if (ReadDataFromFile(supplierList, filename) == -1)
    {
        return 1; // 如果读取文件失败，退出程序
    }

    // 输出链表中的数据
    printf("商家数据：\n");
    printList(supplierList);

    // 按价格排序
    SortByPrice(supplierList);

    // 根据用户调查结果推荐商家
    Recommend(supplierList);

    // 释放链表内存
    freeList(supplierList);

    return 0;
}