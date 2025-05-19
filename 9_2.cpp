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

int main() {
    setlocale(LC_ALL, "Russian");
    vector<people> vec = inFile();
    int m;
    cout << "M: "; cin >> m;
    people** mas = create_hashtable(vec, m);
    return 0;
}
