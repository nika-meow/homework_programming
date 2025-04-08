#include <iostream>

using namespace std;

struct list {
    int inf;
    list *next;
    list *prev;
};

void push (list *&h, list *&t, int x){ //вставка элемента в конец списка
    list *r = new list; //создаем новый элемент
    r->inf = x;
    r->next = NULL; //всегда последний
    if (!h && !t){ //если список пуст
        r->prev = NULL;  //первый элемент
        h = r;  //это голова
    }
    else{
        t->next = r; //r- следующий для хвоста
        r->prev = t; //хвост- предыдущий для r
    }
    t = r; //r теперь хвост
}

void print (list *h, list *t){ //печать элементов списка
    list *p = h; //укзатель на голову
    while (p){  //пока не дошли до конца списка
        cout << p->inf << " ";
        p = p->next; //переход к следующему элементу
    }
}
    
int main(){

    return 0;
}
