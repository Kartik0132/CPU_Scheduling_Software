#include<bits/stdc++.h>

using namespace std;

class Scheduling
{
	//Number of Processes n
	int n;
	int P[100],At[100],Bu[100],S[100],C[100],W[100],T[100],R[100];
	
public:
    // getting the input (n,Burst Time and Arrival Time of each process)
    void getArrival();
	void getBurst();
	
	//First come First served Algorithm
	void FCFS();
	//Shortest job First Algorithm
	void SJF();
	//Shortest job First Algorithm with NonPreemption
	void SJFNP();
	//Shortest job First Algorithm with Preemption // Shortest Job Remaining First
	void SJFP();
	//Round Robin Algorithm
	void RR();

};

void Scheduling::getArrival()
{
	cout<<"Enter the no of processes:";
	cin>>n;
	cout<<endl;
    for(int i=0;i<n;i++)
	{
		cout<<"Enter The Arrival for Process P"<<i<<"= ";
		cin>>At[i];
		P[i]=i;
	}
	cout<<endl;

}

void Scheduling::getBurst()
{
    for(int i=0;i<n;i++)
	{
		cout<<"Enter The BurstTime for Process P"<<i<<"= ";
		cin>>Bu[i];
	}
	cout<<endl;

}



void Scheduling::FCFS()
{
	int B[n],A[n];
    float TT=0.0,TW=0.0,TR=0.0,AW,AT,AR,cycle;
	
	for(int i=0;i<n;i++)
	{
		B[i]=Bu[i];
		A[i]=At[i];
    }
    
    for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < n-i-1; j++) 
        if (A[j] > A[j+1]) 
        {
            int temp = A[j]; 
            A[j] = A[j+1]; 
            A[j+1] = temp;
            int temp2 = B[j]; 
            B[j] = B[j+1]; 
            B[j+1] = temp2;
            int temp3=P[j];
            P[j]=P[j+1];
            P[j+1]=temp3;
        }	
	} 
	
	for(int i=0;i<n;i++)
    {
        S[i] = (i==0) ? A[i] : max(A[i], C[i-1]);  
        C[i] =  S[i] + B[i];
        T[i] = C[i]-A[i];       
        W[i] = T[i]-B[i];
        R[i]=W[i];
       
        TT +=T[i];
        TW +=W[i];
        TR +=R[i];
    }
	

cout<<"PNo. "<<" ArrivalTime "<<" BurstTime "<<" CompletionTime "<<" WaitingTime "<<" TurnAroundTime "<<" ResponseTime "<<endl;
	for(int i=0;i<n;i++)
	cout<<" "<<P[i]<<"         "<<A[i]<<"          "<<B[i]<<"           "<<C[i]<<"               "<<W[i]<<"                "<<T[i]<<"           "<<R[i]<<endl;
    
	AW=TW/n;
	AT=TT/n;
	AR=TR/n;
	cycle=C[n-1]-S[0];
	
	
	cout<<"Average Waiting Time="<<AW<<endl;
	cout<<"Average Turn Around Time ="<<AT<<endl;
	cout<<"Average Response Time ="<<AR<<endl;
	cout<<"Throughput ="<<n/cycle<<endl;
	
}


void Scheduling::SJFNP()
{
	int B[n],A[n],max_completion=INT_MIN,min_arrival=INT_MAX;
	float TT=0.0,TW=0.0,TR=0.0,AW,AT,AR,cycle;
	
	int current_time = 0;
    int completed = 0;
    bool is_completed[n]={false};
	
	for(int i=0;i<n;i++)
	{
		B[i]=Bu[i];
		A[i]=At[i];
	}
	
	while(completed!=n)  // till the time all the processes are not completed
    {
        //find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < n; i++) 
		{
            if(A[i]<= current_time && is_completed[i] == false) 
			{
                if(B[i] < minimum) 
				{
                    minimum = B[i];
                    min_index = i;
                }
                if(B[i]== minimum) // if two processes have same burst time than process will be selected on FCFS
				{
                    if(A[i] < A[min_index]) 
					{
                        minimum= B[i];
                        min_index = i;
                    }
                }
            }
        }
        
        if(min_index!=-1)
        {
        	S[min_index]=current_time;
            C[min_index] = S[min_index] + B[min_index];
            T[min_index] = C[min_index] - A[min_index];
            W[min_index] = T[min_index] - B[min_index];
            R[min_index] = S[min_index] - A[min_index];
            
            TT +=T[min_index];
            TW +=W[min_index];
            TR +=R[min_index];
            
            completed++;
            is_completed[min_index]=true;
            current_time=C[min_index];
        	
		}
		else
		    current_time++;
    }
    
    cout<<"PNo. "<<" ArrivalTime "<<" BurstTime "<<" CompletionTime "<<" WaitingTime "<<" TurnAroundTime "<<" ResponseTime "<<endl;
	for(int i=0;i<n;i++)
		cout<<" "<<P[i]<<"         "<<A[i]<<"          "<<B[i]<<"           "<<C[i]<<"               "<<W[i]<<"                "<<T[i]<<"           "<<R[i]<<endl;
    
    AW=TW/n;
	AT=TT/n;
	AR=TR/n;
	
	for(int i=0;i<n;i++)
	{
		max_completion=max(max_completion,C[i]);
		min_arrival=min(min_arrival,A[i]);
	}
	cycle=max_completion-min_arrival;
	
	cout<<"Average Waiting Time="<<AW<<endl;
	cout<<"Average Turn Around Time ="<<AT<<endl;
	cout<<"Average Response Time ="<<AR<<endl;
	cout<<"Throughput ="<<n/cycle<<endl;
	
    	
}

