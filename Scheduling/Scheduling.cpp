#include <iostream>
#include <string>
using namespace std;

class Process
{
   string process_name;
   int arrival_time;
   int burst_time;
   int is_completed;
   int completion_time;
   int turn_around_time;
   int wait_time;
public:
   Process()
   {
       this->process_name = "";
       this->arrival_time = 0;
       this->burst_time = 0;
       this->completion_time = 0;
       this->turn_around_time = 0;
       this->wait_time = 0;


   }
   Process(string name, int at, int bt)
   {
       this->process_name = name;
       this->arrival_time = at;
       this->burst_time = bt;
   }
   friend class Queue;
   friend class Scheduling;
};


class Queue
{
   int front, rear;
   Process* que[20];
public:
   Queue()
   {
       front = rear = -1;
   }
   int isempty()
   {
       return front == rear;
   }
   void insert(Process* p)
   {
       if (rear < 19) {
           rear++;
           que[rear] = p;
       }
   }
   Process* remove()
   {
	   front++;
	   return que[front];
   }
   friend class Scheduling;
};


class Scheduling
{
   int process_num;
   Process pr[10];
public:
   Scheduling()
   {
       process_num = 0;
   }
   void get_info()
   {
       cout << "How many processes?: ";
       cin >> process_num;
	   for (int j = 0; j < process_num; j++)
	   {
		   cout << "Enter pname, at, bt(space-separated) for process" << j + 1 << ": ";
		   cin >> pr[j].process_name >> pr[j].arrival_time >> pr[j].burst_time;
	   }
	   cout << "\nDisplaying the table provided by you" << endl;
	   cout << "PId\tAT\tBT" << endl;
	   for (int i = 0; i < process_num; i++)
	   {
		   cout << pr[i].process_name << "\t" << pr[i].arrival_time << "\t" << pr[i].burst_time << endl;
	   }
   }

   void display()
   {
       cout << "PId\tAT\tBT\tCT\tTAT\tWT" << endl;
       for (int i = 0; i < process_num; i++)
       {
           cout << pr[i].process_name << "\t" << pr[i].arrival_time << "\t" << pr[i].burst_time
               << "\t" << pr[i].completion_time << "\t" << pr[i].turn_around_time << "\t" << pr[i].wait_time << endl;
       }
   }

   void sort()
   {
       // objects are getting sorted according to their arrival time
       for (int i = 0; i < process_num; i++)
       {
           for (int j = 0; j < process_num - 1; j++)
           {
               if (pr[j].arrival_time > pr[j + 1].arrival_time)
               {
                   // creating a temporary object
                   Process temp;
                   temp = pr[j];
                   pr[j] = pr[j + 1];
                   pr[j + 1] = temp;
               }
           }
       }
   }

   void fcfs()
   {
	   int current_time=0;
	   Queue q;

	   //ptr points to the process array pr
	   Process* ptr=pr;
	   int finished = 0;

	   // q stores the pointers to the process array
	   // using pointers since if object is inserted into the queue
	   // it is passed by value, a copy is created and all the calculations
	   // of ct, tat & wt are lost
	   // using pointers the actual pr array is modified
	   q.insert(ptr);

	   // using this condition in while
	   // because there can be a test case where cpu is idle
	   // i.e. no new process has arrived between 0 to
	   // completion time of previously completed process

	   /*
	    * Take this test case for example
	    * Pno AT BT
	    * p1  0  2
	    * p2  1  2
	    * p3  5  3
	    * p4  6  4
	    * */
	   while(finished<process_num)
	   {
		   if(!q.isempty())
		   {
				Process* first = q.remove();
				current_time += first->burst_time;
				first->completion_time = current_time;
				first->turn_around_time = first->completion_time-first->arrival_time;
				first->wait_time = first->turn_around_time-first->burst_time;
				finished++;
				ptr++;

		   }else{
			   if(ptr->arrival_time<=current_time)
			   {
				   q.insert(ptr);
			   }else{
				   // incrementing the current_time until
				   // it matches to the arrival_time of next process
				   current_time++;
			   }
		   }
	   }
	   display();
   }

   // Non-preemtive sjf
   void sjf()
   {
	   sort();
	   bool is_selected[process_num];
	   // initialize this is_selected array
	   // using this array to keep track of the
	   // process that are already been selected and inserted into q
	   // to prevent re-insertion of the processes
	   for(int i=0; i<process_num; i++)
	   {
		   is_selected[i] = false;
	   }
	   is_selected[0]=true;

	   int current_time=0;
	   int finished=0;
	   Process* ptr = pr;
	   Queue q;
	   q.insert(ptr);
	   while(finished<process_num)
	   {
		   // here we need to select the next process with minimum
		   // burst time within the time span of 0 to
		   // completion time of previously completed process
		   // these two variables serve that purpose
		   // every time this loop executed shortest and min are re-initialized
		   int shortest=-1;
		   int min=999;
		   if(!q.isempty())
		   {
				Process* first = q.remove();
				current_time += first->burst_time;
				first->completion_time = current_time;
				first->turn_around_time = first->completion_time-first->arrival_time;
				first->wait_time = first->turn_around_time-first->burst_time;
				finished++;
		   }else{
			   for(int i=0; i<process_num; i++)
			   {
				   // (ptr+i)->arrival_time is same as pr[i].arrival_time
				   if(!is_selected[i] && (ptr+i)->arrival_time<=current_time && (ptr+i)->burst_time<min)
				   {
					   shortest = i;
					   min = (ptr+i)->burst_time;
				   }
			   }
			   // after execution of this for loop
			   // the index of the next process with minimum burst_time is obtained
			   // that index is stored in the shortest variable
			   if(shortest != -1)
			   {
				   is_selected[shortest]=true;
				   q.insert(ptr+shortest);
			   }else{
				   current_time++;
			   }
		   }
	   }
	   /*
	    * Take this test case
	    * Pno AT  BT
	    * p1  2   6
	    * p2  15  2
	    * p3  11  8
	    * p4  0   3
	    * p5  14  4
	    * */
	   display();
   }

};
int main()
{
   Scheduling d;
   d.get_info();
   d.sjf();
}
