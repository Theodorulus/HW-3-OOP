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

/*class Pair1
{

public:
    int t, u;
    Pair1(int x = 0, int y = 0): t(x),u(y){}
    friend ostream& operator<<(ostream& out, Pair1& P)
    {
        out << '(' << P.t << ", " << P.u << ")";
        return out;
    }
    Pair1 operator=(Pair1 P)
    {
        t = P.t;
        u = P.u;
        return *this;
    }
};*/

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
//    template <class U> Array<Pair1> Merge(const Array<U>& A);
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

/*template <class Type>
template <class U>
Array<Pair1 > Array<Type>::Merge(const Array<U>& A)
{
    if(n != A.n)
    {
        cout << "Nu se pot combina cele doua Array-uri deoarece au lungimi diferite.";
    }
    else
    {
        Pair1 p;
        Array<Pair1 > temp(n, p);
        for(int i = 0 ;i < n; i++)
        {
            temp[i].t = arr[i];
            temp[i].u = A.arr[i];
        }
        return temp;
    }
}*/

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
    /*Array<int> a(5);
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
    cout << c << endl;
    //c =  a + b;
    cout << c << endl;*/
    /*Pair1 p1(2, 3);
    Pair1 p2(5, 6);
    cout << p1 << p2;
    p1 = p2;
    cout << p1;*/
    //p2.t = 15;
    //p2.u = 16;
    //cout << p1;
    //p1 = p2;
    //cout << p1;
    /*Array<Pair1> d(1, p);
    a.Merge(b);
    cout << d;*/

    /*
    Array<int> a(5, 1);
    Array<int> b(5, 2);
    Pair1 p1(2, 3);
    Array<Pair1> c(5, p1);
    c = a.Merge(b);
    cout << c;*/

    Array<int> a(5, 1);
    Array<double> b(5, 2.5);
    Pair<int, double> p1(2, 3.2);
    Array<Pair<int, double> > c(5, p1);
    c = a.Merge(b);
    cout << c;
    return 0;
}
