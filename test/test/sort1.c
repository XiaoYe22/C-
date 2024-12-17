#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} node;

// 生成一个节点
node *initList(void)
{
    node *new = malloc(sizeof(node));

    if (!new)
    {
        printf("malloc fail!\n");
        return NULL;
    }

    new->data = 0;
    new->prev = new;
    new->next = new;

    return new;
}

// 头插法插入一个节点
void head_insert(node *head, node *new)
{
    new->next = head->next;
    head->next->prev = new;
    head->next = new;
    new->prev = head;
}
// 尾插法插入一个节点
void tail_insert(node *head, node *new)
{
    new->prev = head->prev;
    head->prev->next = new;
    new->next = head;
    head->prev = new;
}

// 弹出一个节点
void Remove(node *new)
{
    new->prev->next = new->next;
    new->next->prev = new->prev;
    new->next = new;
    new->prev = new;
}
// 遍历
void traverse(node *head)
{
    for (node *p = head->next; p != head; p = p->next)
    {
        printf("%d ", p->data);
    }

    printf("\n");
}

// 选择排序
void choose_sort(node *head)
{
    // 头结点是空的或者表是空的或者表只有一个节点时候不用排
    if (!head || head->next == head || head->next->next == head)
    {
        return;
    }

    node *p, *min, *tail;

    // tail及tail前面是排好序的，每次从tail后面选出一个最小值，插入到tail前面，直到等于head结束
    for (tail = head; tail->next != head; tail = tail->next)
    {
        // 从tail->next->next开始，到等于head时结束，与tail->next比较找出最小值min
        for (min = tail->next, p = min->next; tail != head, p != head; p = p->next)
        {
            if (min->data > p->data) // 找到一个比min更小的，就记录
            {
                min = p; // 由于是双向循环链表不需要记录min的前驱节点
            }
        }

        printf("本轮排序选择出的最小值： %d\n", min->data);

        if (min != tail->next) // 如果tail->next本来就是本轮的最小值，则不用交换
        {
            /*弹出min节点
            min->prev->next = min->next;
            min->next->prev = min->prev; */
            Remove(min);

            /*尾插法插到tail后面
            min->prev = tail;
            min->next = tail->next;
            tail->next->prev = min;
            tail->next = min;*/
            head_insert(tail, min);
        }

        traverse(head); // 显示每一轮排序结果
    }
}

// 冒泡排序
void bubble_sort(node *head)
{
    int flag;
    node *p, *tmp, *tail;
    tail = head; // tail以及tail后面的是排好序的元素，第一次还没有排好，所以为head

    while (1)
    {
        flag = 1; // flag用来标志是否已经排好序
        // 每次从head->next开始遍历，直到tail结束, prev是p的前驱节点
        for (p = head->next; p && p->next != tail;)
        {
            // 交换后，p已经移动到后面，不需要再遍历下一个
            if (p->data > p->next->data)
            {
                flag = 0;      // 修改flag=0，标志本轮循环交换过
                tmp = p->next; // 在弹出p节点前需先记录p->next节点

                /*弹出p节点
                p->prev->next = p->next;
                p->next->prev = p->prev;*/
                Remove(p);

                /*插入p节点
                p->next = tmp->next;
                tmp->next->prev = p;
                p->prev = tmp;
                tmp->next = p;*/
                head_insert(tmp, p);
            }
            else // 没有交换就继续遍历下一个
            {
                p = p->next;
            }
        }
        printf("本轮排序移动出的最大值：%d\n", p->data);
        traverse(head);
        // 显示每一轮排序结果

        if (flag) // 如果内层循环中都没有交换过，则所有节点都已经是排好序的
        {
            printf("冒泡排序结束！\n");
            break;
        }
        tail = p; // tail向前移一个，tail以及tail后面的是排好序的元素
    }
}

// 插入排序，最优版本
void insert_sort(node *head)
{
    // 头结点是空的或者表是空的或者表只有一个节点时候不用排
    if (!head || head->next == head || head->next->next == head)
    {
        return;
    }

    node *p, *q, *tail;

    // head->next->next开始遍历，tail及tail前面的是排好序的，p是本轮待插入值，等于head时结束
    for (tail = head->next, p = tail->next; p != head; p = tail->next)
    {
        // 从head->next开始遍历，直到tail结束
        for (q = head; q != tail; q = q->next)
        {
            if (p->data < q->next->data) // 插入后结束本次遍历
            {
                /*弹出p节点
                tail->next = p->next;
                p->next->prev = tail; */
                Remove(p);

                /*把p节点插入到q->next前面,即q的后面
                p->next = q->next;
                q->next->prev = p;
                q->next = p
                p->prev = q;*/
                head_insert(q, p);
                break;
            }
        }
        printf("本轮排序插入值：%d, ", p->data);
        if (tail == q) // 在tail前面没有插入，就下移
        {
            printf("已处于插入位置\n");
            tail = tail->next;
        }
        else
        {
            // p已经处于插入位置，显示时要用p->next->data
            printf("插入到%d的前面\n", p->next->data);
        }

        traverse(head); // 显示每一轮排序结果
    }
}

