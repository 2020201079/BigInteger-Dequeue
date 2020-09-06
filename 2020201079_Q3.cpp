#include<iostream>
#include<stdio.h>
#include<cstring>

# define default_size 20

using namespace std;

template <typename T>
class Deque{
    private:
        T *arr;
        int sizeDeque,top,rear,count;
        void increaseSize(){
            T* prev = arr;
            int prevSize = sizeDeque;
            sizeDeque *= 2;
            arr = new T[sizeDeque];
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
            T* prev = arr;
            int prevSize = sizeDeque;
            sizeDeque = x;
            arr = new T[sizeDeque];
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
            arr = new T[default_size];
            top = -1;rear = -1;count=0;
            this->sizeDeque = default_size;
        }
        Deque(int size, T value){
            this->sizeDeque = size;
            arr = new T[size];
            fill_n(arr,size,value);
            top = 0;rear = size-1;count=size;
        }

        void resize(int x, T d){ 
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
        void push_back(T x){
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
        void push_front(T x){
            if(this->full()){
                this->increaseSize();
                this->push_front(x);
                return;
            }
            if(this->empty()){
                top=0;rear=0;
            }
            else{
                top = (top-1)%sizeDeque;
                if(top<0) top += sizeDeque;
            }       
            arr[top] = x;
            ++count;
        }
        T front(){
            if(this->empty()){
                throw runtime_error("called front() but deque is empty ");
            }
            return arr[top];
        }
        T back(){
            if(this->empty()){
                throw runtime_error("called back() but deque is empty ");
            }
            return arr[rear];
        }

        int size(){
            return count;
        }

        void clear(){
            top=-1;rear=-1;count=0;
        }

        T &operator[](int i){
            if(i<0 || i>=count){
                cout<<"Index out of bounds "<<endl;
                throw runtime_error("Index out of bounds");
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
    auto deque = Deque<char>(2,'n');
    deque.print();
    deque.push_front('v');deque.push_front('a');deque.push_front('r');
    deque.print();
    deque.resize(5,'z');
    deque.print();
    deque.resize(7,'h');
    deque.print();
    cout<<"First ele is "<<deque[0]<<endl;
    cout<<"4th ele is "<<deque[3]<<endl;
    cout<<"5th ele is "<<deque[4]<<endl;
}