void Scheduling::SJFP()
{
	int B[n],A[n],max_completion=INT_MIN,min_arrival=INT_MAX;
	float TT=0.0,TW=0.0,TR=0.0,AW,AT,AR,cycle;
	
	int current_time = 0;
    int completed = 0;
    bool is_completed[n]={false};
	
	for(int i=0;i<n;i++)
	{
		B[i]=Bu[i];
		A[i]=At[i];
	}
	
	while(completed!=n)  // till the time all the processes are not completed
    {
        //find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < n; i++) 
		{
            if(A[i]<= current_time && is_completed[i] == false) 
			{
                if(Bu[i] < minimum) // Now in array Bu, Bu[i] is working as remaining burst time array for process at index i.
				{
                    minimum = Bu[i];
                    min_index = i;
                }
                if(Bu[i]== minimum) // if two processes have same burst time than process will be selected on FCFS
				{
                    if(A[i] < A[min_index]) 
					{
                        minimum= Bu[i];
                        min_index = i;
                    }
                }
            }
        }
        
        if(min_index!=-1)
        {
        	if(Bu[min_index] == B[min_index])
                S[min_index] = current_time;
            
        	current_time++;        // first completing selected process by 1 unit
            Bu[min_index] -= 1;   // decreasing burst time by 1;
            
            if(Bu[min_index]==0)
            {
                C[min_index] = current_time ;
                T[min_index] = C[min_index] - A[min_index];
                W[min_index] = T[min_index] - B[min_index];
                R[min_index] = S[min_index] - A[min_index];
            
                TT +=T[min_index];
                TW +=W[min_index];
                TR +=R[min_index];
            
                completed++;
                is_completed[min_index]=true;
                current_time=C[min_index];
            }
        }
        
		else
		    current_time++;
    }
    
    cout<<"PNo. "<<" ArrivalTime "<<" BurstTime "<<" CompletionTime "<<" WaitingTime "<<" TurnAroundTime "<<" ResponseTime "<<endl;
	for(int i=0;i<n;i++)
		cout<<" "<<P[i]<<"         "<<A[i]<<"          "<<B[i]<<"           "<<C[i]<<"               "<<W[i]<<"                "<<T[i]<<"           "<<R[i]<<endl;
    
    AW=TW/n;
	AT=TT/n;
	AR=TR/n;
	
	for(int i=0;i<n;i++)
	{
		max_completion=max(max_completion,C[i]);
		min_arrival=min(min_arrival,A[i]);
	}
	cycle=max_completion-min_arrival;
	
	
	cout<<"Average Waiting Time="<<AW<<endl;
	cout<<"Average Turn Around Time ="<<AT<<endl;
	cout<<"Average Response Time ="<<AR<<endl;
	cout<<"Throughput ="<<n/cycle<<endl;
		
}

