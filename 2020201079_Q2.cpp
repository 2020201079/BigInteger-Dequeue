 #include<iostream>
#include<algorithm>
#include<string>
using namespace std;

#define MAX 3010

class BigInteger{
    public:
        int number[MAX];
        int size;
        void reverse(){
            int l=0;int r=size-1;
            int temp;
            while(l<r){
                temp = number[l];
                number[l] = number[r];
                number[r] = temp;
                l++;r--;
            }
        }
    //public:
        BigInteger(string numberStr){
            for(int i=0;i<numberStr.size();i++){
                this->number[i] = (int)numberStr[i] - '0';
            }
            this->size = numberStr.size();
        }
        BigInteger exponent(int x){
            if(x==0)
                return BigInteger("1");
            if(x%2==0){
                BigInteger a = this->exponent(x/2);
                return a.multiply(a);
            }
            else{
                return this->multiply(this->exponent(x-1));
            }
        }
        BigInteger multiply(BigInteger x){
            BigInteger result("0");
            for(int i=0;i<x.size;i++){
                reverse();
                BigInteger prod = rmultiply(*this,x.number[i]);
                reverse();
                prod.reverse();//need to add zeros x.size-1-i
                for(int j=0;j<x.size-i-1;j++){
                    prod.number[prod.size] = 0;
                    prod.size++;
                }
                result = result.sum(prod); 
            }
            return result;
        }
        BigInteger sum(BigInteger& x){
            BigInteger result("");
            reverse();x.reverse(); // reversing for addition
            int s = max(x.size,size);
            int carry=0;int partSum;
            for(int i=0;i<s;i++){
                if(i<size && i<x.size){
                    partSum = number[i]+x.number[i]+carry;
                    result.number[i] = partSum%10;
                    carry = partSum/10;
                    result.size++;
                }
                else if(i<size){
                    partSum = number[i] + carry;
                    result.number[i] = partSum%10;
                    carry = partSum/10;
                    result.size++;
                }
                else{
                    partSum = x.number[i] + carry;
                    result.number[i] = partSum%10;
                    carry = partSum/10;
                    result.size++;
                }
            }
            while(carry){
                result.number[result.size]=carry%10;
                carry = carry/10;result.size++;
            }
            reverse();x.reverse();result.reverse();
            return result;
        }
        static BigInteger rmultiply(BigInteger m,int x){ // result will be in reverse direction. m is also in reverse
            int carry = 0;
            string result="";
            for(int i=0;i<m.size;i++){
                int prod = (m.number)[i]*x + carry;
                result.push_back(prod%10+'0');
                carry = prod/10;
            }
            while(carry){
                result.push_back(carry%10+'0');
                carry = carry/10;
            }
            return BigInteger(result);
        };
        static BigInteger factorial(int n){
            BigInteger result = BigInteger("1");
            for(int x=2;x<=n;x++){
                result = rmultiply(result,x);
            }
            result.reverse();
            return result; 
        }

        int compare(BigInteger b){ //0 - equal, 1- greater, -1 - less
            if(size > b.size)
                return 1;
            else if(b.size > size)
                return -1;
            else{
                for(int i=0;i<size;i++){
                    if(number[i]>b.number[i])
                        return 1;
                    else if(number[i]<b.number[i])
                        return -1;
                }
            }
            return 0; 
        }
        static BigInteger subtract(BigInteger a, BigInteger b){ // a-b a is always greater 
            b.reverse();a.reverse();
            string res = "";
            for(int i=0;i<a.size;i++){
                if(a.number[i] >= b.number[i]){
                    res += (a.number[i]-b.number[i] + '0');
                }
                else{
                    int j=i+1;
                    while(a.number[j] == 0)
                        j++;
                    a.number[j--]--;
                    while(j != i){
                        a.number[j--] = 9;
                    }
                    res += (a.number[i] + 10 -b.number[i] + '0');
                }
            }
            // this for loop is for triming the initial zeros
            int cut = 0;
            for(int i=res.size()-1;i>=0;i--){
                if(res[i] == '0') cut++;
                else break;
            }
            res = res.substr(0,res.length()-cut);
            BigInteger ans =  BigInteger(res);
            ans.reverse();
            return ans;
        }
        /*
        static BigInteger getMod(BigInteger dividend, BigInteger divisor){
            cout<<"divisor is ";divisor.print();
            cout<<"dividend is ";dividend.print();
            BigInteger prod = BigInteger("");
            divisor.reverse();
            int i=0;
            for(i;i<=9;i++){
                //divisor.reverse();
                prod =  rmultiply(divisor,i);
                prod.reverse();//divisor.reverse();
                int c = prod.compare(dividend);
               // cout<<"prod is :";prod.print();
                if(c == 0)
                    return BigInteger("");
                else if(c==1) //prod is greater
                    break;
            }
            divisor.reverse();
            if(i==10)
                prod = prod.sum(divisor);
            auto ans = subtract(dividend.sum(divisor),prod);
            cout<<"From get mod :"; ans.print();
            return ans; 
        }*/

