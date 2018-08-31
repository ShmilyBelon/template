#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
const int maxn = 1e3+10;
//int a[maxn];



template <typename T>
struct LISTNODE{
    T d; //data
    int id;
    struct LISTNODE* next;
    struct LISTNODE* pre;
    LISTNODE(int tid) //Just an example,change in terms of problem
    {
        this->id = tid;
        this->d = (T)id; //in this example ,data equals id(default : data is an int)
        this->next = NULL;
        this->pre = NULL;
    }
};

template <typename T>
struct LIST{
    LISTNODE<T>* head;
    LISTNODE<T>* tail;
    LISTNODE<T>* id2loc[maxn];//id2loc[i] means the pointer of the node whose id is i. index from 1 to N    
    int len;
    
    LIST (int n)//build a list of n nodes, id of which ranges from 1 to n 
    {
        memset(id2loc,0,sizeof(id2loc));
        this->len = n;

        if(!n)
        {
           this-> head = this->tail = NULL;
            return ;
        }

        this->head = new LISTNODE<T>(1);
        LISTNODE<T>* p = this->head;
        id2loc[1] = this->head;
        for(int i=0;i<n-1;i++)
        {
            p->next = new LISTNODE<T>(i+2);//head->d==1.so p->d here is i+2
            p->next->pre = p;
            id2loc[i+2] = p->next;
       
            if(i<n-2) //p has not reached the tail
                p = p->next;
        }
        this->tail = p;
    }


    ~LIST()
    {
        LISTNODE<T>* p = this->head;
        LISTNODE<T>* pp = p;
        while(p)
        {
            p = p->next;
            delete(pp);
            pp = p;
        }
        this->head = this->tail = NULL;
        this->len = 0;

       // memset(id2loc , 0 , sizeof(id2loc));
    }

    /*to_ins is the place to insert, mode:0 means insert before in_ins node, 1 means after it */
    bool insert(LISTNODE<T>*to_ins, LISTNODE<T>* new_node, int mode=1 ) 
    {
        if(!to_ins || !new_node) // they cannot be NULL
            return false;
        
        if( id2loc[new_node->id] ) // if the new_node's id have exsited
            return false;

        if(mode) // to-ins's back
        {
            if(to_ins->next)//to_ins is not the tail
                to_ins->next->pre = new_node;
            else
                tail = new_node;

            new_node->next = to_ins->next;
            to_ins->next = new_node;
            new_node->pre = to_ins;
        }
        else
        {
            if(to_ins->pre)//to_ins is not the head
                to_ins->pre->next = new_node;
            else
                head = new_node;

            new_node->pre = to_ins->pre;
            to_ins->pre = new_node;
            new_node->next = to_ins;
        }

        id2loc[new_node->id] = new_node;
        len++;

        return true;
    }

    /*give the object u wanna delete*/
    bool remove( LISTNODE<T>* obj ) 
    {
        if(!obj || !len) 
            return false;

        if(! obj->pre)//obj is  the head
        {
            if(obj->next) // there're still some nodes after head
            {  
                obj->next->pre = NULL;//new head
                this->head = obj->next;
            }
            else
                this->head = this->tail = NULL;

        }
        else//obj is NOT the head
        {
            if(! obj->next) //obj is the tail
            {
                if(obj->pre)//there're still some node before tail
                {
                    obj->pre->next = NULL; // new tail
                    this->tail = obj->pre;
                }
                else
                    this->head = this->tail = NULL;
            }

            else // obj is neither head nor tail
            {
                obj->pre->next = obj->next;
                obj->next->pre = obj->pre;
            }

        }
            
        len--;
        id2loc[obj->id] = NULL;
        delete(obj);
        return true; 
    }

    





    /*loc>0 means 'from' is placed after 'to' while loc<0 means before 'to' */
    /*you must ensure the movement is legal*/
    bool move( LISTNODE<T>* from ,  LISTNODE<T>* to , int mode = 1)
    {
        if(!to || !from) // to and from cannot be a NULL
            return false;

       
        if(! from->pre)//from is  the head
        {
            if(from->next) // there're still some nodes after head
            {  
                from->next->pre = NULL;//new head
                this->head = from->next;
            }
            else
                this->head = this->tail = NULL;

        }
        else//from is NOT the head
        {
            if(! from->next) //obj is the tail
            {
                if(from->pre)//there're still some node before tail
                {
                    from->pre->next = NULL; // new tail
                    this->tail = from->pre;
                }
                else
                    this->head = this->tail = NULL;
            }

            else // from is neither head nor tail
            {
                from->pre->next = from->next;
                from->next->pre = from->pre;
            }

        }


        if(mode) // to's back
        {
            if(to->next)//to is not the tail
                to->next->pre = from;
            else
                tail = from;

            from->next = to->next;
            to->next = from;
            from->pre = to;
        }
        else
        {
            if(to->pre)//to is not the head
                to->pre->next = from;
            else
                head = from;

            from->pre = to->pre;
            to->pre = from;
            from->next = to;
        }


        return true; 
    }


    bool traverse(void)
    {
        if(!this->head)
        {
           // printf("This linklist is empty!\n ");
            return false;
        }
    
        LISTNODE<T>* ptrl = head;
        while(ptrl)
        {
            printf("%d",ptrl->d);
            if(ptrl->next)
                printf(" ");
            else
                printf("\n");
            ptrl = ptrl->next;
        }
        //printf("len: %d\n",this->len);   
        return true;
    }

};


int main()
{
            
    int n,m;
    /*
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        LIST<int> l(n);
        for(int i=0;i<m;i++)
        {
            int id,mov,d;
            scanf("%d%d",&id,&mov);
            
            d = abs(mov);
            LISTNODE<int>* to = l.id2loc[id];
            LISTNODE<int>* from = to;
            for(int j=0;j<d;j++)
                to = mov>0 ? to->next : to->pre;
            l.move(from , to , mov>0);
        }
        l.traverse();
    }
      */

    while(scanf("%d%d",&n,&m)!=EOF)
    {
        LIST<int> l(n);
        for(int i=0;i<m;i++)
        {
            int to,mode;
            scanf("%d%d",&to,&mode);
            LISTNODE<int>* newnode = new LISTNODE<int>(n+i+1);
            LISTNODE<int>* pto = l.id2loc[to];

            l.insert(pto,newnode,mode);
            
        
        }    
        l.traverse();

    
    }    
     
/*
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        LIST<int> l(n);
        for(int i=0;i<m;i++)
        {
            int to,mode;
            scanf("%d",&to);
           // LISTNODE<int>* newnode = new LISTNODE<int>(n+i+1);
            LISTNODE<int>* pto = l.id2loc[to];

          //  l.insert(pto,newnode,mode);
            l.remove(pto);
            
        
        }    
        l.traverse();

    
    }    
  */           
                 

    

    return 0;

}

