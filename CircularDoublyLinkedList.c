#include <stdio.h>
#include <stdlib.h>


/*This program is written by: Aryan Jha
   This program creates a user specified amount of nodes
   as a circular doubly linked list. Then, the list is reversed so the last node
   becomes the head. Finally, after reversing the order, the program deletes
   nodes based off the iterative position the user entered until there is only
   one node left. It will loop around the list if the iterative number is greater
   than the number of nodes since its a circular list. Then it returns the surviving
   node's data
 */


struct node { //creates the struct for the node
        int data;
        struct node *next;
        struct node *prev;
};

struct node* create_node (int sequence);


void enqueuenode (struct node * head, int i)
{
        struct node * curnode = create_node(i);
        struct node * lastnode;
        if (head == NULL) //check if list is empty
        {
                curnode->next = curnode;
                curnode->prev = curnode;
                return;
        }
        else
        {
                lastnode = head->prev; //last solider will be previous of start in circle
                curnode->next = head;
                head->prev = curnode;
                curnode->prev = lastnode;
                lastnode->next = curnode;
        }

}


struct node* create_node (int sequence) // dynamic allocate mem for solider
{

        struct node * newnode = (struct node *)malloc(1*sizeof(struct node));
        newnode->data = sequence;
        newnode->next = NULL;
        newnode->prev = NULL;
        return newnode;

}



struct node* create_reverse_circle(int n) // create circular double linked list of n soliders in reverse order
{
        struct node * head = create_node(n);
        for(int i=n; i>0; i--)
        {
                if(i==n) //first node, initialize the values
                {
                        head->prev = head;
                        head->next = head;
                }
                else
                {
                        enqueuenode(head, i);
                }
        }
        return head;
}



struct node* rearrange_circle(struct node* head) // fix the order by swapping adjacent nodes
{
        struct node * temp = NULL;
        struct node * curnode = head;
        if (head->next == head || head == NULL) //checking for empty list or one node list
        {
                return head;
        }
        while (curnode->next != head)
        {
                //swap the adjacent nodes
                temp = curnode->prev;
                curnode->prev = curnode->next;
                curnode->next = temp;
                curnode = curnode->prev;
        }
        //swap the last node that is skipped over by the while loop
        temp = curnode->prev;
        curnode->prev = curnode->next;
        curnode->next = temp;


        return curnode;
}



void display(struct node* head) //prints the list
{
        struct node * temp = head;
        while(temp->next != head)
        {
                printf("%d-->", temp->data);
                temp = temp->next;
        }
        printf("%d\n", temp->data);

}



int delete(struct node* head, int n, int k) //returns surviving solider
{
        int count = 1;
        struct node * temp1;
        struct node * t;
        t = head;

        while(t->next != t) //loop till there is only one node remaining
        {
                printf("Current Node: %d  Previous Node: %d  Next Node: %d\n", t->data, t->prev->data, t->next->data);
                if(count == k) //if the iterative count is met, delete the node
                {
                        printf("Iterative position reached, current node: %d removed.\n", t->data);
                        temp1 = t;
                        t = t->next;
                        temp1->prev->next = temp1->next;
                        temp1->next->prev = temp1->prev;
                        count = 1;
                        printf("List is now: ");
                        display(t);
                        printf("\n");
                }
                else //continue looping, increment count to reach iterative number
                {
                        t=t->next;
                        count += 1;
                }

        }
        return t->data;

}



int main()
{
        int num_nodes, safe_pos;
        printf("How many nodes would you like to enter: ");
        scanf("%d", &num_nodes);
        printf("After what iteration would you like to delete the nodes: ");
        scanf("%d", &safe_pos);

        struct node * headOfList = create_reverse_circle(num_nodes);
        printf("\n");
        printf("List: ");
        display(headOfList);

        headOfList = rearrange_circle(headOfList);
        printf("After ordering: ");
        display(headOfList);

        printf("\n");

        printf("Starting to delete....\n");
        printf("\n");
        int survivor = delete(headOfList, num_nodes, safe_pos);
        printf("Survived: %d\n", survivor);

        return 0;
}
