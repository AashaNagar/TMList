#include<iostream>
#define bool int
#define true 1
#define True 1
#define TRUE 1
#define false 0
#define FALSE 0
#define False 0

using namespace std;
class Iterator
{
private:
int releaseIteratorAfterIteration;
Iterator *iterator;
public:
Iterator()
{
this->releaseIteratorAfterIteration=1;
this->iterator=NULL;
}

Iterator(Iterator *iterator)
{
this->releaseIteratorAfterIteration=1;
this->iterator=iterator;
}

Iterator(const Iterator &other)
{
this->releaseIteratorAfterIteration=1;
this->iterator=other.iterator;
}

virtual ~Iterator()
{
if(this->releaseIteratorAfterIteration==1)delete this->iterator;
}

void setReleaseIteratorAfterIteration(int releaseIteratorAfterIteration)
{
this->releaseIteratorAfterIteration=releaseIteratorAfterIteration;
}

Iterator & operator=(const Iterator &other)
{
this->iterator =other.iterator;
return *this;
}

virtual int hasMoreElements()
{
if(iterator!=NULL)return this->iterator->hasMoreElements();
return 0;
}
virtual int next()
{
if(iterator!=NULL)return this->iterator->next();
return 0;
}
};

class Iterable
{
public:
virtual Iterator getIterator()=0;
};



