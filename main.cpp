#include <iostream>

using namespace std;

template <class Type>
class Increment {
    Type i;
public:
    Increment(int num = 1) : i(num) { }
    Type operator()(Type x) {return x + i;}
};



template <class Type>
class Array
{
    int n;
    Type *arr;
public:
    Array(int len, Type value = 97); // parametrul default este 97 pentru ca atunci cand este folosit tipul char sa se afiseze litera 'a'
    int Len() const;
    Array<Type> operator=(Array A);
    Array(const Array& A);
    Array operator+(Array A)
    Array<Type> operator-(Array A);
    Type& operator[](int i);
    template <class Fct> void Transform(Fct f);
    friend istream& operator>>(istream& in, Array& A)
    {
        in >> A.n;
        for(int i = 0; i < A.n; i++)
            in >> A.arr[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, Array& A)
    {
        for(int i = 0; i < A.n; i++)
            out << A.arr[i] << ' ';
        return out;
    }
};

template <class Type>
Array<Type>::Array(int len, Type value) : n(len)
{
    arr = new Type[n];
    for(int i = 0; i < n; i++)
        arr[i] = value;
}

template <class Type>
int Array<Type>::Len() const
{
    return n;
}

template <class Type>
Array<Type> Array<Type>::operator=(Array A)
{
    delete[] arr;
    n = A.n;
    arr = new Type[n];
    for(int i = 0; i < n; i++)
        arr[i] = A.arr[i];
    return *this;
}

template <class Type>
Array<Type>::Array(const Array& A)
{
    delete[] arr;
    n = A.n;
    arr = new Type[n];
    for(int i = 0; i < n; i++)
        arr[i] = A.arr[i];
}

template <class Type>
Type& Array<Type>::operator[](int i)
{
    return arr[i];
}

template <class Type>
template <class Fct>
void Array<Type>::Transform(Fct f)
{
    for(int i = 0; i < n; i++)
        arr[i] = f(arr[i]);
}

/*template <class Type>
Array Array<Type>::operator+(Array A)
{
    if(n != A.n)
        cout << "Nu se poate face adunarea pe componente deoarece Array-urile au lungimi diferite.";
    else
    {
        Array temp(n);
        for(int i = 0; i < n; i++)
            temp.arr[i] = arr[i] + A.arr[i];
        return temp;
    }
}

/*template <class Type>
Array<Type> Array<Type>::operator-(Array A)
{
    if(n != A.n)
        cout << "Nu se poate face scaderea pe componente deoarece Array-urile au lungimi diferite.";
    else
    {
        Array temp(n);
        for(int i = 0; i < n; i++)
            temp.arr[i] = arr[i] - A.arr[i];
        return temp;
    }
}*/

int main()
{
    Array<int> a(5);
    Array<int> b(3, 17);
    Array<int> c(a);
    cout << a << endl;
    a = b;
    cout << a << endl;
    cout << c[1] << endl;
    c[1] = 1;
    cout << c[1] << endl;
    Increment<int> inc(2);
    c.Transform(inc);
    cout << c;
    return 0;
}
