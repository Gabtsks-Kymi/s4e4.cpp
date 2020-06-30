#include <iostream>

using namespace  std;  
  
class lexicon {  
  
  public:  
    lexicon():root(nullptr){}  
    ~lexicon(){  purge(root); }  
  
    void insert(const string &s){  
      if (root== nullptr)  
        root= new node(s, 1, nullptr, nullptr, nullptr);  
      else  insertkey(root, s , 1);   
    }  
  
    int lookup(const string &s) const{  
      return ffreq(root,s);       
    }  
  
    int depth(const string &s) const{  
      int vathos=1;  
      return fdepth(root ,s, vathos);  
    }  
  
    void replace(const string &s1, const string &s2){  
      int m=lookup(s1);       
      node *q=found(root ,s1);   
      if(q!=nullptr){     
        if(q->left == nullptr &&  q->right == nullptr){  
          if(q== q->parent->left)  
            q->parent->left=nullptr;  
          else  
            q->parent->right=nullptr;  
          delete q;  
        }  
        else if(q->left != nullptr && q->right == nullptr) {  
          node *p= q->left;  
          p->parent=q->parent;  
          if(q==root) root=p;  
          else{  
            if (q== q->parent->left)  
              q->parent->left =p;  
            else q->parent->right =p;  
          }  
  
          delete q;  
        }   
        else if (q->left == nullptr && q->right != nullptr){  
          node *p=q->right;  
          p->parent=q->parent;  
          if(q==root) root=p;  
          else{  
            if (q== q->parent->left)  
              q->parent->left =p;  
            else q->parent->right =p;  
          }  
  
          delete q;  
        }  
        else if(q->left!=nullptr && q->right!=nullptr){  
          node *p=q->left;  
          while(p->right!=nullptr){  
            p=p->right;  
          }  
          q->data=p->data;  
          q->plithos=p->plithos;  
  
          if(p->left != nullptr){  
            node *c= p->left;  
            c->parent= p->parent;  
            if (p == p->parent->left)  
                p->parent->left =c;  
            else p->parent->right = c;  
          delete p;  
          }  
          else{  
          if(p==p->parent->left)  
            p->parent->left=nullptr;  
          else  
            p->parent->right=nullptr;  
          delete p;  
          }  
        }  
        insertkey(root , s2, m);  
      }  
    }  
  
   
    friend ostream & operator << (ostream &out, const lexicon &l){  
      l.print(cout, l.root);           
      return out;  
    }  
  
  private:  
  
    struct node{  
      string data;  
      int plithos;  
      node *left, *right, *parent;  
      node(const string &d, const int &x, node *l ,node *r, node *p): data(d),plithos(x),left(l),right(r),parent(p){}  
    };  
  
    node *root;  
  
    void copy(node *t){  
      if(t != nullptr){  
        insert(t->data);  
        copy(t->left);  
        copy(t->right);  
      }  
    }  
  
    void purge (node *t){  
      if(t!= nullptr){  
        purge(t->left);  
        purge(t->right);  
        delete t;   
      }  
    }  
  
    void print(ostream &out, node *t)const {  
      if(t!= nullptr){  
        print(out, t->left);  
        out<<t->data<<" "<<t->plithos<<endl;  
        print(out, t->right);  
      }  
    }  
  
    node *found( node *t, const string &s){  
      while(t!= nullptr && t->data!=s ){  
        if( s< t->data)  
          t=t->left;  
        else  
          t=t->right;  
      }  
      if(t==nullptr)  
        return nullptr;  
      else  
        return t;  
    }  
  
    void insertkey(node *t , const string &s , int  k ){  
      if( s < t->data){  
        if (t->left == nullptr)  
          t->left= new node(s , k , nullptr, nullptr, t);           
        else   
          return   insertkey(t->left, s , k);    
      }  
      else if (s > t->data ){  
        if( t->right == nullptr)  
          t->right =new node( s, k , nullptr, nullptr, t);        
        else  
          return insertkey(t->right , s, k);  
      }  
      else if(s== t->data)   
        t->plithos=t->plithos +k;  
    }  
  
    int ffreq( node *t ,const string &x) const{  
      if(t==nullptr)  
        return 0;  
      else{  
        if( x < t->data)  
          return ffreq( t->left ,x);  
        else if( x > t->data )  
          return ffreq( t->right, x);  
        else   
          return t->plithos;    
      }  
    }  
  
    int fdepth( node*t , const string &s, int v )const {  
      if (t==nullptr)  
        return 0;  
      else{  
        if(s < t->data )  
          return fdepth( t->left , s, v+1);   
        if ( s > t->data)  
          return fdepth(t->right, s, v+1);            
      }  
      return v;  
    }  
  
};  
