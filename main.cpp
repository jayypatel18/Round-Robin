#include <iostream>
#include <string>
using namespace std;

class PCB{
public:
    int process_id;
    int exe_time;
    int rt;
    int waiting_time;
    string state;
    PCB* next;
    PCB(int id, int exec_time){
        this->process_id = id;
        this->exe_time = exec_time;
        this->state = "Ready For CPU";
        this->next = NULL;
        this->rt = exe_time;
        this->waiting_time = 0;
    }
};

class ReadyQueue{
public:
    PCB* head;
    PCB* tail;
    int queue_size;
public:
    ReadyQueue(){
        this->head = nullptr;
        this->tail = nullptr;
        this->queue_size = 0;
    }
    bool empty_che(){
        return head == nullptr;
    }
    int size() {
        return queue_size;
    }
    void enqueue(PCB* chunk){
        if (head == nullptr){
            head = chunk;
            tail = chunk;
        } else {
            tail->next = chunk;
            tail = chunk;
        }
        queue_size++;
    }

    PCB* dequeue() {
        if (!empty_che()){
            PCB* front = head;
            head = head->next;
            front->next = nullptr;
            queue_size--;
            return front;
        } else {
            return nullptr;
        }
    }
};

class RoundRobin{
public:
    int timeQ;
    int currTime;
    int TwaitT;
    int total_turn_around_time;
    ReadyQueue ready_queue;
public:
    RoundRobin(){
        this->timeQ=3;
        this->currTime=0;
        this->TwaitT= 0;
        this->total_turn_around_time =0;
    }
    ReadyQueue getRQ(){
        return ready_queue;
    }
    void create_process(int process_id, int exe_time){
        PCB* new_process = new PCB(process_id, exe_time);
        ready_queue.enqueue(new_process);
        
    }

    void terminate_process(PCB* process){
        process->state = "Terminated";
        total_turn_around_time += currTime;
        TwaitT += process->waiting_time;
        delete process;
    }

    void dispatcher(){
        PCB* current_process =ready_queue.dequeue();
        if(current_process){
            cout<<"-------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<endl<<endl<<"Executing Process ID  - "<<current_process->process_id<<endl;
            cout <<current_process->state <<endl;
            current_process->rt -= timeQ;
            currTime += timeQ;
            if(current_process->rt <= 0){
                terminate_process(current_process);
                cout << "Terminated" << endl;
            } 
            else{
                current_process->state = "Ready For CPU";
                ready_queue.enqueue(current_process);
                current_process->waiting_time += currTime +this->timeQ;
            }
            PCB* curr_process = ready_queue.head;
            if(curr_process){
            cout<<endl<<"Processes in ReadyQueue after execution :  "<<endl;
            for(int i=0;i<3 && curr_process;i++){
                cout << endl;
                cout<<"Process ID : "<<curr_process->process_id<<endl;
                cout<<"Execution Time : "<<curr_process->exe_time<<endl;
                cout<<"Remaining Time : "<<curr_process->rt<<endl;
                cout<<"Waiting Time : "<<curr_process->waiting_time<<endl;
                curr_process = curr_process->next;
            }
        }
        }
    }
};


int main(){
    RoundRobin obj;
    int num;
     cout<<"Enter the number of processes you want to execute. "<<endl;
     cin>>num;
    int temp = num;
    int i = 1;
     while(temp--){
         int Process_Id;
         int Execution_Time;
         cout << i <<") " << "Enter the Process ID. "<<endl;
         cin>>Process_Id;
         cout<<"Enter the Burst Time of the process. "<<endl<<endl;
         cin>>Execution_Time;
         i = i+1;
         obj.create_process(Process_Id, Execution_Time);
     }

    while(!obj.getRQ().empty_che()){
        obj.dispatcher();
    }

    double avg_wt;
    avg_wt = double(obj.TwaitT)/num;
    double avg_tat;
    avg_tat = double(obj.total_turn_around_time)/num;
    
    cout<< endl<<endl;

    cout << "Average Waiting Time is : " << avg_wt << endl;
    cout << "Average Turn Around Time is : " << avg_tat<< endl;
    
    return 0;
}
