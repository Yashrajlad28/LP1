#include <iostream>
#include <string>
using namespace std;

class Process
{
    string process_name;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int wait_time;
public:
    Process()
    {
        this->process_name = "";
        this->arrival_time =0;
        this->burst_time =0;
        this->completion_time=0;
        this->turn_around_time=0;
        this->wait_time=0;
    }
    Process(string name, int at, int bt)
    {
        this->process_name = name;
        this->arrival_time = at;
        this->burst_time = bt;
    }

    friend class Process_Details;
};

class Process_Details
{
	int process_num;
	Process pr[10];
public:
	Process_Details()
	{
		process_num = 0;
	}
	    void get_info()
	    {
	    	cout<<"How many processes?: ";
	    	cin>>process_num;
	    	for(int j=0; j<process_num; j++)
	    	{
	    		cout<<"Enter pname, at, bt(space-separated) for process"<<j+1<<": ";
	    		cin>>pr[j].process_name>>pr[j].arrival_time>>pr[j].burst_time;
	    	}

	    }

	    void display()
	    {
	    	cout<<"PId\tAT\tBT"<<endl;
	    	for(int i=0; i<process_num; i++)
	    	{
	    		cout<<pr[i].process_name<<"\t"<<pr[i].arrival_time<<"\t"<<pr[i].burst_time<<endl;
	    	}
	    }

	    void fcfs()
	    {
	    	pr[0].completion_time = pr[0].burst_time;
	    	for(int i=0; i<process_num-1; i++)
	    	{
	    		if(pr[i+1].arrival_time > 0 &&pr[i+1].arrival_time<=pr[i].completion_time)
	    		{
	    			pr[i+1].completion_time = pr[i+1].burst_time+pr[i].completion_time;
	    		}
	    		else
	    		{
	    			pr[i+1].completion_time = pr[i+1].arrival_time+pr[i+1].burst_time;
	    		}
	    	}
	    }

	    void show_completion()
	    {
	    	cout<<"\nCompletion time"<<endl;
	    	for(int i=0; i<process_num; i++)
	    	{
	    		cout<<pr[i].process_name<<"\t"<<pr[i].completion_time<<endl;
	    	}
	    }
};


int main()
{
	Process_Details d;
	d.get_info();
	d.display();
	d.fcfs();
	d.show_completion();
}
