#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#define LEN 2

/*
 1. конструктор по умолчанию нужен для того, чтобы создать массив объектов, указать, что строки в нашем объекте пусты
 2. перегрузка оператора < необходима, чтобы сравнивать объекты класса в qsort
 3. readName необходим для чтения имени
 4. readAddress нужен для чтения адреса
 5. и перегрузка вывода, для вывода результатов сортировки в поток
 6. копирующий конструктор не нужен, т.к. вся наша информация хранится в массивах, для которых память выделяется автоматически, поэтому происходит поверхностное побитовое копирование каждой строки
 7. если в private было бы char *name и char *address, то был бы нужен копирующий конструктор, когда мы объявляем SType объект и сразу же присваиваем ему значение, деструктор
 */

using namespace std;

class humanity {
public:
    humanity();                                                   // конструктор по умолчанию
    //humanity(const char *x) { strcpy(name, x); strcpy(address, x); }
    int operator <(humanity &a);                                  // меньше
    void readName(char *nm);                                      // добавить имя
    void readAddress(char *adr);                                  // добавить адресс
    friend ostream &operator <<(ostream &out, const humanity &a); // вывод в поток
    
private:
    char name[LEN], address[LEN];
};

humanity::humanity() { // конструктор по умолчанию
    name[0] = 0;
    address[0] = 0;
}

int humanity::operator <(humanity &a) { // меньше
    assert(this != NULL && &a != NULL);
    
    if (strcmp(a.name, name) > 0)
        return 1;
    return 0;
}

void humanity::readName(char *nm) { // добавить имя
    assert(strlen(nm) <= LEN);
    strcpy(name, nm);
}

void humanity::readAddress(char *adr) { // добавить адресс
    assert(strlen(adr) <= LEN);
    strcpy(address, adr);
}

ostream &operator <<(ostream &out, const humanity &a) { // вывод в поток
    out << a.name << " " << a.address << " ";
    return out;
}

template <class CType> void swap(CType *a, CType *b) { // поменять a и b местами
    CType temp = *a;
    *a = *b;
    *b = temp;
}

template <class SType> void qsort(SType *item, int left, int right) { // сортировать массив объектов item в границах left и right
    int i = left, j = right;
    SType x = item[(left + right) / 2], y;
    
    do {
        while (item[i] < x && i < right)
            i++;
        while (x < item[j] && j > left)
            j--;
        
        if (i <= j) {
            y = item[i];
            item[i] = item[j];
            item[j] = y;
            i++;
            j--;
        }
    } while (i <= j);
    
    if (left < j)
        qsort(item, left, j);
    if (i < right)
        qsort(item, i, right);
}

template <class SType> void print(SType *item, int size) { // вывод массива item
    int i = 0;
    for (; i < size; i++)
        cout << item[i] << " ";
    cout << endl;
}

int main() {
    char s[LEN];
    char adr[LEN] = { 'C' };
    
    humanity x[6];
    
    for (int i = 0; i < 6; i++) {
        cin >> s;
        x[i].readName(s);
        x[i].readAddress(adr);
    }
    
    print(x, 6);
    
    qsort(x, 0, 5);
    
    print(x, 6);
    
    system("pause");
}
