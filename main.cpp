#include <iostream>

using namespace std;

template <class Type>
class Array
{
    int n;
    Type *arr;
public:
    Array(int len, Type value = 97); // parametrul default este 97 pentru ca atunci cand este folosit tipul char sa se afiseze litera 'a'
    int Len() const;
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

int main()
{
    Array<int> a(5);
    cout << a << endl;
    cout << a.Len();
    return 0;
}
