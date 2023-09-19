#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Data // ��������� ����� � ���������� ������
{
    Data();
    int weight, kgTNT, loadFactor, maxLoadFactor;
    char colour[8];
};

struct HashNode // ��������� ��� ��������� ����� � ��������
{
    long long key;
    Data value;
    HashNode* next = nullptr;
};

struct LinkedList // ��������� ������'������ ������
{
    LinkedList();
    ~LinkedList();
    HashNode* head;
    HashNode* tail;
    int count;

    void push_back(long long key, Data obj); // ��������� �������� � �����

    void remove(int id); // ��������� ������� ��������
};
#endif 