void Scheduling::RR()
{
	int tq,index,B[n],A[n],max_completion=INT_MIN,min_arrival=INT_MAX;
	float TT=0.0,TW=0.0,TR=0.0,AW,AT,AR,cycle;
	
	cout<<"\nEnter time quanta: ";
    cin>>tq;

	queue<int> q;
	int current_time = 0;
    int completed = 0;
    bool visited[n]={false};
	
	for(int i=0;i<n;i++)
	{
		B[i]=Bu[i];
		A[i]=At[i];
	}
	
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < n-i-1; j++) 
        if (A[j] > A[j+1]) 
        {
            int temp = A[j]; 
            A[j] = A[j+1]; 
            A[j+1] = temp;
            int temp2 = B[j]; 
            B[j] = B[j+1]; 
            B[j+1] = temp2;
            int temp3=P[j];
            P[j]=P[j+1];
            P[j+1]=temp3;
        }	
	} 
	for(int i=0;i<n;i++)
	{
		Bu[i]=B[i];
	}
	
	q.push(0);  
    visited[0] = true;
    
    while(completed!=n)
    {
    	index = q.front();      
        q.pop();
        if(Bu[index] == B[index])
        {
            S[index] = max(current_time,A[index]); //for both the cases in which queue was not empty and queue was empty.
            current_time =  S[index];
        }

        if(Bu[index]-tq > 0)
        {    
            Bu[index] -= tq;
            current_time += tq;
        }
        else 
        {
            current_time += Bu[index];
            Bu[index]= 0;
            completed++;

            C[index] = current_time ;
            T[index] = C[index] - A[index];
            W[index] = T[index] - B[index];
            R[index] = S[index] - A[index];
            
            TT +=T[index];
            TW +=W[index];
            TR +=R[index];
        }
      
        //check which new Processes needs to be pushed to Ready Queue from Input list
        for(int i = 1; i < n; i++) 
        {
            if(Bu[i] > 0 && A[i] <= current_time && visited[i] == false) 
            {
                q.push(i);
                visited[i] = true;
            }
        }
        
        //check if Process on CPU needs to be pushed to Ready Queue
        if( Bu[index]> 0) 
            q.push(index);
            
        //if queue is empty, just add one process from list, whose remaining burst time > 0
        if(q.empty())
        {
            for(int i = 1; i < n; i++)
            {
                if(Bu[i]> 0)
                {
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
   }
   
    cout<<"PNo. "<<" ArrivalTime "<<" BurstTime "<<" CompletionTime "<<" WaitingTime "<<" TurnAroundTime "<<" ResponseTime "<<endl;
	for(int i=0;i<n;i++)
	cout<<" "<<P[i]<<"         "<<A[i]<<"          "<<B[i]<<"           "<<C[i]<<"               "<<W[i]<<"                "<<T[i]<<"           "<<R[i]<<endl;
    
    AW=TW/n;
	AT=TT/n;
	AR=TR/n;
	
	for(int i=0;i<n;i++)
	{
		max_completion=max(max_completion,C[i]);
		min_arrival=min(min_arrival,A[i]);
	}
	cycle=max_completion-min_arrival;
	
	
	cout<<"Average Waiting Time="<<AW<<endl;
	cout<<"Average Turn Around Time ="<<AT<<endl;
	cout<<"Average Response Time ="<<AR<<endl;
	cout<<"Throughput ="<<n/cycle<<endl;
    
}



int main()
{
	int choice;
	
	cout<<"	MENU "<<endl<<endl;
	cout<<"1.FirstComeFirstServe"<<endl;
	cout<<"2.Shortest Job First NonPreemptive"<<endl;
	cout<<"3.Shortest Job First Preemptive / Shortest Remaining Time First"<<endl;	
	cout<<"4.Round Robin"<<endl;
	cout<<"5.EXIT"<<endl<<endl;
	cout<<"Enter your choice"<<endl;
	cin>>choice;
	
	Scheduling s;
	
	switch(choice)
	{
		case 1:
			cout<<"FIRST COME FIRST SERVED SCHEDULING"<<endl<<endl;
			s.getArrival();
	        s.getBurst();
	        s.FCFS();
			break;
		case 2:
			cout<<"SHORTEST JOB FIRST NONPREEMPTIVE SCHEDULING"<<endl<<endl;
			s.getArrival();
	        s.getBurst();
	        s.SJFNP();
			break;
		case 3:
			cout<<"SHORTEST JOB FIRST PREEMPTIVE / SHORTEST REMAINING TIME FIRST SCHEDULING"<<endl<<endl;
			s.getArrival();
	        s.getBurst();
	        s.SJFP();
			break;
		case 4:
			cout<<"ROUND ROBIN SCHEDULING"<<endl<<endl;
			s.getArrival();
	        s.getBurst();
            s.RR();
			break;
		case 5:
			cout<<"NOT A VALID INPUT"<<endl;
			break;
	}
	return 0;
}
