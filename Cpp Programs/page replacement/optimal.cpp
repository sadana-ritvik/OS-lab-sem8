#include <stdio.h>
int fr[3];

void display()
{
    int i; 
    printf("\n"); 
    for(i=0;i<3;i++) 
        printf("\t%d",fr[i]);
}

int main()
{
    display();
    int p[12]={2,3,2,1,5,2,4,5,3,2,5,2},i,j,fs[3];
    int max,found=0,lg[3],index,k,l,flag1=0,flag2=0,pf=0,frsize=3;
    for(i=0;i<3;i++)
        fr[i]=-1;
    for(j=0;j<12;j++)
    {
        flag1=0;
        flag2=0;
        for(i=0;i<3;i++)
        {
            if(fr[i]==p[j])
            {
                flag1=1;
                flag2=1;
                break;
            }
        }
        if(flag1==0)
        {
            for(i=0;i<3;i++)
            {
                if(fr[i]==-1)
                {
                    fr[i]=p[j];
                    flag2=1;
                    break;
                }
            }
        }

        if(flag2==0)
        {
            for(i=0;i<3;i++)
            lg[i]=0;
        
            for(i=0;i<frsize;i++)
            {
                for(k=j+1;k<12;k++)
                {
                    if(fr[i]==p[k])
                    {
                        lg[i]=k-j;
                        break;
                    }
                }
            }
            found=0;
            for(i=0;i<frsize;i++)
            {
                if(lg[i]==0)
                {
                    index=i;
                    found=1;
                    break;
                }
            }
            if(found==0)
            {
                max=lg[0];
                index=0;
                for(i=1;i<frsize;i++)
                {
                }
            }
            fr[index]=p[j];
            pf++;
        }
        display();
    }
     
    if(max<lg[i])
    {
        max=lg[i];
        index=i;
    }
    printf("\n no of page faults:%d",pf);
return 0;
}
