#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node 
{
    int data;
    int height;
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

    int calheight(struct node *p) // пересчет снизу вверх
    {
        if(p->left && p->right)
        {
            if (p->left->height < p->right->height)
                return p->right->height + 1;
            else return  p->left->height + 1;
        }
        else if(p->left && p->right == NULL)
        {
            return p->left->height + 1;
        }
        else if(p->left ==NULL && p->right)
        {
            return p->right->height + 1;
        }
        return 0;

    }

    int bf(struct node *n)  // balance factor
    {
        if(n->left && n->right)
        {
            return n->left->height - n->right->height; 
        }
        else if(n->left && n->right == NULL)
        {
            return n->left->height; 
        }
        else if(n->left== NULL && n->right )
        {
            return -n->right->height;
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
    // void update(struct node *r)
    // {

    // }

    struct node* insert(struct node *r,int data)
    {
        if(r==NULL)
        {
            struct node *n;
            n = new struct node;
            n->data = data;
            r = n;
            r->left = r->right = NULL;
            r->height = 1; 
            return r;             
        } else {
            if(data < r->data)
                r->left = insert(r->left,data);
            else
                r->right = insert(r->right,data);
        }

        r->height = calheight(r);
        cout << r->data << " " << r->height << "\n";

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

        return r;
    }

    void levelorder_newline()
    {
        if (this->root == NULL)
        {
            cout<<"\n"<<"Empty tree"<<"\n";
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
            cur = q.front();
            q.pop();
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
    struct node* search(struct node* node, int data) 
    {
        if (node == NULL || node->data == data) return node;
        if (data < node->data) return search(node->left, data);
        else return search(node->right, data);
    }
    ~ABL(){

    }
};


int main(){

    ABL b;
    int c, x, xx;
    struct node* s;

    while(true)
    {
        cout << "\n1.Показать граф";
        cout << "\n2.Вставить";
        cout << "\n3.Найти";
        cout << "\n4.Очистить";
        cout << "\n5.вставить граф программно\n";
        cout << "\nВыбор: ";

        cin>>c;

        switch (c)
        {
            case 1: 
                b.levelorder_newline();
                break;

            case 2:
                cout<<"\nВведите данные(ключ): ";
                cin>>x;
                b.root = b.insert(b.root,x);
                // cout << b.root->data << "\n";
                // cout << b.root->height << "\n";
                break;
            case 3: 
                cout << "\nКакой ищем: ";
                cin >> xx;
                s = b.search(b.root, xx);
                if(s!=NULL) cout << s->data << " " << s->height << "\n";
                else cout << "Таково нет" << "\n";
                break;
            case 4:
                b.root = NULL;
                break;
            
            case 5:
                vector <int> t {350,200,400,100,300}; //350,200,400,100,300 вводим 160 LL поворот + 100
                for(int i = 0; i < t.size(); i++)
                    b.root = b.insert(b.root, t[i]);
                break;
        }
    }
}