#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
ifstream in("input1.txt");

struct date {
    int dd, mm, yy;
};

struct people {
    string name;
    string post;
    date DateOfBirth;
    int exp;
    int salary;
};

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
    while(in >> temp.name >> temp.post) {
        string tmp;
        in >> tmp;
        temp.DateOfBirth = Str_to_Date(tmp);
        in >> temp.exp >> temp.salary;
        x.push_back(temp);
    }
    return x;
}

people** create_hashtable(vector<people>& vec, int m) {
    people** table = new people*[m]();
    for (people& person : vec) {
        int x = person.exp;
        int h1 = x % m;
        int h2 = 1 + (x % (m - 1));
        
        for (int i = 0; i < m; ++i) {
            int index = (h1 + i * h2) % m;
            
            if (table[index] == nullptr) {
                table[index] = new people(person);
                break;
            }
        }
    }
    return table;
}

void print_pep(people* p) {
    if (p) {
        cout << p->name << " " << p->post << " " 
             << p->DateOfBirth.dd << "." << p->DateOfBirth.mm << "." << p->DateOfBirth.yy << " "
             << p->exp << " " << p->salary;
    }
}

void printHashTable(people** mas, int M) {
    for (int i = 0; i < M; ++i) {
        cout << i << " ";
        if (mas[i]) {
            print_pep(mas[i]);
        } else {
            cout << "NULL";
        }
        cout << endl;
    }
}

void hash_search(people** mas, int m, int d) {
    int h1 = d % m;
    int h2 = 1 + (d % (m - 1));
    for (int i = 0; i < m; ++i) {
        int index = (h1 + i * h2) % m;
        if (mas[index] && mas[index]->exp == d) {
            print_pep(mas[index]);
            return;
        }
        if (!mas[index]) {
            break;
        }
    }
    cout << "�� �������" << endl;
}

void hash_p(people** table, int m, const people& person) {
    int x = person.exp;
    int h1 = x % m;
    int h2 = 1 + (x % (m - 1));
    for (int i = 0; i < m; ++i) {
        int index = (h1 + i * h2) % m;
        if (table[index] == nullptr) {
            table[index] = new people(person);
            break;
        }
    }
    cout << "�� ������� �������� ������� - ������� �����������" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<people> vec = inFile();
    int m;
    cout << "M: "; cin >> m;
    people** mas = create_hashtable(vec, m);
    printHashTable(mas, m);
    cout << "����� �� ������ 15 ���:" << endl;
    hash_search(mas, m, 15);
    cout << endl;
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
