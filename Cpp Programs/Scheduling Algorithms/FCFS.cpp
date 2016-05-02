#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	freopen("input_FCFS.txt","r",stdin);
	int n,a[10],b[10],t[10],w[10],g[10],i,m;
	float att=0,awt=0;
   	for(i=0;i<10;i++){
        a[i]=0; b[i]=0; w[i]=0; g[i]=0;
    }

    //cout<<"Enter the Number of Processes"<<endl;
    cin>>n;
    //cout<<"Enter the Burst Times"<<endl;

	for(i=0;i<n;i++)
        cin>>b[i];

    //cout<<"Enter the Arrival Times"<<endl;
	for(i=0;i<n;i++)
        cin>>a[i];

	g[0]=0;
	for(i=0;i<10-1;i++)
      	g[i+1]=g[i]+b[i];

	for(i=0;i<n;i++)
	{     
		w[i]=g[i]-a[i];
		t[i]=g[i+1]-a[i];
		awt=awt+w[i];
		att=att+t[i]; 
	}
	awt =awt/n;
	att=att/n;
	
    cout<<"Process\tWaiting Time\tTurn Around Time"<<endl;
	for(i=0;i<n;i++)
	{
        cout<<"P"<<i<<"\t\t"<<w[i]<<"\t\t"<<t[i]<<endl;
	}

    cout<<"The Average Waiting Time is "<<awt<<endl;
    cout<<"The Average Turn Around Time is "<<att<<endl;

    fclose(stdin);
	return 0;
}