// 快速排序的一次划分，第一种版本
node *partition(node *head, node *tail)
{
    node *p, *basic, *tmp;

    // 从baisc后面开始遍历，找到比baisc小的就插入到head后面，直到tail结束，prev是p的前驱节点
    // 这里head可以理解为本次待划分的链表的头结点，tail是链表的最后一个节点的下一个(NULL)
    for (basic = head->next, p = basic->next; p != tail; p = p->next)
    {
        if (p->data < basic->data)
        {
            // 保留p->prev的位置, 交换后p要复位
            tmp = p->prev;

            /*弹出p节点
            p->next->prev = p->prev;
            p->prev->next = p->next;*/
            Remove(p);

            /*p节点插入到head后
            p->next = head->next;
            head->next->prev = p;
            p->prev = head;
            head->next = p;*/
            head_insert(head, p);

            // p复位
            p = tmp;
        }
    }

    return basic;
}

// 快速排序，第一种版本
void quick_sort(node *head, node *tail)
{
    // 头结点是空的或者表是空的或者表只有一个节点时候不用排
    // tail是链表的结束点，一开始等于head,后面等于basic
    if (!head || head->next == tail || head->next->next == tail)
    {
        return;
    }
    // baisc前的节点都比basic小，baisc后的节点都比baisc大
    node *basic = partition(head, tail);
    printf("本次划分节点：%d\n", basic->data);

    quick_sort(head, basic); // 把head->next到basic前一个进行递归排序
    quick_sort(basic, tail); // 从basic->next到tail前一个进行递归排序
}

// 交换两节点，p, q互换
void swap(node *p, node *q)
{
    if (p->data == q->data)
    {
        return;
    }

    node *tmp = p->prev; // 记录p的前驱节点

    Remove(p);         // 弹出p节点
    head_insert(q, p); // 把p插入到q后面

    Remove(q);           // 弹出q节点
    head_insert(tmp, q); // 把q插入到tmp后面
}

// 快速排序的一次划分，第二种版本
node *partition2(node *head, node *tail)
{
    node *p, *q, *tmp;

    p = head->next; // 这里head可以理解为本次待划分的链表的头结点
    q = tail->prev; // 这里tail是链表的最后一个节点的后面，可以理解为NULL

    // 区间长度等于零时结束
    // 特别说明，内层循环中判断条件中，有且仅有一个内层循环要加“<=”号，二选一
    // 内层循环只能是两个，如果是一个的话，会出错，举例：12 34 78 56 23 99 34 12 45 76
    while (p != q)
    {
        // 从后面开始往前遍历，直到p==q或者p->data大于等于q->data
        while (p != q && p->data < q->data)
        {
            q = q->prev;
        }

        if (p == q) // 如果p->data 都小于q->data，表示已经排好
        {
            break;
        }

        tmp = p->prev; // 交换前先保留p->prev，用来复位p 和 q
        swap(p, q);    // 交换p和q
        q = p;         // q复位
        p = tmp->next; // p复位

        // 从前面开始往后遍历，直到p==q或者p->data大于q->data
        while (p != q && p->data <= q->data)
        {
            p = p->next;
        }

        if (p == q) // 如果p->data 都小于q->data，表示已经排好
        {
            break;
        }

        tmp = p->prev; // 交换前先保留p->prev，用来复位p 和 q
        swap(p, q);    // 交换p和q
        q = p;         // q复位
        p = tmp->next; // p复位
    }

    return p;
}

// 快速排序，第二种种版本
void quick_sort2(node *head, node *tail)
{
    // 头结点是空的或者表是空的或者表只有一个节点时候不用排
    // tail是链表的结束点，一开始等于head,后面等于basic
    if (!head || head->next == tail || head->next->next == tail)
    {
        return;
    }
    // baisc前的节点都比basic小，baisc后的节点都比baisc大
    node *basic = partition2(head, tail);
    printf("本次划分节点：%d\n", basic->data);

    quick_sort2(head, basic); // 把head->next到basic前一个进行递归排序
    quick_sort2(basic, tail); // 从basic->next到tail前一个进行递归排序
}

int main(void)
{
    int i, len;
    node *head, *new, *p, *q;

    printf("请输入双向循环链表的长度: ");
    scanf("%d", &len);

    head = initList();
    head->data = len;

    printf("请输入元素：");
    for (int i = 0; i < len; i++)
    {
        new = initList();
        scanf("%d", &new->data);
        tail_insert(head, new);
    }

    printf("请选择排序方式，1.选择排序 2.冒泡排序 3.插入排序 4.快速排序: ");
    scanf("%d", &i);

    printf("排序前:\n");
    traverse(head);
    switch (i)
    {
    case 1:
        choose_sort(head);
        break;

    case 2:
        bubble_sort(head);
        break;

    case 3:
        insert_sort(head);
        break;

    case 4:
        quick_sort2(head, head);
        break;
    }

    printf("由小到大排序后:\n");
    traverse(head);

    return 0;
}