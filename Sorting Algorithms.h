#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <algorithm> 

namespace mina
{
    template<typename T>
    void bubble_sort(std::vector<T>& A);

    template<typename T>
    void insertion_sort(std::vector<T>& A);

    template<typename T>
    void selection_sort(std::vector<T>& A);

    template<typename T>
    void quick_sort(std::vector<T>& A);

    template<typename T>
    void quick_sort(int l, int h, std::vector<T>& A);

    template<typename T>
    int quick_helper(int l, int h, std::vector<T>& A);
    template<typename T>
    void shell_sort(std::vector<T>&);

}

template<typename T>
void mina::bubble_sort(std::vector<T>& A)
{
    bool flag;
    for (size_t i = 0; i < A.size() - 1; i++)
    {
        flag = false;
        for (size_t j = 0; j < A.size() - 1 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                std::swap(A[j], A[j + 1]);
                flag = true;
            }
        }
        if (!flag)
            break;
    }
}

template<typename T>
void mina::insertion_sort(std::vector<T>& A)
{
    for (size_t i = 1; i < A.size(); i++)
    {
        T x = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > x)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

template<typename T>
void mina::selection_sort(std::vector<T>& A)
{
    for (size_t i = 0; i < A.size(); i++)
    {
        size_t k = i;
        for (size_t j = i + 1; j < A.size(); j++)
        {
            if (A[j] < A[k])
                k = j;
        }
        if (k != i)
            std::swap(A[i], A[k]);
    }
}

template<typename T>
void mina::quick_sort(std::vector<T>& A)
{
    mina::quick_sort(0, A.size() - 1, A);
}

template<typename T>
void mina::quick_sort(int l, int h, std::vector<T>& A)
{
    if (l < h)
    {
        int j = mina::quick_helper(l, h, A);
        mina::quick_sort(l, j, A);
        mina::quick_sort(j + 1, h, A);
    }
}

//dont be an idiot and use it its just a helper function 
template<typename T>
int mina::quick_helper(int l, int h, std::vector<T>& A)
{
    T pivot = A[l];
    int i = l;
    int j = h;
    while (true)
    {
        while (A[i] < pivot) i++;
        while (A[j] > pivot) j--;
        if (i >= j)
            return j;
        std::swap(A[i++], A[j--]);
    }
}

template <typename T>
void mina::shell_sort(std::vector<T>& A)
{
    int n = (int)A.size();
    int gap, i, j;
    for (gap = n / 2; gap >= 1; gap /= 2)
    {
        for (i = gap; i < n; i++)
        {
            T temp = A[i];
            j = i - gap;
            while (j >= 0 && A[j] > temp)
            {
                A[j + gap] = A[j];
                j = j - gap;
            }
            A[j + gap] = temp;
        }
    }
}


#endif