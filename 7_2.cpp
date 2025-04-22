#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
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

tree *find(tree *tr, int x){//поиск
    if (!tr || x == tr->inf)//нашли или дошли до конца ветки
        return tr;
    if (x < tr->inf)
        return find(tr->left, x);//ищем по левой ветке
    else
        return find(tr->right, x);//ищем по правой ветке
}


void f(tree *tr){
    if (tr){
        if (tr->left && !(tr->right)){
            cout << tr->inf << " ";
        }
        f(tr->left);
        f(tr->right);
    } 
 
}

void print(tree *tr, int k){
    if(!tr) cout << "Empty tree\n";
    else{
        queue<tree*> cur, next;
        tree *r = tr;
        cur.push(r);
        int j = 0;
        while(cur.size()){
            if(j==0){
                for(int i=0; i<(int)pow(2.0,k)-1; i++)
                    cout<<" ";
            }
            tree *buf=cur.front();
            cur.pop();
            j++;
            if(buf){
                cout<<buf->inf;
                next.push(buf->left);
                next.push(buf->right);
                for(int i=0; i<(int)pow(2.0,k+1)-1; i++)
                    cout<<" ";
            }
        
            if(!buf){
                for(int i=0; i<(int)pow(2.0,k+1)-1; i++)
                    cout << " ";
                cout << " ";
            }
            if(cur.empty()){
                cout << endl;
                swap(cur,next);
                j = 0;
                k--;
            }
        }
    }    
}

int main(){
    int n, x;
    cout << "n="; cin >> n;
    tree *tr = NULL;
    for(int i = 0; i < n; i++){
        cin >> x;
        insert(tr, x);
    }
    int k = int(log((float)n)/log((float)2.0));
    print(tr, k);
    f(tr);
    return 0;
}
