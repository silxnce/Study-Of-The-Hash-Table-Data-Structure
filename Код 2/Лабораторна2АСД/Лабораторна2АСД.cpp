#include <iostream>
#include <unordered_map>
#include "LinkedList.h"

using namespace std;

struct HashTable // Структура Хеш-таблиці
{
    int arrSize, currSize;
    float loadFactor, maxLoadFactor;
    LinkedList* bucketsArray;

    HashTable(int sizeNum = 1000, float loadFacNum = 0.5) // Конструктор
    {
        arrSize = sizeNum; // Розмір динамічного масиву 
        currSize = 0; // Кількість елементів в хеш-таблиці
        bucketsArray = new LinkedList[arrSize]; // Виділення пам'яті під динамічний масив
        maxLoadFactor = loadFacNum; // Максимальний коефіцієнт, після якого відбувається перевиділення
        loadFactor = 0; // Коефіцієнт завантаженості хеш-таблиці
    }

    ~HashTable() // Деструктор
    {
        delete[] bucketsArray;
    }

    int hash(long long key) // Хеш-функція
    {
        return key % arrSize;
    }

    void insert(long long key, Data obj) // Додавання елементу під відповідним ключем (заміна у випадку існування ключа)
    {
        int id = hash(key);
        if (bucketsArray[id].head) // Якщо в комірці є елементи
        {
            HashNode* nodeObj = bucketsArray[id].head;
            while (nodeObj) // Цикл перевірки однозв'язного списку на існування елементу з тим самим ключем
            {
                if (nodeObj->key == key) // Якщо існує, відбувається заміна значення
                {
                    nodeObj->value = obj;
                    return;
                }
                nodeObj = nodeObj->next;
            }
        }
        bucketsArray[id].push_back(key, obj); // Якщо елементу з таким ключем немає, додаємо 
        currSize++;
        loadFactor = currSize / arrSize; // Обчислення коефіцієнту завантаженості
        if (loadFactor >= maxLoadFactor) // Якщо хеш-таблиця перевантажена, перевиділяємо пам'ять
            relocMem();
    }

    HashNode* find(long long key) // Метод для знаходження елементу під відповідним ключем
    {
        int id = hash(key);
        HashNode* nodeObj = bucketsArray[id].head;
        while (nodeObj && nodeObj->key != key) // Цикл проходження по однозв'язному списку
            nodeObj = nodeObj->next;
        return nodeObj; // Якщо елемент знайдено, повертається вказівник, якщо ні - повертається nullptr
    }

    void erase(long long key) // Метод видалення елементу під відповідним ключем
    {
        int id = hash(key), i = 1; // i - індекс елементу в однозв'язному списку, який буде видалено
        HashNode* nodeObj = bucketsArray[id].head;
        while (nodeObj) // Цикл проходження по однозв'язному списку
        {
            if (nodeObj->key == key) // Якщо елемент знайдено
            {
                bucketsArray[id].remove(i);
                currSize--;
                loadFactor = currSize / arrSize; // Обчислення коефіцієнту завантаженості
                return;
            }
            nodeObj = nodeObj->next;
            i++;
        }
    }

    int size() // Метод, що повертає кількість елементів в хеш-таблиці
    {
        return currSize;
    }

    void relocMem() // Перевиділення пам'яті
    {
        arrSize *= 2;
        LinkedList* newArray = new LinkedList[arrSize]; // Виділення більшої кількості пам'яті

        for (int i = 0; i < (arrSize / 2); i++) // Цикл перенесення всіх елементів у комірки під новими індексами
        {
            if (bucketsArray[i].head)
            {
                HashNode* nodeObj = bucketsArray[i].head;
                while (nodeObj)
                {
                    int id = hash(nodeObj->key);
                    newArray[id].push_back(nodeObj->key, nodeObj->value);
                    nodeObj = nodeObj->next;
                }
            }
        }

        delete[] bucketsArray; // Видалення старого масиву
        bucketsArray = newArray; // Зміна масиву, з яким пов'язаний вказівник
    }
};

long long generateRandLong() // Функція генерації довгого числа
{
    long long num = 0;
    int maxLen = rand() % 12 + 1;

    for (int i = 0; i < maxLen; i++)
        num += (rand() % 10) * pow(10, i);
    return num;
}

bool testHashTable() // Функція тестування хеш-таблиці
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
    // generate random keys:
    long long* keys = new long long[keysAmount];
    long long* keysToInsert = new long long[iters];
    long long* keysToErase = new long long[iters];
    long long* keysToFind = new long long[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = generateRandLong();
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[generateRandLong() % keysAmount];
        keysToErase[i] = keys[generateRandLong() % keysAmount];
        keysToFind[i] = keys[generateRandLong() % keysAmount];
    }
    // test my HashTable:
    HashTable hashTable;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++) {
        hashTable.insert(keysToInsert[i], Data());
    }
    int myInsertSize = hashTable.size();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
    int myEraseSize = hashTable.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.find(keysToFind[i]) != NULL)
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    // test STL hash table:
    unordered_map<long long, Data> unorderedMap;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({ keysToInsert[i], Data() });
    }
    int stlInsertSize = unorderedMap.size();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }
    int stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTime << " , after insert: " << myInsertSize << " , after erase:" << myEraseSize << ", found: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << " , after insert: " << stlInsertSize << " , after erase:" << stlEraseSize << ", found: " << stlFoundAmount << endl << endl;
    delete[] keys;
    delete[] keysToInsert;
    delete[] keysToErase;
    delete[] keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount ==
        stlFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }cerr << ":(" << endl;
    return false;
}

int main()
{
    srand(time(NULL));
    testHashTable();
}
