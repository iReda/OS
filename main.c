#include <stdio.h>
#include <stdlib.h>
#define capacity 1


typedef struct node
{
    int data;
    struct node *next;
}node;

node *remove_position(int position, node *head);
node *insert_beginning(int number, node* head);
node *insert_position(int data, int position, node *head);
node *insert_end(int data, node *head);
void waiting_time(node *head, int running_process, int waiting_time_process[]);

int main()
{
    node *head = NULL;
    int io_arrival_time[] = {1, 2, 1, 2, 3, 1 ,2, 3, 1, 1};
    int arrival_time[]={0,2,3,7,8,9,10,11,12,13};
    int process_time[]={2,3,5,3,4,6,8,7,9,1};
    int time=0;
    int g[]={0,0,0,0,0,0,0,0,0,0};
    int waiting_time[]={0,0,0,0,0,0,0,0,0,0};
    int running_time[capacity]={0,0,0,0,0,0,0,0,0,0};
    int sys_running_time = 0;
    int finishing_time[capacity];
    int finished[capacity];
    int turn_around_time[]={0,0,0,0,0,0,0,0,0,0};
    int running_process = 0;
    int busy=0;
    float awt=0;
    float att=0;
    int first_ready;
    int i;
    int x;
    int no_elements = 0;

    for(i = 0; i < capacity; i ++)
    {

        finished[i] = -1;
    }

    first_ready = 0;
    while(not_finished(finished))
    {
    //This will enter the processes into the READY queue for the first time only
        if(sys_running_time == arrival_time[first_ready])
            {
                head = insert_end(first_ready, head);
                running_process = head -> data;
                first_ready++;
            }
        //This function increments the waiting time for each process
        waiting_time(head,running_process, waiting_time);
        if(running_time[running_process] == io_arrival_time[running_process])
        {
            head = insert_end(running_process, head);
            head = remove_position(1, head);
            running_process = head -> data;
            //continue;
        }



    }




    return 0;
}


/*************************************************************************************************************8
*this function will go through the ready queue(the linked list) element by element if a process is in the ready
*queue but it's not the running process it will increments its waiting time by one
*
*
******************************************************************************************************************/

void waiting_time(node *head, int running_process, int waiting_time_process[])
{
    node* temp;
    temp = head;
    while(temp != NULL)
    {
        if(running_process != temp ->data)
        {
            waiting_time_process[temp->data] ++;
            temp = temp->next;
        }
    }
}

node *remove_position(int position, node *head)
{
    node *current = head;
    int i;
    for(i = 0; i < position - 2; i++)
    {
        current = current -> next;
    }
    node *remove = current -> next;
    current -> next = remove -> next;
    free(remove);
    return head;
}

node *insert_beginning(int number, node* head)
{
    node *temp;
    temp = (node*) malloc(sizeof(node));
    temp -> data = number;
    temp -> next = head;
    head = temp;
    return head;
}

node *insert_position(int data, int position, node *head)
{
    if(position == 1)
    {
        insert_beginning(data, head);
    }
    else
    {
        node *temp1 = (node *)malloc(sizeof(node));
        temp1 -> data = data;
        temp1 -> next = NULL;

        node *temp2 = head;
        int i;
        for(i = 0; i < position - 2; i++)
        {
            temp2 = temp2 -> next;
        }

        temp1 -> next = temp2 -> next;
        temp2 -> next = temp1;
    }
    return head;
}

node *insert_end(int data, node *head)
{

    node *new_node = (node *) malloc(sizeof(node));
    new_node -> data = data;
    new_node -> next = NULL;

    if(head == NULL)
    {
        head = new_node;
        printf("Added at beginning\n");
    }
    else
    {
        node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
        printf("added later\n");
    }
    return head;
}
