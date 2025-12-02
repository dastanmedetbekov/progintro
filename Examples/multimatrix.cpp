// The MultiMatrix template demo
// Copyright (c) Andrey Vikt. Stolyarov, 2011-2025
// This is just a sample program for a book devoted to C++, see
// http://www.stolyarov.info/books/cppintro for details.
// No rights restricted; do whatever you want with this code,
// if you really want to.


template <class T>
class Array {
    T *p;
    T init;
    unsigned int size;
public:
    Array(T in) : p(0), init(in), size(0) {}
    ~Array() { if(p) delete[] p; }
    T& operator[](unsigned int idx) {
        if(idx >= size)
            Resize(idx);
        return p[idx];
    }
    const T& operator[](unsigned int idx) const {
        return idx >= size ? init : p[idx];
    }
    int Size() const { return size; }
private:
    void Resize(unsigned int required_index) {
        unsigned int new_size = size==0 ? 8 : size;
        while(new_size <= required_index)
            new_size *= 2;
        T *new_array = new T[new_size];
        for(unsigned int i = 0; i < new_size; i++)
            new_array[i] = i < size ? p[i] : init;
        if(p)
            delete[] p;
        p = new_array;
        size = new_size;
    }
    void operator=(const Array<T>& ref) {}
    Array(const Array<T>& ref) {}
};

template <class T, T init_val, int dim>
class MultiMatrix {
    Array<MultiMatrix<T, init_val, dim-1>*> arr;
public:
    MultiMatrix() : arr(0) {}
    ~MultiMatrix() {
        for(int i=0; i < arr.Size(); i++)
            if(arr[i])
                delete arr[i];
    }
    MultiMatrix<T, init_val, dim-1>& operator[](unsigned int idx) {
        if(!arr[idx])
            arr[idx] = new MultiMatrix<T, init_val, dim-1>;
        return *arr[idx];
    }
    const MultiMatrix<T, init_val, dim-1>& operator[](unsigned int idx) const {
        static MultiMatrix<T, init_val, dim-1> dummy;
        return arr[idx] ? *arr[idx] : dummy;
    }
};

#if 1    // this implementation works fine, but there's a simpler approach

template <class T, T init_val>
class MultiMatrix<T, init_val, 1> {
    Array<T> arr;
public:
    MultiMatrix() : arr(init_val) {}
    T& operator[](unsigned int idx) { return arr[idx]; }
    const T& operator[](unsigned int idx) const { return arr[idx]; }
};

#else    // here the simpler approach goes

template <class T, T init_val>
class MultiMatrix<T, init_val, 1> : public Array<T> {
public:
    MultiMatrix() : Array<T>(init_val) {}
};

#endif


/* **************************************************************

Please note that this "simplified" approach with inheritance instead of
composition works ONLY for the dim==1 case, because on higher levels
the Array-based object is supposed to hold _pointers_ to "dim-1" objects,
while the operator[] must return a _reference_ to that object, hence
there's an extra dereference in the operator[]'s body.

Attempt to do smth. like this

template <class T, T init_val, int dim>
class MultiMatrix : public Array<MultiMatrix<T, init_val, dim-1>*> {
public:
    MultiMatrix() : Array<MultiMatrix<T, init_val, dim-1>*>(0) {}
};

will therefore fail, effectively meaning that we'll have to provide our own
versions of operator[] anyway, but their bodies will look very ugly as
we'll have to mention the base class explicitly, several times, and, heh,
just take a look at it (that "Array<MultiMatrix<T, init_val, dim-1>*>"
thing).

There's also a temptation to hold objects, not pointers, within the arrays,
so it will be smth. like

template <class T, T init_val, int dim>
class MultiMatrix : public Array<MultiMatrix<T, init_val, dim-1> > {
public:
    MultiMatrix() {}
};

Holding an object instead of a pointer is not good as the object is
notably larger, but this may be considered a minor issue not preventing us
from implementing the thing that way.  However, there are more problems.

Such an implementation requires a default constructor for the Array
template (which is okay), but this also requires the assignment operator
for the Array<...> classes to be visible (and properly implemented), as it
is used within the Resize method.  Yes, this is still possible, but it
effectively means every resize will _copy_ all lower-dimension data.  Some
people believe such things are okay.  We don't.

************************************************************** */


#if 0  // this is a simple test as it is shown in the book

#include <stdio.h>

int main()
{
    MultiMatrix<int, -1, 5> mm;
    mm[3][4][5][2][7] = 193;
    mm[2][2][2][2][2] = 251;
    printf("%d %d %d %d\n",
        mm[3][4][5][2][7],
        mm[2][2][2][2][2],
        mm[0][1][2][3][4],
        mm[1][2][3][2][1]);
    return 0;
}

#else  // this version of the test is more sophisticated

#include <stdio.h>

typedef MultiMatrix<int, -1, 5> MMi5;

static int get_mm5(const MMi5 &mm, int i1, int i2, int i3, int i4, int i5)
{
    return mm[i1][i2][i3][i4][i5];
}

int main()
{
    MultiMatrix<int, -1, 5> mm;
        // this uses the non-const operator[]'s version
    mm[3][4][5][2][7] = 193;
    mm[2][2][2][2][2] = 251;

        // this _still_ uses the non-const operator[]'s version
    printf("%d %d %d %d\n",
        mm[3][4][5][2][7],
        mm[2][2][2][2][2],
        mm[0][1][2][3][4],
        mm[1][2][3][2][1]);

        // and this uses the const operator[]'s version
    printf("%d %d %d %d\n",
        get_mm5(mm, 3, 4, 5, 2, 7),
        get_mm5(mm, 2, 2, 2, 2, 2),
        get_mm5(mm, 0, 1, 2, 3, 4),
        get_mm5(mm, 1, 2, 3, 2, 1));
    return 0;
}


#endif






