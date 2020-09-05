#include<iostream>
#include<string>
#include<cmath>
//Make the stack dynamic ! 
#define MAX_SIZE 100001

using namespace std;

template <class T>
class myStack{
    private:
        T arr[MAX_SIZE];
        int t;
    public:
        myStack(){
            this->t = -1;
        }
        void push(T value){
            if(this->t == MAX_SIZE-1){
                cout<<"Stack overflow "<<endl;
                return;
            }
            (this->arr)[++t] = value;
        }
        void pop(){
            if(this->empty()){
                cout<<"Trying to pop but stack is empty "<<endl;
                return;
            }
            --(this->t);
            return;
        }
        T peek(){
            if(this->empty()){
                cout<<"Trying to peek but Stack is empty "<<endl;
                return -1;
            }
            return (this->arr)[t];
        }
        bool empty(){
            if(this->t == -1)
                return true;
            return false;
        }
        void Print(){
            if(this->t == -1)
                return;
            int temp = this->t;
            while(temp>=0){
                cout<<this->arr[temp]<<" ";
                --temp;
            }
        }
};

bool isOperator(const char& c){
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%')
        return true;
    return false;
}

int getPrecedence(const char & c){
    if(c=='*' || c=='/' || c=='%')
        return 2;
    else 
        return 1;
}

void insert(char c,myStack<char>& operatorStack, string & postfix){
    if(c==')'){
        while(operatorStack.peek() != '('){
            postfix+= " ";
            postfix += operatorStack.peek();
            operatorStack.pop();
        }
        operatorStack.pop();
        return;
    }
    if(c=='('){
        operatorStack.push(c);
        return;
    }
    if(operatorStack.empty()){
        operatorStack.push(c);
        return;
    }
    if(operatorStack.peek() == '('){
        operatorStack.push(c);
        return;
    }
    int currPrecedence = getPrecedence(c);
    int prevPrecedence = getPrecedence(operatorStack.peek());
    if(currPrecedence > prevPrecedence){
        operatorStack.push(c);
    }
    else if( currPrecedence < prevPrecedence){
        postfix += " ";
        postfix += operatorStack.peek(); 
        operatorStack.pop();
        insert(c,operatorStack,postfix);
    }
    else { // equal precedence case
            postfix += " ";
            postfix += operatorStack.peek(); 
            operatorStack.pop();
            insert(c,operatorStack,postfix);
    }
}

string convertToPostfix(const string& expression){
    string postfix="";
    myStack<char> operatorStack;
    for(char c:expression){
        if(isOperator(c)){
            insert(c,operatorStack,postfix);
            postfix+=" ";
        }
        else if(c=='(' || c==')'){
            insert(c,operatorStack,postfix);
        }
        else{
            postfix += c;
        }
    }
    while(!operatorStack.empty()){
        postfix += " ";
        postfix += operatorStack.peek();
        operatorStack.pop();
    }
    return postfix;
}

long double calculate(double a, double b,char c){
    switch(c)
    {
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
        case '%':
            return fmod(a,b);
        default:
            cout<<"Unknown operator "<<endl;
            return -1;
            break;
    }
}

double calculateExpression(const string& postfix){
    string operand="";
    myStack<double> resultStack;
    for(int i=0;i<postfix.size();i++){
        if(isOperator(postfix[i])){
            double operand2 = resultStack.peek();
            resultStack.pop();
            double operand1 = resultStack.peek();
            resultStack.pop();
            resultStack.push(calculate(operand1,operand2,postfix[i]));
            i++;
        }
        else if(isspace(postfix[i])){
            if(operand.empty()){
                cout<<"Invalid maths sequence "<<endl;
                return -1;
            }
            resultStack.push(stold(operand));
            operand="";
        }
        else
            operand+=postfix[i];
    }
    return resultStack.peek();
}

int main(){
    myStack<double> s;
    myStack<char> charStack;
    string expression;
    cout<<"Enter the expression ";
    cin>>expression;
    string postfix = convertToPostfix(expression);
    cout<<calculateExpression(postfix);
}