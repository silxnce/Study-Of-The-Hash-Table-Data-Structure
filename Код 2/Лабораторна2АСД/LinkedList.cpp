#include "LinkedList.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Data::Data()
{
    char colourArr[20][8] = { "Red", "Green", "Blue", "Yellow", "Purple", "Pink", "Orange", "Brown", "Cyan",
                "Magenta", "Lime", "Olive", "Navy", "Teal", "Maroon", "Silver", "Gold", "Black", "White", "Gray" };
    strcpy_s(colour, colourArr[rand() % 20]);
    weight = rand() % 10000;
    kgTNT = rand();
}

LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

LinkedList::~LinkedList()
{
    while (head)
    {
        HashNode* obj = head;
        head = head->next;
        delete obj;
    }
}

void LinkedList::push_back(long long key, Data obj) // Додавання елементу в кінець
{
    HashNode* node = new HashNode; // Створення нового вузлу
    node->value = obj;
    node->next = nullptr; // Присвоєння вказівнику пустої адреси
    node->key = key;

    if (tail != nullptr) // Якщо список був не пустий
        tail->next = node; // Присвоєння вказівнику адреси передостаннього елемента списку

    tail = node; // Присвоєння вказівнику адреси останнього елемента списку

    if (head == nullptr) // Якщо список був пустий
        head = tail;

    count++;
}

void LinkedList::remove(int id) // Видалення певного елементу
{
        HashNode* before = head; // Створення вузлу, що має знаходитися перед необхідним місцем
        count--;

        if (id == 1) // Якщо видаляється перший елемент
        {
            head = head->next;
            delete before;
            return;
        }

        for (int i = 1; i < (id - 1); i++) // Пошук потрібного елементу
            before = before->next;

        HashNode* nodeObj = before->next; // Визначення елементу, що буде видалений
        before->next = nodeObj->next;
        if (nodeObj == tail) // Якщо елемент був останнім
            tail = before;
        delete nodeObj;
}