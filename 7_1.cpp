#include <iostream>
#include <vector>
using namespace std;

struct tree{
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x){
    tree *n = new tree;
    n->inf = x;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

void preorder (tree *tr){ // прямой обход (К-Л-П)
    if (tr){
        cout << tr->inf << " "; //корень
        preorder(tr->left); //левое
        preorder(tr->right); //правое
    } 
}

void preorderv(tree* tr, vector<int>& result) {
    if (tr) {
        result.push_back(tr->inf);  // Записываем значение в вектор
        preorderv(tr->left, result);
        preorderv(tr->right, result);
    }
}

void postorder (tree *tr){ // обратный обход (Л-П-К)
    if (tr){
        postorder(tr->left); //левое
        postorder(tr->right); //правое
        cout << tr->inf << " "; //корень
    }
}
    
void inorder (tree *tr){ // симметричный обход (Л-К-П)
    if (tr){
        inorder(tr->left); //левое
        cout << tr->inf << " "; //корень
        inorder(tr->right); //правое
    }
    
}

void insert(tree *&tr, int x) { //вставка
    tree *n = node(x);
    if (!tr) tr = n; //если дерево пустое- корень
    else {
        tree *y = tr;
        while(y){ //ищем куда вставлять
            if (n->inf > y->inf) //правая ветка
                if (y->right)
                    y = y->right;
                else{
                    n->parent = y; //узел становится правым ребенком
                    y->right = n;
                    break;
                }
            else if (n->inf < y->inf)//левая ветка
                if (y->left)
                    y = y->left;
                else{
                    n->parent = y;//узел становится левым ребенком
                    y->left = n;
                    break;
                }
        }
    }
}

int main(){
    int n, x, uz;
    cout << "n="; cin >> n;
    tree *tr = NULL;
    for(int i = 0; i < n; i++){
        cin >> x;
        insert(tr, x);
    }
    return 0;
}