    static BigInteger getMod(BigInteger dividend, BigInteger divisor){
        BigInteger prod = BigInteger("");
        int i;
        for(i=1;i<=9;i++){
            prod = divisor.multiply(BigInteger(to_string(i)));
            int c = prod.compare(dividend);
            if(c==1){
                break;
            }
            if(c==0)
                return BigInteger("");
        }
        if(i==10)
            prod = prod.sum(divisor);
        BigInteger x =  subtract(prod,divisor);
        BigInteger ans = subtract(dividend,x);
        return ans;
    }

        BigInteger modulus(BigInteger b){ // a mod b
            cout<<" modulus is called  "<<endl;
            cout<<"a is ";print();
            cout<<"b is ";b.print();
            int c = compare(b);
            BigInteger divisor = BigInteger("");
            BigInteger dividend = BigInteger("");
            if(c == 0)
                return BigInteger("");
            else if(c == 1) // this > b
            {
                divisor = b;
                dividend = *this; 
            }
            else{
                return *this;
            }
            cout<<"divisor is : ";divisor.print();
            cout<<"dividend is : ";dividend.print();
            int count = 0;
            while(dividend.compare(divisor) == 1)
            {
                cout<<"0) dividend is : ";dividend.print();
                if(count == 7)
                    break;
                ++count;
                string currDividendStr = "";
                int currDivSize = 0;
                for(int i=0;i<divisor.size;i++){
                    currDividendStr += (dividend.number[i] + '0');
                    ++currDivSize;
                }
                cout<< "1) currDividendStr is : "<<currDividendStr<<endl;  
                BigInteger currDividend = BigInteger(currDividendStr);
                if(divisor.compare(currDividend) == 1){
                    cout<<" 2) I entered divisor is greater condition "<<endl;
                    currDividendStr += (dividend.number[currDivSize] + '0');
                    currDividend = BigInteger(currDividendStr);
                    ++currDivSize;
                }
                cout<<"3) curr Dividend is : "; currDividend.print(); // 12
                cout<<"3) curr Divisor is : "; divisor.print(); // 12
                BigInteger modulus = getMod(currDividend,divisor); // modulus ""
                cout<<" 4) modulus is :" ;modulus.print();
                cout<<"5) Modulus size : "<<modulus.size<<endl;
                string newDividendStr = "";
                for(int i=0;i<modulus.size;i++)
                    newDividendStr += (modulus.number[i] + '0');
                for(int i=currDivSize;i<dividend.size;i++)
                    newDividendStr += (dividend.number[i]+'0');
                cout<<"5) New Dividend string "<<newDividendStr<<endl;
                dividend = BigInteger(newDividendStr);
            }
            if(dividend.size==0 || dividend.compare(divisor)==0)
                return BigInteger("");
            else
                return dividend;
        }

        static BigInteger gcd(BigInteger a, BigInteger b){
            int x = a.compare(b);
            if(x == 0)
                return a;
            else if(x==-1){
                return gcd(b,a);
            }
            if(b.size == 0)
                return a;
            BigInteger c = a.modulus(b);
            cout<<"calling gcd of :";b.print();cout<<" and ";c.print();
            return gcd(b,c);
        }
        void print(){
            if(size == 0)
                cout<<"Empty Big int"<<endl;
            for(int i=0;i<size;i++)
                cout<<number[i];
            cout<<endl;
        }
};

int main(){
    string a,b;
    cin>>a>>b;
    cout<<"Size of a :"<<a.length()<<endl;
    cout<<"Size of b :"<<b.length()<<endl;
    auto x = BigInteger(a);
    auto y = BigInteger(b);
    auto gcd = BigInteger::gcd(x,y);
    cout << "gcd is :";gcd.print();
}