#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace std;
ifstream in("input1.txt");

struct date{
    int dd, mm, yy;
};

struct people {
    string name;
    string post;
    date DateOfBirth;
    int exp;
    int salary; 
};

struct list {
    people inf;
    list *next;
    list *prev;
};

void push (list *&h, list *&t, people x){ //������� �������� � ����� ������
    list *r = new list{x, nullptr, nullptr}; //������� ����� �������
    r->inf = x;
    r->next = NULL; //������ ���������
    if (!h && !t){ //���� ������ ����
        r->prev = NULL;  //������ �������
        h = r;  //��� ������
    }
    else{
        t->next = r; //r- ��������� ��� ������
        r->prev = t; //�����- ���������� ��� r
    }
    t = r; //r ������ �����
}

void del_node(list *&h, list *&t, list *r){ //������� ����� r
    if(r == h && r == t) //������������ ������� ������
        h = t = NULL;
    else if(r == h){ //������� ������ ������
        h = h->next; //�������� ������
        h->prev = NULL;
    }
    
    else if (r == t){ //������� ����� ������
        t = t->prev; //�������� �����
        t->next = NULL;
    }
    else{
        r->next->prev = r->prev; //��� ����-�� �� r ����. ����-�� r->prev
    }
    delete r; //������� r
}

date Str_to_Date(string str) {
    date x;
    string temp=str.substr(0, 2);
    x.dd = atoi(temp.c_str());
    temp = str.substr(3, 2);
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4);
    x.yy = atoi(temp.c_str());
    return x;
}

vector<people> inFile() {
    vector<people> x;
    people temp;
    while(in.peek() != EOF) {
        in >> temp.name;
        in >> temp.post;
        string tmp;
        in >> tmp;
        temp.DateOfBirth = Str_to_Date(tmp);
        in >> temp.exp;
        in >> temp.salary;
        x.push_back(temp);
    }
    return x;
}

list** create_hashtable(vector<people>& vec, int m) {
    list** table = new list*[m];
    for (int i = 0; i < m; ++i) {
        table[i] = nullptr;
    }
     for (people person : vec) {
        int index = person.exp % m;
        if (index >= 0 && index < m) {
            list* head = table[index];
            list* tail = table[index];
            while (tail && tail->next) {
                tail = tail->next;
            }
            push(head, tail, person);
            table[index] = head;
        }
    }
    return table;
}

void print_pep(people x) {
    cout << x.name << " " << x.post << " " 
    << x.DateOfBirth.dd << "." << x.DateOfBirth.mm << "." << x.DateOfBirth.yy << " "
    << x.exp << " " << x.salary << endl;
}

void printHashTable(list** mas, int M) {
    for (int i = 0; i < M; ++i) {
        cout << i << ": " << endl;
        list* current = mas[i];
        while (current) {
            print_pep(current->inf);
            current = current->next;
        }
        cout << endl;
    }
}

void hash_search(list**& mas, int m, int d) {
    list* current = mas[d%m];
    bool ok = false;
    while (current) {
        if (current->inf.exp == d){
            print_pep(current->inf);
            ok = true;
        }
        current = current->next;
    } 
    if (ok == false) cout << "�� �������\n";
}

void hash_p(list** mas, int m, people x) {
    int index = x.exp % m;
    list*& head = mas[index];
    list* tail = head;
    while (tail && tail->next) {
        tail = tail->next;
    }
    push(head, tail, x);
}


void hash_del_el(list** table, int m, int d) {
    int index = d % m;
    list* current = table[index];
    while (current) {
        list* next_node = current->next;
        if (current->inf.exp == d) {
            list* head = table[index];
            list* tail = head;
            while (tail && tail->next) {
                tail = tail->next;
            }
            del_node(head, tail, current);
            table[index] = head;
        }
        current = next_node;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<people> vec = inFile();
    int m;
    cout << "M: "; cin >> m;
    list** mas = create_hashtable(vec, m);
    printHashTable(mas, m);
    cout << "����� �� ������ 15 ���:" << endl;
    hash_search(mas, m, 15);
    cout << "�������� �� ������ 20 ���:" << endl;
    hash_del_el(mas, m, 20);
    printHashTable(mas, m);
    people temp;
    cin >> temp.name;
    cin >> temp.post;
    string tmp;
    cin >> tmp;
    temp.DateOfBirth = Str_to_Date(tmp);
    cin >> temp.exp;
    cin >> temp.salary;
    hash_p(mas, m, temp);
    printHashTable(mas, m);
    return 0;
}
