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

void LinkedList::push_back(long long key, Data obj) // ��������� �������� � �����
{
    HashNode* node = new HashNode; // ��������� ������ �����
    node->value = obj;
    node->next = nullptr; // ��������� ��������� ����� ������
    node->key = key;

    if (tail != nullptr) // ���� ������ ��� �� ������
        tail->next = node; // ��������� ��������� ������ ��������������� �������� ������

    tail = node; // ��������� ��������� ������ ���������� �������� ������

    if (head == nullptr) // ���� ������ ��� ������
        head = tail;

    count++;
}

void LinkedList::remove(int id) // ��������� ������� ��������
{
        HashNode* before = head; // ��������� �����, �� �� ����������� ����� ���������� �����
        count--;

        if (id == 1) // ���� ����������� ������ �������
        {
            head = head->next;
            delete before;
            return;
        }

        for (int i = 1; i < (id - 1); i++) // ����� ��������� ��������
            before = before->next;

        HashNode* nodeObj = before->next; // ���������� ��������, �� ���� ���������
        before->next = nodeObj->next;
        if (nodeObj == tail) // ���� ������� ��� �������
            tail = before;
        delete nodeObj;
}