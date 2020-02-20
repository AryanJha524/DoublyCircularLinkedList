#include <stdio.h>
#include <stdlib.h>


/*This program is written by: Aryan Jha */



struct soldier{
  int data;
  struct soldier *next;
  struct soldier *prev;
};

struct soldier* create_soldier (int sequence);


void enqueueSoldier (struct soldier * head, int i)
{
  struct soldier * curSoldier = create_soldier(i);
  struct soldier * lastSoldier;
  if (head == NULL) //check if list is empty
    {
      curSoldier->next = curSoldier;
      curSoldier->prev = curSoldier;
      return;
    }
  else
    {
      lastSoldier = head->prev; //last solider will be previous of start in circle
      curSoldier->next = head;
      head->prev = curSoldier;
      curSoldier->prev = lastSoldier;
      lastSoldier->next = curSoldier;
    }

}


struct soldier* create_soldier (int sequence) // dynamic allocate mem for solider
{

  struct soldier * newSoldier = (struct soldier *)malloc(1*sizeof(struct soldier));
  newSoldier->data = sequence;
  newSoldier->next = NULL;
  newSoldier->prev = NULL;
  return newSoldier;

}



struct soldier* create_reverse_circle(int n) // create circular double linked list of n soliders in reverse order
{
  //MAYBE ERROR BELOW??
  struct soldier * head = create_soldier(n);
  for(int i=n; i>0; i--)
    {
      if(i==n) //first node, initialize the values
      {
        head->prev = head;
        head->next = head;
      }
      else
      {
        enqueueSoldier(head, i);
      }
    }
  return head;
}



struct soldier* rearrange_circle(struct soldier* head) // fix the order by swapping adjacent nodes
{
  struct soldier * temp = NULL;
  struct soldier * curSoldier = head;
  if (head->next == head || head == NULL) //checking for empty list or one node list
    {
      return head;
    }
  while (curSoldier->next != head)
    {
      temp = curSoldier->prev;
      curSoldier->prev = curSoldier->next;
      curSoldier->next = temp;
      curSoldier = curSoldier->prev;
    }
    temp = curSoldier->prev;
    curSoldier->prev = curSoldier->next;
    curSoldier->next = temp;


  return curSoldier;
}



void display(struct soldier* head) //prints the list
{
  struct soldier * temp = head;
  while(temp->next != head)
    {
      printf("%d ", temp->data);
      temp = temp->next;
    }
    printf("%d\n", temp->data);

}



int kill(struct soldier* head, int n, int k) //returns surviving solider
{
  int count = 1;
  struct soldier * temp1;
  struct soldier * t;
  t = head;

  while(t->next != t)
  {
    if(count == k)
      {
        temp1 = t;
        t = t->next;
        temp1->prev->next = temp1->next;
        temp1->next->prev = temp1->prev;
        count = 1;
      }
    else
      {
          t=t->next;
          count += 1;
      }
  }
  return t->data;

}



int main()
{
  int num_soldiers, safe_pos;

  scanf("%d %d", &num_soldiers, &safe_pos);

  struct soldier * headOfList = create_reverse_circle(num_soldiers);
  printf("List: ");
  display(headOfList);
  headOfList = rearrange_circle(headOfList);
  printf("After ordering: ");
  display(headOfList);
  int survivor = kill(headOfList, num_soldiers, safe_pos);
  printf("Survived: %d\n", survivor);

  return 0;
}
