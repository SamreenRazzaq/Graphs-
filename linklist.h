/*
  Name:  Hina Khalid
  Copyright: 
  Author: 
  Date: 13/03/12 14:02
  Description: 
*/
#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include "object.h"
using namespace::std;
struct node
{
       object * data;
       node* link;
};

class LL
{
   private:
           node* head;
           node* getAt(int index)    // index starts at 0
              {
               node* tptr=head;
               int x=0;
               if(head!=NULL)
                 while(x<index)
                     {
                     tptr=tptr->link;
                     x++;
                     }
               return tptr;
               }   
   public:
          LL();
          void insert( object *);
          object * remove(int index);
          object * get(int index);
          void print();
          int getLength();
          int isEmpty();          
};

LL::LL()
{
        head=NULL;
}

object* LL::get(int index)
{
    return getAt(index)->data;    
 }

void LL::insert(object * y)
{
  node* nptr=new node;
  nptr->data=y;
  nptr->link=NULL;
  if(head==NULL)
   head=nptr;
  else
  (getAt(getLength()-1))->link=nptr;
 }

void LL::print()
 {
  node * tptr=head;
  while(tptr!=NULL)
    {
      tptr->data->print();
      cout<<" -> ";
      tptr=tptr->link;

    }
  cout<<"NULL\n"	;
 }
 
int LL::getLength()
 {
  node * tptr=head;
  int x=0;
  while(tptr!=NULL)
    {
      tptr=tptr->link;
      x++;
    }
  return x	;
 }

 int LL::isEmpty()
 {
   if(head==NULL)
    return 1;  // for true
   else return 0;  // for false
 }
 
object* LL::remove(int index)
 {
  node* tptr=head, *pptr=head;
  node* hptr=getAt(index);
  while(tptr!=NULL)
    {
      if(tptr==hptr)    //data is found
      {
       if(tptr==head)                    // data is found at head
          {
           tptr=tptr->link;
           head=head->link;
           break;
	  }
       else                              // data is found anywhere else in list it could be on consective nodes or not
          {
	       pptr->link=tptr->link;
           tptr=pptr->link;
           break;
          }
       }
      else                    // if data is not found just move ahead
       {
        pptr=tptr;
        tptr=tptr->link;
       }
    }
    return hptr->data;
 }

#endif
