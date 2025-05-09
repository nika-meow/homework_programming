#include <iostream>
#include <string>
#include <stack>
#include <windows.h>
#include <iomanip>
using namespace std;

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

struct tree{ 
    char inf;
    tree* right;
    tree* left ;
    tree* parent;
};

tree *node(char x){
    tree *n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

tree *create_tree(string str) { //создание дерева
    tree *tr = NULL;
    for (unsigned int i = 0; i < str.length(); i++){ //проход по строке
        tree *n = node(str[i]);
        if (str[i] == '-' || str[i] == '+'){//становится корнем
            tr->parent = n;
            n->left = tr; //имеющееся дерево становится левым
            tr = n;
        }
        else if (str[i] == '/' || str[i] == '*'){
            if (isdigit(tr->inf)) { //если первый знак операции в выражении- корень
                tr->parent = n;
                n->left = tr;
                tr = n;
            }
            else { //добавляем справа от корня
                n->parent = tr;
                n->left = tr->right;//имеющийся элемент становится левым
                tr->right->parent = n;
                tr->right = n;
            }
        }
        else{//цифра
            if (!tr) tr = n;//если первая в выражении - становится корнем
            else{//нет
                if (!tr->right) {//у корня нет правого сына, становится им
                    n->parent = tr;
                    n->left = tr->right;
                    tr->right = n;
                }
                else {//ищем операнд без правого сына
                    tree *x = tr->right;
                    while (x->right) x = x->right;
                    n->parent = x->parent;
                    x->right = n;
                }
            }
        }
    }
    return tr;
}

void postorder (tree *tr, stack<int> &a) {//обратный обход
    if(tr){
        postorder(tr->left, a);
        postorder(tr->right, a);
        if (isdigit(tr->inf)){//если узел - число, записываем в стек
            int n = tr->inf - '0';
            a.push(n);
        }
        else {//знак операции
            int b = a.top();//извлекаем 2 последних элемента стека
            a.pop();
            int c = a.top();
            a.pop();
            if (tr->inf == '+') a.push(b + c);
            if (tr->inf == '-') a.push(c - b);
            if (tr->inf == '*') a.push(b * c);
            if (tr->inf == '/') a.push(c / b);
        }
    }
}

// Префиксный обход (выводит польскую нотацию)
void prefixtr(tree* root, string& output) {
    if (!root) return;
    output += root->inf;
    output += ' ';  // для разделения элементов
    prefixtr(root->left, output);
    prefixtr(root->right, output);
}

// Постфиксный обход (выводит обратную польскую нотацию)
void postfixtr(tree* root, string& output) {
    if (!root) return;
    postfixtr(root->left, output);
    postfixtr(root->right, output);
    output += root->inf;
    output += ' ';  // для разделения элементов
}

void max_height(tree *x, short &max, short deepness = 1){
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right,max, deepness + 1);
}

void print_helper(tree *x, const COORD pos, const short offset) {
    SetConsoleCursorPosition(outp, pos);
    cout << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, {pos.X, short(pos.Y + 1)}, offset >> 1);
    if (x->right) print_helper(x->right, {short(pos.X + offset), short(pos.Y + 1)}, offset >> 1);
}

void print(tree *root = NULL) {
    if (root) {
        short max = 1;
        max_height(root, max);
        short width = 1 << max + 1, max_w = 128; 
        if (width > max_w) width = max_w;
        for (short i = 0; i < max; ++i) cout << '\n'; 
        GetConsoleScreenBufferInfo(outp, &csbInfo); 
        COORD endPos = csbInfo.dwCursorPosition;
        print_helper(root, {0, short(endPos.Y- max)}, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
        SetConsoleTextAttribute(outp, 7);
    }
}

void preorderpr(tree *tr){
    if (tr){
        cout << tr->inf; //корень
        preorderpr(tr->left); //левое
        preorderpr(tr->right); //правое
    } 
}

void postorderpr(tree *tr){ 
    if (tr){
        postorderpr(tr->left); //левое
        postorderpr(tr->right); //правое
        cout << tr->inf; //корень
    }
}

int main(){
    string str;
    cout << "str: ";
    cin >> str;
    string znak = "+-/*0123456789()";
    int n = str.length();
    bool flag = true;
    for (unsigned int i = 0; i < n; i++)
        if (znak.find_first_of(str[i]) == string::npos) {
            flag = false;
            break;
        }
    if (!flag) cout << "error";
    else {
        tree *tr = create_tree(str);//создали дерево
        print(tr);
        stack<int> a;
        postorder(tr, a); //вызвали обход
        cout << "res: " << a.top(); //в стеке один элемент - извлекаем его
        a.pop();
        cout << endl;
        cout << "prefix: ";
        preorderpr(tr);
        cout << endl;
        cout << "postfix: ";
        postorderpr(tr);
        
    }
    
    return 0;
}
