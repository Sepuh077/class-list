#include <iostream>

template<class T>
class list {
    struct el {
        T v;
        el* link;
    };
    el* first;
    int n;

public:
    list();
    list(const list<T>& a);
    ~list();
    void insertAt(int m, T p);
    void deleteAt(int m);
    void push_back(T k);
    void push_front(T k);
    void pop_back();
    void pop_front();
    bool empty() const;
    int length() const;
    void clear();
    T getValue(int m) const;
    void print() const;
};
/////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
list<T>::list() {
    first = NULL;
    n = 0;
}

template<class T>
list<T>::list(const list<T>& a) {
    first = NULL;
    n = 0;
    for(int i = 1;i <= a.n; ++i) {
        insertAt(i, a.getValue(i));
    }
}

template<class T>
list<T>::~list() {
    n = 0;
    first = NULL;
}

template<class T>
void list<T>::insertAt(int m, T p) {
    if(m > n + 1 || m <= 0) {
        return;
    }
    else {
        if(m == 1) {
            el* q = new el;
            q->v = p;
            q->link = first;
            first = q;
        }
        else {
            el* q = first;
            for(int i = 2;i < m; ++i) {
                q = q->link;
            }
            el* r = new el;
            r->link = q->link;
            q->link = r;
            r->v = p;
        }
        n++;
        return;
    }
}

template<class T>
void list<T>::deleteAt(int m) {
    if(m > n || m <= 0) {
        return;
    }
    else {
        if(m == 1) {
            el* q = first;
            first = first->link;
            delete q;
        }
        else {
            el* q = first;
            for(int i = 2;i < m; ++i) {
                q = q->link;
            }
            el* r = q->link;
            if(m == n)
                q->link = nullptr;
            else
                q->link = r->link;
            delete r;
        }
        n--;
        return;
    }
}

template<class T>
void list<T>::push_back(T k) {
    insertAt(n+1, k);
}

template<class T>
void list<T>::push_front(T k) {
    insertAt(1, k);
}

template<class T>
void list<T>::pop_back() {
    deleteAt(n);
}

template<class T>
void list<T>::pop_front() {
    deleteAt(1);
}

template<class T>
bool list<T>::empty() const{
    return n == 0;
}

template<class T>
int list<T>::length() const{
    return n;
}

template<class T>
void list<T>::clear() {
    for(int i = n;i >= 1; --i) {
        deleteAt(1);
    }
}

template<class T>
T list<T>::getValue(int m) const{
    if(m == 1)
        return first->v;
    el* q = first;
    for(int i = 2; i <= m; ++i) {
        q = q->link;
    }
    return q->v;
}

template<class T>
void list<T>::print() const{
    el* q = first;
    for(int i = 1;i <= n; ++i) {
        std::cout<<q->v<<" ";
        q = q->link;
    }
    std::cout<<std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

template<class T>
int find_coefficent(list<T> f1, list<T> f2, int max_degree, int degree) {
    int sum = 0;
    int i = (degree - max_degree < 0) ? 0 : (degree - max_degree);
    while(i <= degree && i <= max_degree) {
        sum += (f1.getValue(i+1) * f2.getValue(degree - i + 1));
        ++i;
    }
    return sum;
}

/* Կապակցված ցուցակների տեսքով ներկայացված 
բազմանդամների համար իրականացնել նրանց բազմապատկման ալգորիթմը*/

int main() {
    list<int> f, g, F;
    int n,k;
    cin>>n; // ներմուծենք n-րդ աստիճանի 2 բազմանդամ( f եւ g )
    for(int i = 0;i <= n; ++i) {
        cin>>k;
        f.push_back(k);
    }
    for(int i = 0;i <= n; ++i) {
        cin>>k;
        g.push_back(k);
    }
    for(int i = 0;i <= 2*n; ++i) {
        int value = find_coefficent(f, g, n, i); // ֆունկիայի միջոցով հաշվենք արտադրյալի x֊ի i աստիճանի գործակիցը
        F.push_back(value);
    }

    F.print(); // վերջնական բազմանդամի գործակիցների արտածում
    f.clear();g.clear();F.clear();
    return 0;
}