class TMList:public Iterable
{
public:
virtual void add(int data,bool *success)=0;
virtual int get(int index,int *success)const=0;
virtual int getSize()const=0;
virtual void insertAt(int index,int data,int *success)=0;
virtual int removeAt(int index,int *success)=0;
virtual void update(int index,int data,int *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
};


class TMArrayList:public TMList
{
private:
int **ptr;
int capacity;
char allocationFlag;
int size;
bool addRow(); 



class TMArrayListIterator:public Iterator
{
int index;
int size;
int **ptr;
public:
TMArrayListIterator(int **ptr,int size)
{
this->index=0;
this->size=size;
this->ptr=ptr;
}
TMArrayListIterator(const TMArrayListIterator & other)
{
this->index=other.index;
}

TMArrayListIterator & operator=(const TMArrayListIterator &other)
{
this->index=other.index;
return *this;
}


int hasMoreElements()
{
return index<size;
}
int next()
{
if(index==size)return 0;
int rowIndex=index/10;
int columnIndex=index%10;
int data=this->ptr[rowIndex][columnIndex];
index++;
return data;
}
};
public:
Iterator getIterator()
{
TMArrayListIterator *tmArrayListIterator;
tmArrayListIterator=new TMArrayListIterator(this->ptr, this->size);
Iterator k(tmArrayListIterator);
k.setReleaseIteratorAfterIteration(0);
return k;
//return Iterator(tmForwardListIterator);
}






TMArrayList();
TMArrayList(int bufferSize);
TMArrayList(const TMArrayList & other);
~TMArrayList();
void removeAll();
void clear();
void add(int data,bool *success);
int get(int index,bool *success)const;
int getSize()const;
void insertAt(int index,int data , bool *success);
void update(int index , int data ,int *success);
int removeAt(int index ,bool *success);
TMArrayList & operator =(const TMArrayList &other);
void operator+=(const TMArrayList &other);
TMArrayList operator +(const TMArrayList &other);
TMArrayList(const TMList &other);
TMArrayList & operator =(const TMList &other);
void operator +=(const TMList &other);
TMArrayList operator +(const TMList &other);
};



TMArrayList::TMArrayList()//DEFAULT CONSTRUCTOR
{
this->ptr=new int*[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->size=0;
this->allocationFlag=0;
}



TMArrayList::TMArrayList(int bufferSize)//PARAMETERIZED CONSTRUCTOR
{
this->allocationFlag=0;
if(bufferSize<=0)
{
this->ptr=new int*[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->size;
}
else
{
int rows;
int numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0)rows++;
numberOfPointers=rows+(10-(rows%10));
this->ptr=new int *[numberOfPointers];
for(int e=0;e<rows;e++)
{
this->ptr[e]=new int[10];
}
this->capacity=rows*10;
this->size=0;
}
}


TMArrayList :: TMArrayList(const TMList &other)
{
this->ptr=new int*[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
this->allocationFlag=0;
int e;
int succ;
for(e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}





TMArrayList::TMArrayList(const TMArrayList & other)// COPY CONSTRUCTOR
{
this->allocationFlag=0;
int bufferSize=other.size;
if(bufferSize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->size=0;
}
else
{
int rows;
int numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0)rows++;
numberOfPointers=rows+(10-(rows%10));
this->ptr=new int*[numberOfPointers];
for(int e=0;e<rows;e++)
{
this->ptr[e]=new int[10];
}
this->capacity=rows*10;
this->size=0;
}
int succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}

}



TMArrayList :: ~TMArrayList()//DESTRUCTOR
{
if(this->allocationFlag==0)
{
int rows=this->capacity/10;
int j;
for(j=0;j<rows;j++)
{
delete [] this->ptr[j];
}
delete [] this->ptr;
}
}




TMArrayList & TMArrayList :: operator =(const TMArrayList &other)// operator =
{
if(other.allocationFlag==0)
{
this->size=0;
int succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
else
{
int rows;
int j;
for(j=0;j<rows;j++)
{
delete [] this->ptr[j];
}
delete [] this->ptr;
this->ptr=other.ptr;
this->capacity=other.capacity;
this->size=other.size;
}
return *this;
}


TMArrayList & TMArrayList :: operator =(const TMList &other)
{
this->size=0;
int e;
int succ;
for(e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
return *this;
}





TMArrayList  TMArrayList :: operator+(const TMArrayList &other)
{
TMArrayList k;
int succ;
for(int e=0;e<this->size;e++)
k.add(this->get(e,&succ),&succ);

for(int e=0;e<other.size;e++)
k.add(other.get(e,&succ),&succ);
k.allocationFlag=1;
return k;
}


TMArrayList  TMArrayList:: operator+(const TMList &other)
{
TMArrayList k;
int succ;
for(int e=0;e<this->size;e++)
k.add(this->get(e,&succ),&succ);

for(int e=0;e<other.getSize();e++)
k.add(other.get(e,&succ),&succ);
return k;
}





void TMArrayList::operator+=(const TMArrayList &other)
{
int succ;
for(int e=0;e<other.size;e++)
this->add(other.get(e,&succ),&succ);
}

void TMArrayList::operator+=(const TMList &other)
{
int succ;
for(int e=0;e<other.getSize();e++)
this->add(other.get(e,&succ),&succ);
}




bool TMArrayList::addRow()
{
if(capacity%100==0)
{
int numberOfPointers;
numberOfPointers=this->capacity/10;
int **tmp=new int*[numberOfPointers+10];
if(tmp==NULL)return false;
for(int e=0;e<numberOfPointers;e++)
tmp[e]=this->ptr[e];
delete[] this->ptr;
this->ptr=tmp;
}
int i=this->capacity/10;
this->ptr[i]=new int[10];
if(this->ptr[i]==NULL)return false;
this->capacity=this->capacity +10;
return true ;
}






void TMArrayList::add(int data,bool *success)
{
if(success)*success =false;
if(this->size==this->capacity)
{
if(!addRow())return ;
}
int rowIndex,columnIndex;
rowIndex=this->size/10;
columnIndex=this->size%10;
this->ptr[rowIndex][columnIndex]=data;
this->size++;
if(success)*success =true;
}



int TMArrayList::get(int index,int *success)const
{
if(success)*success =false;
if(index<0||index>=this->size)return 0;
int rowIndex=index/10;
int columnIndex=index%10;
if(success)*success=true;
return ptr[rowIndex][columnIndex];
}



int TMArrayList::getSize()const
{
return this->size;
}



void TMArrayList::update(int index,int data,int*success)
{
if(success)*success =false;
int rowIndex=index/10;
int columnIndex= index%10;
this->ptr[rowIndex][columnIndex]=data;
if(success)*success=true;
}




int TMArrayList::removeAt(int index ,int *success)
{
if(success)*success=false;
if(index<0||index>=size)return 0;
bool succ;
int data = this->get(index,&succ);
int j;
int ep=this->size-2;
j=index;
while(j<=ep)
{
this->update(j,this->get(j+1,&succ),&succ);
j++;
}
this->size--;
if(success)*success=true;
return data;
}




void TMArrayList::insertAt(int index,int data,bool *success)
{
if(success)*success =false;
if(index<0||index>this->size)return ;
if(index==this->size)
{
this->add(data,success);
return;
}
bool succ;
int k=this->get(this->size-1,&succ);
this->add(k,&succ);
if(succ==false)return ;
int j;
j=this->size-3;
while(j>=index)
{
this->update(j+1,this->get(j,&succ),&succ);
j--;
}
this->update(index,data,&succ);
if(success)*success =true;
}

void TMArrayList :: removeAll()
{
this->size=0;
}

void TMArrayList :: clear()
{
this->size=0;
}






class TMForwardList:public TMList //TMForwardList inherited with TMList & Iterable
{
class TMNode // TMNode class;
{
public:
int data;
TMNode *next;
TMNode()
{
this->next=NULL;
}
};

private:
TMNode *start ,*end;
int size;
char allocationFlag;
public:  
class TMForwardListIterator:public Iterator//TMForwardListIterator inherited with Iterator inside TMForwardList
{
TMNode *ptr;
public:
TMForwardListIterator()
{
this->ptr=NULL;
}
TMForwardListIterator(TMNode *ptr)
{
this->ptr=ptr;
}
TMForwardListIterator(const TMForwardListIterator & other)
{
this->ptr=other.ptr;
}

TMForwardListIterator & operator=(const TMForwardListIterator &other)
{
this->ptr=other.ptr;
return *this;
}


int hasMoreElements()
{
return this->ptr!=NULL;
}
int next()
{
if(this->ptr==NULL)return 0;
int data=this->ptr->data;
this->ptr=this->ptr->next;
return data;
}
};

private:
TMForwardListIterator tmForwardListIterator;
public:
Iterator getIterator()
{
TMForwardListIterator *tmForwardListIterator;
tmForwardListIterator=new TMForwardListIterator(this->start);
Iterator k(tmForwardListIterator);
k.setReleaseIteratorAfterIteration(0);
return k;
//return Iterator(tmForwardListIterator);
}






TMForwardList();
TMForwardList(int bufferSize);
TMForwardList(const TMForwardList &other);
~TMForwardList();
TMForwardList & operator =(const TMForwardList & other);
void operator += (const TMForwardList &other);
TMForwardList operator +(const TMForwardList &other );
void add(int data,bool *success);
int getSize()const;
void insertAt(int index,int data,bool *success);
int removeAt(int intdex , int *success);
void update(int index,int data,int *success);
void removeAll();
void clear();
int get(int index,int *success)const;
TMForwardList(const TMList &other);
TMForwardList & operator =(const TMList &other);
void operator +=(const TMList &other);
TMForwardList operator +(const TMList &other);

};


TMForwardList :: TMForwardList()
{
this->start=NULL;
this->end=NULL;
this->size=0;
}


TMForwardList :: TMForwardList(const TMForwardList &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}


TMForwardList :: TMForwardList(const TMList &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}



TMForwardList :: ~TMForwardList()
{
if(this->allocationFlag==0)
{
this->clear();
}
}


void TMForwardList :: add(int data ,bool *success)
{
if(success)*success =false;
TMNode *t;
t=new TMNode;
if(t==NULL)
return ;
t->data=data;
if(this->start==NULL)
{
this->start=this->end =t;
}
else
{
this->end->next=t;
this->end=t;
}
this->size++;
if(success)*success=true;
}


int TMForwardList :: get(int index,int *success)const
{
if(success)*success=false;
if(index<0||index>=this->size)return 0;
TMNode *t;
int x;
t=this->start;
for(x=0;x<index;x++)t=t->next;

if(success)*success=true;

return t->data;

}


int TMForwardList::getSize()const
{
return this->size;
}

void TMForwardList:: insertAt(int index,int data,int *success)
{
if(success)*success = false ;
if(index<0||index>this->size)return ;
if(index==this->size)
{
this->add(data,success);
return;
}

TMNode *gg;
gg=new TMNode;
if(gg==NULL)return;
gg->data=data;
int x;
TMNode *t ,*j;
t=this->start;
for(x=0;x<index;x++)
{
j=t;
t=t->next;
}

if(t==this->start)
{
gg->next=this->start;
this->start=gg ;
}
else
{
gg->next=t;
j->next=gg;
}
this->size++;
if(success)*success = true;
}




int TMForwardList:: removeAt(int index,int *success)
{
int data=0;
if(success)*success=false;
if(index<0||index>=this->size) return data;
TMNode *t,*j;
int x;
t=this->start;
for(x=0;x<index;x++)
{
j=t;
t=t->next;
}
data=t->data;
if(t==this->start && t==this->end)
{
this->start=this->end=NULL;
}

else if(t==this->start)
{
this->start=this->start->next;
}

else if(t==this->end)
{
j->next=NULL;
this->end=j;
}

else 
{
j->next=t->next;
}
this->size--;
delete t;
if(success)*success = true ;
return data;
}




void TMForwardList:: update(int index,int data,int *success)
{
if(success)*success=false;
if(index<0||index>=this->size)return;
TMNode *t;
int x;
for(t=this->start,x=0;x<index;x++,t=t->next);
t->data=data;
if(success)*success=true;
}




void TMForwardList:: removeAll()
{
clear();
}
void TMForwardList:: clear()
{
TMNode *t;
while(this->start!=NULL)
{
t=this->start;
this->start=this->start->next;
delete t;
}
this->end=NULL;
this->size=0;
}



TMForwardList & TMForwardList :: operator =(const TMForwardList & other)
{
this->clear();
if(other.allocationFlag==1)
{
this->size=other.size;
this->start=other.start;
this->end= other.end;
}
else
{
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
return *this;
}

TMForwardList & TMForwardList :: operator =(const TMList & other)
{
this->clear();
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
return *this;
}





void TMForwardList:: operator += (const TMForwardList &other)
{
int k;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&k),&k);
} 
}

void TMForwardList:: operator += (const TMList &other)
{
int k;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&k),&k);
} 
}



