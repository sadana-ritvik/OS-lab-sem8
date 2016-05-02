#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int list[20],n_blocks,p_list[2][20];
void allocate(int x); 
void get_blocks(); 
void addProcess(); 
void display();
void deleteProcess(int i);

int top = 0;
int main ()
{
    int choice,id;
    get_blocks();
    do{
        cout<<"\n\n Press 1 : TO ADD A NEW PROCESS.\n Press 2 : TO DELETE A PROCESS.\n PRESS 3 : TO DISPLAY ALL THE PROCESS INFO.\n Press 4 : TO EXIT.";

        cin >> choice;
        switch(choice)
        {

            case 1 : addProcess();
                break;
            case 2 : cout<< "\nEnter the process id.";
                     cin >> id;
                     deleteProcess(id-1);
                break;
            case 3 : display();
                break;
            case 4 : exit(0);
        }
    }while(choice!=4);
    return 0;
}
void get_blocks()
{
    cout<<"Enter the no. of memory blocks";
    cin >> n_blocks;
    cout<<"\nEnter the free size of each block\n";
    for(int i=0;i<n_blocks;i++)
        cin>>list[i];
}
void addProcess()
{
    if(top<20)
    {
        cout<<"\nEnter the size of the process";
        cin >> p_list[0][top];
        top++;
        allocate(top-1);
    }
    else
        cout<<"Cannot enter a new process. Delete some first.";
}
void deleteProcess(int i)
{
    if(top==0)
        cout<<"No processes exist! Add some.";
    else
    {
        list[p_list[1][i]-1]+=p_list[0][i];
        for(int x=i;x<top-1;x++)
        {
            p_list[0][x]=p_list[0][x+1];
            p_list[1][x]=p_list[1][x+1];
        }
        top--;
    }
}
void allocate(int i)
{
    int size,large,pos,num,x;
    x=p_list[0][i];
    num=i;
    large = -1;
    for(i=0;i<n_blocks;i++)
    {
        if(list[i]>large&&list[i]>=x)
        {
            large = list[i];
            pos = i;
        }
    }
    if(large == -1)
    {
        cout<<"Cannot allocate process";
        deleteProcess(num);
        return;
    }
    list[pos]-=x;

    cout<<"\nProcess "<<num+1<<" allocated to "<<"memory block "<<pos+1<<endl;
    p_list[1][num]=pos+1;
}
void display()
{
    cout<<"Process ID\tMemory needed\tMemory Block.\n";
    for(int i=0;i<top;i++)
        cout<<i+1<<"\t\t"<<p_list[0][i]<<"\t\t"<<p_list[1][i]<<endl;
}
