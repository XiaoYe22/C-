#include <stdio.h>
#include <stdlib.h>

typedef struct tagSupplier
{
    int id;                   // 商家编号
    float price;              // 商品价格
    float score;              // 用户评分
    struct tagSupplier *next; // 链表指针
} Supplier;

// 定义链表结构
typedef struct tagSupplierList
{
    Supplier *head; // 链表头指针
} SupplierList;

void ReadDataFromFile(SupplierList *list, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    Supplier *newNode, *tail = NULL;
    while (1)
    {
        newNode = (Supplier *)malloc(sizeof(Supplier));
        if (fscanf(file, "%d %f %f", &newNode->id, &newNode->price, &newNode->score) != 3)
        {
            free(newNode);
            break;
        }
        newNode->next = NULL;
        if (list->head == NULL)
        {
            list->head = newNode;
        }
        else
        {
            tail->next = newNode;
        }
        tail = newNode;
    }

    fclose(file);

    // 输出链表数据
    Supplier *temp = list->head;
    while (temp)
    {
        printf("商家编号: %d, 商品价格: %.2f, 用户评分: %.2f\n", temp->id, temp->price, temp->score);
        temp = temp->next;
    }
}

// void SortByPrice(SupplierList *list)
// {
//     if (list->head == NULL)
//         return;
//     Supplier *i, *j;
//     for (i = list->head; i != NULL; i = i->next)
//     {
//         for (j = i->next; j != NULL; j = j->next)
//         {
//             if (i->price > j->price)
//             {
//                 // 交换数据
//                 int tempId = i->id;
//                 float tempPrice = i->price;
//                 float tempScore = i->score;
//                 i->id = j->id;
//                 i->price = j->price;
//                 i->score = j->score;
//                 j->id = tempId;
//                 j->price = tempPrice;
//                 j->score = tempScore;
//             }
//         }
//     }
/* void SortByPrice(SupplierList *list)
{
    if (list->head == NULL)
        return;

    Supplier *i, *j, *p, *temp;
    p = (Supplier *)malloc(sizeof(Supplier));
    if (p == NULL)
    {
        printf("内存分配失败\n");
        return;
    }
    p->next = list->head;

    for (i = p; i->next != NULL; i = i->next)
    {
        for (j = i->next; j->next != NULL; j = j->next)
        {
            if (i->next->price > j->next->price)
            {
                // 交换节点
                temp = j->next;
                j->next = temp->next;
                temp->next = i->next;
                i->next = temp;
            }
        }
    }

    list->head = p->next;
    free(p);

    // 输出排序后的链表数据
    Supplier *t = list->head;
    printf("\n按价格排序后的商家信息:\n");
    while (t)
    {
        printf("商家编号: %d, 商品价格: %.2f, 用户评分: %.2f\n", t->id, t->price, t->score);
        t = t->next;
    }
} */
void SortByPrice(SupplierList *list)
{
    if (list->head == NULL || list->head->next == NULL)
        return;

    Supplier *sorted = NULL; // 排好序的部分
    Supplier *current, *prev, *minNode, *minPrev;

    while (list->head != NULL)
    {
        // 每次循环从未排序部分找到最小节点
        minNode = list->head;
        minPrev = NULL;
        prev = NULL;
        current = list->head;

        while (current != NULL)
        {
            if (current->price < minNode->price)
            {
                minNode = current;
                minPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        // 从未排序部分中移除 minNode
        if (minPrev != NULL)
        {
            minPrev->next = minNode->next;
        }
        else
        {
            list->head = minNode->next; // 如果最小节点是头节点
        }

        // 将 minNode 添加到已排序部分的链表头
        minNode->next = sorted;
        sorted = minNode;
    }

    // 更新链表头为排序后的链表
    list->head = sorted;

    // 输出排序后的链表
    Supplier *temp = list->head;
    printf("\n按价格排序后的商家信息:\n");
    while (temp)
    {
        printf("商家编号: %d, 商品价格: %.2f, 用户评分: %.2f\n", temp->id, temp->price, temp->score);
        temp = temp->next;
    }
}
void Recommend(SupplierList *list)
{
    // 统计商家的数量
    int count = 0;
    Supplier *temp = list->head;
    while (temp)
    {
        count++;
        temp = temp->next;
    }

    if (count == 0)
        return;

    // 获取商家价格的中位数
    float prices[count];
    temp = list->head;
    int i = 0;
    while (temp)
    {
        prices[i++] = temp->price;
        temp = temp->next;
    }

    // 对价格数组进行排序
    for (i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (prices[i] > prices[j])
            {
                float tmp = prices[i];
                prices[i] = prices[j];
                prices[j] = tmp;
            }
        }
    }

    float medianPrice = prices[count / 2]; // 中位数

    printf("\n推荐商家列表:\n");
    temp = list->head;
    while (temp)
    {
        if (temp->price < medianPrice)
        {
            printf("商家编号: %d, 商品价格: %.2f, 用户评分: %.2f (价格较低的商家)\n", temp->id, temp->price, temp->score);
        }
        else
        {
            printf("商家编号: %d, 商品价格: %.2f, 用户评分: %.2f (评分较高的商家)\n", temp->id, temp->price, temp->score);
        }
        temp = temp->next;
    }
}

int main()
{
    SupplierList list = {NULL};
    const char *filename = "Suppliers.txt";

    // 读取文件数据并输出
    ReadDataFromFile(&list, filename);

    // 按价格排序并输出
    SortByPrice(&list);

    // 按调查结果进行推荐
    Recommend(&list);

    return 0;
}