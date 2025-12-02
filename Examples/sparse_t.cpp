// The SparseArray template demo
// Copyright (c) Andrey Vikt. Stolyarov, 2010-2025
// This is just a sample program for a book devoted to C++, see
// http://www.stolyarov.info/books/cppintro for details.
// No rights restricted; do whatever you want with this code,
// if you really want to.


#include <stdio.h>

template<class T>
class SparseArray {
    struct Item {
        int index;
        T value;
        Item *next;
    };
    Item *first;
    T defval;
public:
    SparseArray(const T &dv) : first(0), defval(dv) {}
    ~SparseArray();
    class Interm {
        friend class SparseArray<T>;
        SparseArray<T> *master;
        int index;
        Interm(SparseArray<T> *a_master, int ind)
            : master(a_master), index(ind) {}
        T& Provide();
        void Remove();
    public:
        operator T();
        T operator=(const T &x);
        T operator+=(const T &x);
        T operator++();
        T operator++(int);
        T operator<<=(int n);
        T operator->() { return Provide(); }
    };
    friend class Interm;

    Interm operator[](int idx)
        { return Interm(this, idx); }
    T operator[](int idx) const;

    int NonzeroCount() const;

private:
    SparseArray(const SparseArray<T>&) {}
    void operator=(const SparseArray<T>&) {}
};

template <class T>
SparseArray<T>::~SparseArray()
{
    while(first) {
        Item *tmp = first;
        first = first->next;
        delete tmp;
    }
}

template <class T>
T SparseArray<T>::operator[](int idx) const
{
    Item* tmp;
    for(tmp = first; tmp; tmp = tmp->next)
        if(tmp->index == idx)
            return tmp->value;
    return defval;
}

template <class T>
int SparseArray<T>::NonzeroCount() const
{
    int r = 0;
    for(Item *tmp = first; tmp; tmp = tmp->next)
        r++;
    return r;
}

template <class T>
T& SparseArray<T>::Interm::Provide()
{
    Item* tmp;
    for(tmp = master->first; tmp; tmp = tmp->next)
        if(tmp->index == index)
            return tmp->value;
    tmp = new Item;
    tmp->index = index;
    tmp->next = master->first;
    master->first = tmp;
    return tmp->value;
}

template <class T>
void SparseArray<T>::Interm::Remove()
{
    Item** tmp;
    for(tmp = &(master->first); *tmp; tmp = &(*tmp)->next) {
        if((*tmp)->index == index) {
            Item *to_delete = *tmp;
            *tmp = (*tmp)->next;
            delete to_delete;
            return;
        }
    }
}

template <class T>
T SparseArray<T>::Interm::operator=(const T &x)
{
    if(x == master->defval)
        Remove();
    else
        Provide() = x;
    return x;
}

template <class T>
T SparseArray<T>::Interm::operator+=(const T &x)
{
    T& location = Provide();
    location += x;
    T res = location;
    if(res == master->defval)
        Remove();
    return res;
}

template <class T>
T SparseArray<T>::Interm::operator++()
{
    T& location = Provide();
    ++location;
    T res = location;
    if(location == master->defval)
        Remove();
    return res;
}

template <class T>
T SparseArray<T>::Interm::operator++(int)
{
    T& location = Provide();
    T res = location;
    location++;
    if(location == master->defval)
        Remove();
    return res;
}

template <class T>
T SparseArray<T>::Interm::operator<<=(int n)
{
    T& location = Provide();
    location <<= n;
    T res = location;
    if(res == master->defval)
        Remove();
    return res;
}

template <class T>
SparseArray<T>::Interm::operator T()
{
    Item* tmp;
    for(tmp = master->first; tmp; tmp = tmp->next)
        if(tmp->index == index)
            return tmp->value;
    return master->defval;
}

////////////////////////////////////////////////////////////
// tests

#ifdef TEST_ON_INT

static void do_query(SparseArray<int> &array, char *str)
{
    int idx, r;
    r = sscanf(str, "%d", &idx);
    if(r != 1) {
        printf("Invalid index\n");
        return;
    }
    printf("** array[%d] == %d\n", idx, (int) (array[idx]));
}

static void do_assign(SparseArray<int> &array, char *str)
{
    int idx, val, r;
    r = sscanf(str, "%d %d", &idx, &val);
    if(r != 2) {
        printf("Invalid numbers\n");
        return;
    }
    array[idx] = val;
}

int main()
{
    char buf[1024];
    SparseArray<int> array(0);
    printf("The following commands are recognized:\n"
           "   ? <key>            query the given key\n"
           "   ! <key> <value>    set the value for the key\n"
           "   #                  query the number of non-default items\n"
           "   q                  quit (or just EOF\n"
           "Please note both keys and values must be integers, suitable\n"
           "for 32 bit int\n");
    while(fgets(buf, sizeof(buf), stdin)) {
        switch(buf[0]) {
            case '?': do_query(array, buf+1); break;
            case '!': do_assign(array, buf+1); break;
            case '#':
                printf("%d items now\n", array.NonzeroCount());
                break;
            case 'q': return 0;
            default:
                printf("Unknown action, must be '?', '!', '#' or 'q'\n");
        }
    }
    return 0;
}

#else  // not TEST_ON_INT

#include <string.h>

class MyStr {
    char *p;
public:
    MyStr() {
        p = new char[1];
        *p = 0;
    }
    MyStr(const char *s) {
        int len = strlen(s);
        p = new char[len+1];
        strcpy(p, s);
    }
    MyStr(const MyStr &a) {
        int len = strlen(a.p);
        p = new char[len+1];
        strcpy(p, a.p);
    }
    ~MyStr() { delete[] p; }
    void operator=(const MyStr &s) {
        delete[] p;
        int len = strlen(s.p);
        p = new char[len+1];
        strcpy(p, s.p);
    }
    const char *str() const { return p; }
    bool operator==(const MyStr &s) const {
        return strcmp(p, s.p) == 0;
    }
};

static void do_query(SparseArray<MyStr> &array, char *str)
{
    int idx, r;
    r = sscanf(str, "%d", &idx);
    if(r != 1) {
        printf("Invalid index\n");
        return;
    }
    MyStr s = array[idx];
    printf("** array[%d] == %s\n", idx, s.str());
}

static void do_assign(SparseArray<MyStr> &array, char *str)
{
    int idx, r;
    char val[1024];
    r = sscanf(str, "%d %1023s", &idx, val);
    if(r != 2) {
        printf("Invalid numbers\n");
        return;
    }
    array[idx] = val;
}

int main()
{
    char buf[1024];
    SparseArray<MyStr> array(MyStr("--//--"));
    printf("The following commands are recognized:\n"
           "   ? <key>            query the given key\n"
           "   ! <key> <value>    set the value for the key\n"
           "   #                  query the number of non-default items\n"
           "   q                  quit (or just EOF\n"
           "Please note keys must be integers, suitable for 32 bit int,\n"
           "while a value may be any string not containing whitespace\n");
    while(fgets(buf, sizeof(buf), stdin)) {
        switch(buf[0]) {
            case '?': do_query(array, buf+1); break;
            case '!': do_assign(array, buf+1); break;
            case '#':
                printf("%d items now\n", array.NonzeroCount());
                break;
            case 'q': return 0;
            default:
                printf("Unknown action, must be '?', '!', '#' or 'q'\n");
        }
    }
    return 0;
}

#endif  // TEST_ON_INT
