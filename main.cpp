#include <iostream>
#include <cmath>
#include <chrono>

namespace sortlib
{
    template <class T>
    struct sorting
    {
        static void bubble(T *arr, int n)
        {
            for (int i = 0, c; i < n; ++i)
            {
                c = 1;
                for (int j = 0, k = 1; j < n - 1; ++j, ++k)
                {
                    if (arr[j] > arr[k])
                    {
                        swap(arr[j], arr[k]);
                        c = 0;
                    }
                }
                if (c)
                    return;
            }
        }
        static void selection(T *arr, int n)
        {
            for (int i = 0, k = 0; i < n - 1; ++i, ++k)
            {
                for (int j = i; j < n; ++j)
                {
                    if (arr[j] < arr[k])
                    {
                        k = j;
                    }
                }
                swap(arr[i], arr[k]);
            }
        }
        static void insertion(T *arr, int n)
        {
            for (int i = 1; i < n; ++i)
            {
                int j = i - 1, k = i;
                while (arr[k] <= arr[j] && j >= 0)
                {
                    swap(arr[k], arr[j]);
                    --j, --k;
                }
            }
        }

        static int sort(T *arr, int s, int e)
        {
            int p_index = (s + e) / 2;
            swap(arr[p_index], arr[e]);
            int index = s; // correct index of the pivot
            for (int i = s; i < e; ++i)
            {
                if (arr[i] <= arr[e])
                {
                    swap(arr[i], arr[index]);
                    index++;
                }
            }
            swap(arr[e], arr[index]);
            return index;
        }
        static void merge(T *arr, int start, int mid, int end)
        {
            int i = start, j = mid + 1, k = start;
            T tmp[end + 1];
            while (i <= mid && j <= end)
            {
                if (arr[i] <= arr[j])
                {
                    tmp[k] = arr[i];
                    ++i, ++k;
                }
                else if (arr[i] > arr[j])
                {
                    tmp[k] = arr[j];
                    ++j, ++k;
                }
            }
            if (i > mid)
            {
                for (int m = k; m < end + 1; ++m, ++j)
                {
                    tmp[m] = arr[j];
                }
            }
            else if (j > end)
            {
                for (int m = k; m < end + 1; ++m, ++i)
                {
                    tmp[m] = arr[i];
                }
            }

            for (int s = start; s <= end; ++s)
            {
                arr[s] = tmp[s];
            }
        }
        static void merge_sort(T *arr, int start, int end) // 1 2 3 5
        {
            if (start < end)
            {
                int m = (start + end) / 2;
                merge_sort(arr, start, m);
                merge_sort(arr, m + 1, end);
                merge(arr, start, m, end);
            }
        }
        static void quick(T *arr, int start, int end)
        {
            if (start >= end)
            {
                return;
            }
            int pivot = sort(arr, start, end);
            quick(arr, start, pivot - 1);
            quick(arr, pivot + 1, end);
        }

        static void shell_sort(T *arr, int n)
        {
            int num = 1;
            int gap = n / (pow(2, 0 + num));
            while (gap >= 1)
            {
                for (int i = gap; i < n; i += gap)
                {
                    int j = i - gap, k = i;
                    while (arr[k] <= arr[j] && j >= 0)
                    {
                        swap(arr[k], arr[j]);
                        k -= gap, j -= gap;
                    }
                }
                ++num;
                gap = n / (pow(2, 0 + num));
            }
        }
        static void count_sort(T *arr, int n, int r)
        {
            int range[r + 1]{0};
            T sorted_arr[n];
            for (int i = 0; i < n; ++i)
            {
                int index = (int)arr[i];
                ++range[index];
            }

            for (int i = 1; i <= r; ++i)
            {
                range[i] += range[i - 1];
            }

            for (int i = r; i >= 0; --i)
            {
                range[i] = range[i - 1];
            }
            range[0] = 0;

            for (int i = 0; i < n; ++i)
            {
                int index = (int)arr[i];
                sorted_arr[range[index]] = arr[i];
                ++range[index];
            }
            for (int i = 0; i < n; ++i)
            {
                arr[i] = sorted_arr[i];
            }
        }
    };
}
using namespace std;
using std::chrono::duration;
using std::chrono::milliseconds;
using namespace sortlib;

int main()
{
    // generate array
    int sz = 20000;
    int s[sz];
    for (int i = 0; i < sz; i++)
        s[i] = rand() % 1000;

    auto start = chrono::high_resolution_clock::now();
    sorting<int>::count_sort(s, sz, 999);
    auto stop = chrono::high_resolution_clock::now();
    duration<double, std::milli> ms_double = stop - start;
    cout << "Time taken by function: " << ms_double.count() << " ms" << endl;

    // sorting<float>::bubble(s, 9);
    // sorting<float>::insertion(s, 9);
    // sorting<float>::merge_sort(s, 0, 8);
    // sorting<float>::quick(s, 0, 8);
    // sorting<int>::count_sort(s, 9, 9);

    // print after sort

    // for (int i = 0; i < sz; ++i)
    // {
    //     cout << s[i] << " ";
    // }

    return 0;
}
