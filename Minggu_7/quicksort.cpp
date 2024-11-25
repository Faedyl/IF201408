#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;

struct Node 
{
    int data;
    struct Node* next;
};
int per = 0;
void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = new Node;
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node)
{
    while (node != NULL) 
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

struct Node* getTail(struct Node* cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

struct Node* partition(struct Node* head, struct Node* end, struct Node** newHead, struct Node** newEnd)
{
    struct Node* pivot = end;
    struct Node *prev = NULL, *cur = head, *tail = pivot;

    cout << "Partitioning around pivot: " << pivot->data << endl;
    cout << "Before partition: ";
    printList(head);

    while (cur != pivot) 
    {
    
        if (cur->data < pivot->data) 
        {
            per++;
            if ((*newHead) == NULL)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
            
        }
        else
        {
            per++;
            if (prev)
                prev->next = cur->next;
            struct Node* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
            
        }
        
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;

    (*newEnd) = tail;
    cout << "Perulangan ke - " << per << endl;
    cout << "After partition: ";
    printList(*newHead);
    cout << endl;

    return pivot;
}

struct Node* quickSortRecur(struct Node* head, struct Node* end)
{
    if (!head || head == end)
        return head;

    cout << "Current sublist: ";
    printList(head);

    Node *newHead = NULL, *newEnd = NULL;

    struct Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        struct Node* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    cout << "Sorted sublist: ";
    printList(newHead);
    cout << endl;

    return newHead;
}

void quickSort(struct Node** headRef)
{
    cout << "Starting QuickSort" << endl;
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    cout << "QuickSort completed" << endl;
}

void inputData(struct Node** headRef)
{
    int n;
    cout << "Masukkan jumlah data: ";
    cin >> n;

    struct Node* tail = NULL;
    for (int i = 1 ; i <= n; i++)
    {
        int data;
        cout << "Masukkan data ke-" << i << ": ";
        cin >> data;

        if (*headRef == NULL)
        {
            *headRef = new Node;
            (*headRef)->data = data;
            (*headRef)->next = NULL;
            tail = *headRef;
        }
        else
        {
            struct Node* newNode = new Node;
            newNode->data = data;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void inputRandom(struct Node** headRef)
{
    srand(time(0));
    int n;
    cout << "Masukkan jumlah data: ";
    cin >> n;

    struct Node* tail = NULL;
    for (int i = 1; i <= n; i++)
    {
        int data = rand() % 10000;
        cout << "Data ke-" << i << ": " << data << endl;

        if (*headRef == NULL)
        {
            *headRef = new Node;
            (*headRef)->data = data;
            (*headRef)->next = NULL;
            tail = *headRef;
        }
        else
        {
            struct Node* newNode = new Node;
            newNode->data = data;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void clearData(struct Node** headRef)
{
    while (*headRef != NULL)
    {
        Node *tmp = *headRef;
        *headRef = (*headRef)->next;
        delete tmp;
    }
    cout << "Linkedlist telah dibersihkan" << endl;
}

int main()
{
    struct Node* head = NULL;

    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Manual Input" << endl;
        cout << "2. Random Input" << endl;
        cout << "3. Bersihkan List" << endl;
        cout << "4. Exit" << endl;
        cout << "Pilih menu: ";
        int pilihan;
        cin >> pilihan;

        if (pilihan == 1 || pilihan == 2)
        {
            
            
            switch (pilihan)
            {
            case 1:
            {
                inputData(&head);
                cout << "Data sebelum disort: ";
                printList(head);
                auto start = std::chrono::high_resolution_clock::now();
                quickSort(&head);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                cout << "Waktu pengurutan: " << duration.count() << " Mikrodetik" << endl;
                break;

            }
            case 2:
            {
                inputRandom(&head);
                cout << "Data sebelum disort: ";
                printList(head);
                auto start = std::chrono::high_resolution_clock::now();
                quickSort(&head);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                cout << "Waktu pengurutan: " << duration.count() << " Mikrodetik" << endl;
                break;
            }
            }

           

            cout << "Data setelah diurutkan: ";
            printList(head);
           
        }
        else if (pilihan == 3)
        {
            clearData(&head);
        }
        else if (pilihan == 4)
        {
            return 0;
        }
        else
        {
            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
        }
    }

    return 0;
}