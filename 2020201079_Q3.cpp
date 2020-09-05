#include<iostream>
#include<stdio.h>
#include<cstring>

# define default_size 20

using namespace std;

class Deque{
    private:
        int *arr;
        int sizeDeque,top,rear,count;
        void increaseSize(){
            int* prev = arr;
            int prevSize = sizeDeque;
            sizeDeque *= 2;
            arr = new int[sizeDeque];
            int i=0;
            while(top != rear){
                arr[i] = prev[top];
                top = (top + 1) % prevSize;
                i++;
            }
            arr[i] = prev[top];
            top = 0;
            rear = i;
            delete[] prev; // remove the old array
        }
        void increaseSize(int x){
            int* prev = arr;
            int prevSize = sizeDeque;
            sizeDeque = x;
            arr = new int[sizeDeque];
            int i=0;
            while(top != rear){
                arr[i] = prev[top];
                top = (top + 1) % prevSize;
                i++;
            }
            arr[i] = prev[top];
            top = 0;
            rear = i;
            delete[] prev; // remove the old array
        }
    public :
        Deque(){
            arr = new int[default_size];
            top = -1;rear = -1;count=0;
            this->sizeDeque = default_size;
        }
        /*
        Deque(int size){
            this->sizeDeque = size;
            arr = new int[size];
            top = -1;rear = -1;count=0;
        }*/
        Deque(int size, int value){
            this->sizeDeque = size;
            arr = new int[size];
            fill_n(arr,size,value);
            top = 0;rear = size-1;count=size;
        }

        void resize(int x, int d){
            //changes here is required 
            if(x < count){
                cout<<"resizing will delete some elements "<<endl;
                rear = (rear - count+x)%sizeDeque;
                if(rear<0) rear += sizeDeque;
                count = x;
            }
            else{
                while(x>sizeDeque)
                    increaseSize();
                cout<<"Curr size is :"<<sizeDeque<<endl;

                if(rear+x-count < sizeDeque){
                    fill_n(arr+rear+1,x-count,d); // this is getting overflow
                }
                else{
                    fill_n(arr+rear+1,sizeDeque-rear-1,d);
                    fill_n(arr,x-count-sizeDeque+rear+1,d);
                }
                rear = (rear+x-count) % sizeDeque; 
                count = x; 
                //increaseSize(x);
            }
        }
        bool empty(){
            if(top == -1 && rear == -1)
                return true;
            return false;
        }
        bool full(){
            if((rear+1)%sizeDeque == top)
                return true;
            return false;
        }
        void push_back(int x){
            if(this->full()){
                cout<<"deque is full calling increase "<<endl;
                this->increaseSize();
                this->push_back(x);
                return;
            }
            if(this->empty())
                {top = 0;rear = 0;}
            else
                rear = (rear+1)%sizeDeque;
            arr[rear] = x;
            ++count;
        }
        void pop_back(){
            if(this->empty()){
                cout<<"Deque is empty cannot pop_back "<<endl; return;
            }
            else if(this->count == 1){
                top=-1;rear=-1;--count;
            }
            else{
                rear = (rear-1)%sizeDeque; // verify if the mod returns pos values
                if(rear<0) rear += sizeDeque;
                --count; 
            }
        }
        void pop_front(){
            if(this->empty()){
                cout<<"Deque is empty cannot pop_front "<<endl;return;
            }
            else if(this->count == 1){
                top=-1;rear=-1;--count;
            }
            else{
                top = (top + 1) % sizeDeque;
                --count;
            }
        }
        void push_front(int x){
            if(this->full()){
                cout<<"deque is full calling increase"<<endl;
                this->increaseSize();
                this->push_front(x);
                return;
            }
            if(this->empty()){
                top=0;rear=0;
            }
            else{
                top = (top-1)%sizeDeque; // verify if the mod returns pos values
                if(top<0) top += sizeDeque;
            }       
            arr[top] = x;
            cout<<"top is " << top << endl;
            ++count;
        }
        int front(){
            if(this->empty()){
                cout<<"called front() but deque is empty ";
                return -1;
            }
            return arr[top];
        }
        int back(){
            if(this->empty()){
                cout<<"called back() but deque is empty ";
                return -1;
            }
            return arr[rear];
        }

        int size(){
            return count;
        }

        void clear(){
            top=-1;rear=-1;count=0;
        }

        int &operator[](int i){
            if(i<0 || i>=count){
                cout<<"Index out of bounds "<<endl;
                int i = -1;
                int &q = i;
                return q;
            }
            int temp = top;
            temp=(top+i)%sizeDeque;
            return arr[temp];
        }
        void print(){
            int temp = top;
            while(temp != rear){
                cout<<arr[temp]<<" ";
                temp = (temp + 1) % sizeDeque;
            }
            cout<<arr[temp]<<endl;
        } 
};

int main(){
    auto deque = Deque();
    deque.push_front(3);deque.push_front(5);deque.push_front(7);
    deque.print();
    deque.resize(1,123);
    deque.print();
    deque.resize(4,89);
    deque.print();
    cout<<"First ele is "<<deque[0]<<endl;
    cout<<"4th ele is "<<deque[3]<<endl;
    cout<<"5th ele is "<<deque[4]<<endl;
}