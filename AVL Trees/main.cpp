#include <bits/stdc++.h>
using namespace std;





class Node
{
public:
    Node* left;
    int data;
    int height;
    Node* right;
};
class avl
{
    Node* root;
public:
    avl(){root=NULL;}
    Node* RInsert(Node* p,int x);
    Node* getRoot(){return root;}
    void setRoot(Node* p){root = p;}
    void InOrder(Node* p);
};

int NodeHeight(Node* p)
{
    int x,y;
    x = (p&&p->left) ? p->left->height:0;
    y = (p&&p->right)? p->right->height:0;
    return (x>y)?x+1:y+1;
}
Node* LLRotation(Node* p)
{
    Node* LRchild = p->left->right,*Lchild=p->left;
    Lchild->right = p;
    p->left = LRchild;
    return Lchild;
}
Node* LRRotation(Node* p)
{
    Node *Lchild = p->left, *LRchild = p->left->right;
    Node *LRLchild = LRchild->left, *LRRchild = LRchild->right;
    LRchild->left = Lchild;
    LRchild->right = p;
    Lchild->right = LRLchild;
    p->left = LRRchild;
    return LRchild;
}
Node* RLRotation(Node* p)
{
    Node *Rchild = p->right,*RLchild = Rchild->left,*RLRchild = RLchild->right,*RLLchild = RLchild->right;
    RLchild->left = p;
    RLchild->right = Rchild;
    Rchild->left = RLRchild;
    p->right = RLLchild;
    return RLchild;
}
Node* RRRotation(Node* p)
{
    Node *Rchild = p->right, *RLchild = Rchild->left;
    Rchild->left = p;
    p->right = RLchild;
    return Rchild;
}
int BFactor(Node* p){
    int hl,hr;
    hl = (p&&p->left)? p->left->height : 0;
    hr = (p&& p->right)?p->right->height : 0;
    return hl-hr;
}

Node* avl::RInsert(Node* p,int x)
{
    if(p==NULL){
        p = new Node;
        p->data = x;
        p->left = p->right = NULL;
        p->height = 1;
        return p;
    }
    if(x > p->data){
        p->right = RInsert(p->right,x);
    }else if(x < p->data){
        p->left = RInsert(p->left,x);
    }
    p->height = NodeHeight(p);
    int BF = BFactor(p);
    int BFl = BFactor(p->left);
    int BFr = BFactor(p->right);
    if(BF == 2 && BFl == 1)
        return LLRotation(p);
    else if(BF == 2 && BFl == -1)
        return LRRotation(p);
    else if(BF == 2 && BFr == 1)
        return RLRotation(p);
    else if(BF == -2 && BFr == -1)
        return RRRotation(p);
    return p;
}
void avl::InOrder(Node* p)
{
    if(p){
        InOrder(p->left);
        cout<<p->data<<endl;
        InOrder(p->right);
    }
}
void DTree(Node *p)
{
    if(p)
    {
        DTree(p->left);
        if(p->left == NULL && p->right == NULL){
            delete(p);
            return;
        }
        DTree(p->right);
        if(p->left == NULL && p->right == NULL){
            delete(p);
            return;
        }
    }
}


int main(){
    avl t;

    t.InOrder(t.getRoot());
    DTree(t.getRoot());
}
