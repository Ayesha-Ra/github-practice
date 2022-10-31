#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void first_class (int [], int);
void economy_class (int [], int);
void ticket_status (int [], int );

int main()
{

    int a[100]={0};
     printf("\n\n\t*Welcome to Airline B90*\n");
    printf("\tHere is the Ticket Status of Airline B90.\n\tFirst Class contain seats (1-30) & Economy class contain seats (31-100).\n\tLet me know your choice.\n");
    ticket_status(a, 100);

    printf("\n\nPress '1' for first class:\nPress '2' for economy class: \n");
    int num=0;
    srand(time(NULL));
    scanf("%d",&num);
    switch(num)
    {
        case 1:
        first_class(a, 30);
        break;
        case 2:
        economy_class(a, 100);
        break;
    }
}

void first_class(int a[], int size)
{
    int seat=0;
    seat=1+rand()%30;
    while(seat)
    {
        if(seat!=0)
        {
            printf("\n\nYour ticket status is:\n");
            printf("Your seat is in the 'First class' section of the plane.\n");
            printf("Your seat number is: %d\n\n", seat);
            a[seat-1]=1;
            ticket_status(a, 100);
            break;
        }
        seat=1+rand()%size;
    }
}


void economy_class(int a[], int size)
{
    int seat=0;
    seat=31+(rand()%size);
    while(seat)
    {
        if(seat!=0)
        {
            printf("\n\nYour ticket status is:\n");
            printf("Your seat is in the 'Economy class' section of the plane.\n");
            printf("Your seat number is: %d\n\n", seat);
            a[seat-1]=1;
            ticket_status(a, 100);
            break;
        }
        seat=31+(rand()%size);
    }
}

void ticket_status (int a[], int size)
{
     printf("\t***************************************************\n\n\n");
    printf("\t\t\t\t\tTICKET BOARD STATUS\n");
    for(int i=0; i<size; i++)
    {
        if(i==0)
        {
            puts("\nFirst Class");
        }
        if(i%10==0)
        {
            puts("\n\t");
        }
        if(i==30)
        {
            puts("Economy Class\n");
        }
        printf("%d ",a[i]);
    }
    puts("\n\n");
    printf("\t***************************************************");
}