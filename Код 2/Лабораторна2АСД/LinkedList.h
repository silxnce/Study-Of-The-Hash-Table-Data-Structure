#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Data // Структура Бомба з відповідними даними
{
    Data();
    int weight, kgTNT, loadFactor, maxLoadFactor;
    char colour[8];
};

struct HashNode // Структура для зберігання ключа і значення
{
    long long key;
    Data value;
    HashNode* next = nullptr;
};

struct LinkedList // Структура однозв'язного списку
{
    LinkedList();
    ~LinkedList();
    HashNode* head;
    HashNode* tail;
    int count;

    void push_back(long long key, Data obj); // Додавання елементу в кінець

    void remove(int id); // Видалення певного елементу
};
#endif 
