#include <iostream>

using namespace std;

template <class T, class U>
struct Pair
{
    T t;
    U u;
    Pair(T x = 0, U y = 0): t(x),u(y){}
    friend ostream& operator<<(ostream& out, Pair<T, U>& P)
    {
        out << '(' << P.t << ", " << P.u << ")";
        return out;
    }
    Pair<T,U> operator=(Pair<T,U> P)
    {
        t = P.t;
        u = P.u;
        return *this;
    }
};

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
    Array operator+(const Array<Type>& A);
    Array operator-(const Array<Type>& A);
    Type& operator[](int i);
    template <class Fct> void Transform(Fct f);
    template <class U> Array<Pair<Type, U> > Merge(Array<U>& A);
    friend istream& operator>>(istream& in, Array& A)
    {
        in >> A.n;
        for(int i = 0; i < A.n; i++)
            in >> A.arr[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, Array<Type>& A)
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

template <class Type>
template <class U>
Array<Pair<Type, U> > Array<Type>::Merge(Array<U>& A)
{
    if(n != A.Len())
    {
        cout << "Nu se pot combina cele doua Array-uri deoarece au lungimi diferite.";
    }
    else
    {
        Pair<Type, U> p(arr[0],A[0]);
        Array<Pair<Type, U> > temp(n, p);
        for(int i = 0 ;i < n; i++)
        {
            temp[i].t = arr[i];
            temp[i].u = A[i];
        }
        return temp;
    }
}

template <class Type>
Array<Type> Array<Type>::operator+(const Array<Type>& A)
{
    if(n != A.n)
    {
        cout << "Nu se poate face adunarea pe componente deoarece Array-urile au lungimi diferite.";
    }
    else
    {
        Array<Type> temp(n);
        for(int i = 0; i < n; i++)
            temp.arr[i] = arr[i] + A.arr[i];
        return temp;
    }
}

template <class Type>
Array<Type> Array<Type>::operator-(const Array<Type>& A)
{
    if(n != A.n)
        cout << "Nu se poate face adunarea pe componente deoarece Array-urile au lungimi diferite.";
    else
    {
        Array<Type> temp(n);
        for(int i = 0; i < n; i++)
            temp.arr[i] = arr[i] - A.arr[i];
        return temp;
    }
}

int main()
{
    Array<int> a_int(5, 1);
    Array<double> a_double(5, 2.5);
    Pair<int, double> p;
    Array<Pair<int, double> > result(5, p);
    result = a_int.Merge(a_double);
    cout << result << "(Functionalitatea de combinare a doua array-uri, rezultand un array de perechi si redefinirea operatorului '<<')\n";

    Array<int> a(5);
    cout << a << " (Constructor cu 2 parametri, dintre care un parametru default) \n";
    Array<int> b(5, 7);
    cout << b << " (Constructor cu 2 parametri)\n";
    Array<int> c(a);
    cout << c << " (Copy-constructor)\n";
    c = a - b;
    cout << c << " (Redefinirea operatorului '-' si redefinirea operatorului '=')\n";
    c = a + b;
    cout << c << " (Redefinirea operatorului '+')\n";
    cout << a.Len() << " (Lungimea lui 'a')\n";
    cout << a[1] << " (a[1] (read) )\n";
    a[1] = 12;
    cout << a << " (Array-ul 'a' dupa modificarea elementului de pe a doua pozitie, adica a[1] (write) )\n";
    Increment<int> inc(2);
    a.Transform(inc);
    cout << a << " (Array-ul 'a' dupa ce fiecare element al lui a fost incrementat cu 2)";
    return 0;
}