TMForwardList TMForwardList :: operator +(const TMForwardList &other )
{
TMForwardList  k;
k+=(*this);
k+=other;
return  k;
}

TMForwardList TMForwardList :: operator +(const TMList &other )
{
TMForwardList  k;
k+=(*this);
k+=other;
return  k;
}


int main()
{
    
/*
cout<<"TMForwardList implementation"<<endl;
bool k;
TMForwardList list1;
for(int x=100;x<=123;x++)
list1.add(x,&k);
cout<<"Size is"<<list1.getSize()<<endl;

cout<<"Contents of list1"<<endl;
for(int x=0;x<list1.getSize();x++)
cout<<list1.get(x,&k)<<" ";

cout<<"((((((((((((((((((((((((:::::::::"<<endl;

list1.update(2,6000,&k);
if(k)
{
cout<<"updated Suucessfully"<<endl;
}
else
{
cout<<"updataion is unsuccessfull"<<endl;
}

for(int x=0;x<list1.getSize();x++)
cout<<list1.get(x,&k)<<" ";

cout<<endl;
cout<<"************"<<endl;

list1.insertAt(12,1234,&k);
if(k)
{
cout<<"inserted Suucessfully"<<endl;
}
else
{
cout<<"insertion is unsuccessfull"<<endl;
}
for(int x=0;x<list1.getSize();x++)
cout<<list1.get(x,&k)<<" ";

cout<<":::::::::::::::::::::::::::::::::::::"<<endl;

list1.removeAt(0,&k);
if(k)
{
cout<<"removed Suucessfully"<<endl;
}
else
{
cout<<"unable to remove "<<endl;
}

for(int x=0;x<list1.getSize();x++)
cout<<list1.get(x,&k)<<" ";
cout<<endl<<endl;

cout<<"(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:"<<endl;

TMForwardList list2(list1);
cout<<"Size is"<<list2.getSize()<<endl;

cout<<"Contents of list2"<<endl;
for(int x=0;x<list2.getSize();x++)
cout<<list1.get(x,&k)<<" ";

list2.add(1231,&k);
list2.removeAt(0,&k);

cout<<endl<<endl;

cout<<"(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(:"<<endl;


cout<<"Contents of list2"<<endl;
for(int x=0;x<list2.getSize();x++)
cout<<list2.get(x,&k)<<" ";


cout<<endl<<endl;
cout<<"list1=list2"<<endl;

list1=list2;

cout<<"Contents of list1"<<endl;
for(int x=0;x<list1.getSize();x++)
cout<<list1.get(x,&k)<<" ";

cout<<endl<<endl;
TMForwardList list3;
list3.add(2000,&k);
list3.add(3000,&k);
list3.add(4000,&k);
list1+=list3;


cout<<"Contents of list1"<<endl;
for(int x=0;x<list1.getSize();x++)
cout<<list1.get(x,&k)<<" ";

cout<<endl<<endl;
TMForwardList list4;
list4=list1+list3;

cout<<"Contents of list4"<<endl;
for(int x=0;x<list4.getSize();x++)
cout<<list4.get(x,&k)<<" ";

TMArrayList list6;
for(int x=102;x<=120;x++)
{
list6.add(x,&k);
}
cout<<endl<<endl;

TMForwardList list7(list6);
cout<<"Contents of list7"<<endl;
for(int x=0;x<list7.getSize();x++)
cout<<list7.get(x,&k)<<" ";

cout<<endl<<endl<<endl;

list7+=list6;
cout<<"Contents of list7"<<endl;
for(int x=0;x<list7.getSize();x++)
cout<<list7.get(x,&k)<<" ";
*/

bool k;
cout<<"Now iterating on TMArrayrsList"<<endl;
TMForwardList list8;
list8.add(1000,&k);
list8.add(2009,&k);
list8.add(3009,&k);
list8.add(4009,&k);
list8.add(500,&k);
list8.add(600,&k);


Iterator iterator = list8.getIterator();

/*while(iterator.hasMoreElements())
{
cout<<iterator.next()<<endl;	
}
*/
Iterator iterator1=list8.getIterator();
Iterator iterator2=list8.getIterator();
Iterator iterator3=list8.getIterator();

cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;

cout<<"************************"<<endl;

cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;







cout<<"Now iterating on TMForwardList"<<endl;
TMForwardList list9;

list9.add(100,&k);
list9.add(200,&k);
list9.add(300,&k);
list9.add(400,&k);
list9.add(500,&k);
list9.add(600,&k);


 iterator = list9.getIterator();

/*while(iterator.hasMoreElements())
{
cout<<iterator.next()<<endl;	
}
*/

iterator1=list9.getIterator();
iterator2=list9.getIterator();
iterator3=list9.getIterator();

cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;

cout<<"************************"<<endl;

cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;



return 0;
}
