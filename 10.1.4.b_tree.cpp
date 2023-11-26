/*
    Task: Реализация сбалансированного бинарного дерева АБЛ
    добавлен пересчет высот всех узлов авто при добавлении - работает
    динамический расчет height эксперимент - работает
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node 
{
    int data;
    // int height;
    struct node *left;
    struct node *right;
};

class ABL
{
private:
    
public:
    struct node* root;
    ABL()
    {
        this->root = NULL;
    }

    int calh_rec(struct node *p) //рекурсивный расчет высоты
    {
        if(p == NULL) return 0;
        int l{0}, r{0};
        if(p->left == NULL && p->right == NULL) return 1;
        if(p->left != NULL) l = calh_rec(p->left);
        if(p->right != NULL) r = calh_rec(p->right);
        return ((l>r)?l:r) + 1;
    }

    int bf(struct node *n)  // balance factor
    {
        int l {0};
        int r {0};
        if(n->left && n->right)
        {
            l = calh_rec(n->left);
            r = calh_rec(n->right);
            return l - r; 
        }
        else if(n->left && n->right == NULL)
        {
            l = calh_rec(n->left);
            return l; 
        }
        else if(n->left== NULL && n->right )
        {
            r = calh_rec(n->right);
            return -r;
        }
        return 0;
    }

    struct node* llrotation(struct node *n)
    {
        struct node *p;
        struct node *tp;
        p = n;
        tp = p->left;

        p->left = tp->right;
        tp->right = p;

        return tp; 
    }


    struct node* rrrotation(struct node *n)
    {
        struct node *p;
        struct node *tp;
        p = n;
        tp = p->right;

        p->right = tp->left;
        tp->left = p;

        return tp; 
    }


    struct node* rlrotation(struct node *n)
    {
        struct node *p;
        struct node *tp;
        struct node *tp2;
        p = n;
        tp = p->right;
        tp2 =p->right->left;

        p -> right = tp2->left;
        tp ->left = tp2->right;
        tp2 ->left = p;
        tp2->right = tp; 
        
        return tp2; 
    }

    struct node* lrrotation(struct node *n)
    {
        struct node *p;
        struct node *tp;
        struct node *tp2;
        p = n;
        tp = p->left;
        tp2 =p->left->right;

        p -> left = tp2->right;
        tp ->right = tp2->left;
        tp2 ->right = p;
        tp2->left = tp; 
        
        return tp2; 
    }

    struct node* insert(struct node *r,int data)
    {
        if(r==NULL)
        {
            struct node *n;
            n = new struct node;
            n->data = data;
            r = n;
            r->left = r->right = NULL;
            // r->height = 1; 
            return r;
        } else {
            if(data < r->data)
                r->left = insert(r->left,data);
            else
                r->right = insert(r->right,data);
        }
        
        // r->height = calheight(r);
        // cout << r->data << " " << "\n";

        if(bf(r)==2 && bf(r->left)==1)
        {
            r = llrotation(r);
        } else if(bf(r)==-2 && bf(r->right)==-1)
        {
            r = rrrotation(r);
        } else if(bf(r)==-2 && bf(r->right)==1)
        {
            r = rlrotation(r);
        } else if(bf(r)==2 && bf(r->left)==-1)
        {
            r = lrrotation(r);
        }

        // if(root == r && r != NULL) update_h(r);
        return r;
    }

    void levelorder_newline()
    {
        if (this->root == NULL)
        {
            cout<<"\n"<<"Дерево пусто"<<"\n";
            return;            
        }
        levelorder_newline(this->root);
    }

    void levelorder_newline(struct node *v) // обход в ширину
    { 
        queue <struct node *> q;
        struct node *cur;
        q.push(v);
        q.push(NULL);      

        while(!q.empty())
        {
            cur = q.front(); //получили
            q.pop(); // удалили
            if(cur == NULL && q.size()!=0)
            {
                cout<<"\n";
                
                q.push(NULL);
                continue;
            }
            if(cur!=NULL)
            {
                cout<<" "<<cur->data;

                if (cur->left!=NULL)
                {
                    q.push(cur->left);
                }
                if (cur->right!=NULL)
                {
                    q.push(cur->right);
                }
            }
        }
    }
    struct node* search(struct node* node, int data, int& h) 
    {
        h = 0;
        if(node == NULL || node->data == data) 
        {
            h = calh_rec(node);
            return node;
        }
        if(data < node->data) return search(node->left, data, h);
        else return search(node->right, data, h);
    }
    ~ABL(){

    }
};


int main(){

    ABL b;
    int c, x, xx;
    int h, hh;
    struct node* s;

    vector <int> t {350,200,400,100,300}; //350,200,400,100,300 вводим 160 LL поворот + 100


    while(true)
    {
        cout << "\n1.Показать граф";
        cout << "\n2.Вставить элемент";
        cout << "\n3.Найти элемент";
        cout << "\n4.Очистить граф";
        cout << "\n5.Вставить граф программно";
        cout << "\n6.Выход\n";
        cout << "\nВыбор: ";

        cin >> c;

        switch (c)
        {
            case 1: 
                b.levelorder_newline();
                // cout << b.calh_rec(b.root) << "\n";
                break;
            case 2:
                cout<<"\nВведите данные(ключ): ";
                cin>>x;
                s = b.search(b.root, x , h);
                if(s != NULL)
                {
                    cout << "Такая вершина уже есть" << "\n";
                    continue;
                }
                b.root = b.insert(b.root,x);
                break;
            case 3: 
                cout << "\nКакой ищем: ";
                cin >> xx;
                s = b.search(b.root, xx, hh);
                if(s != NULL) cout << s->data << " " << hh << "\n";
                else cout << "Таково нет" << "\n";
                break;
            case 4:
                b.root = NULL;
                break;
            case 5:
                for(int i = 0; i < t.size(); i++)
                    b.root = b.insert(b.root, t[i]);
                break;
            case 6:
                exit(EXIT_SUCCESS);
        }
    }
    return 0;
}