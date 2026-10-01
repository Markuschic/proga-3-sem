#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

void randomfill(int *arr, size_t size)
{
    int min = 1;
    int max = 9;
    for (int i = 0; i < size; ++i)
    {
        arr[i] = min + rand() % (max - min + 1);
    }
}

void reverse(int *arr, size_t size)
{
    for (int i = 0; i != size / 2; ++i)
    {
        std::swap(arr[i], arr[size - i - 1]);
    }
}

void print(int *arr, size_t size)
{
    std::cout << " Your array: " << '\n';
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << '\t';
    }
}

void bubble(int *arr, size_t size)
{
    bool flag = true;
    while (flag == true)
    {
        flag = false;
        for (int i = 0; i < size - 1; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                std::swap(arr[i], arr[i + 1]);
                flag = true;
            }
        }
    }
}

void insert(int *arr, size_t size)
{
    for (int i = 1; i < size; ++i)
    {
        int timeindex = i;
        while (timeindex > 0 && arr[timeindex] < arr[timeindex - 1])
        {
            std::swap(arr[timeindex], arr[timeindex - 1]);
            --timeindex;
        }
    }
}

void select(int *arr, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        int smallest = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (arr[j] < arr[smallest])
            {
                std::swap(arr[j], arr[smallest]);
            }
        }
    }
}

void quick(int *arr, size_t size, int left, int right, int &max_depth, int current_depth = 1)
{
    if (current_depth > max_depth)
    {
        max_depth = current_depth;
    }
    if (left >= right)
    {
        return;
    }
    int half = arr[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j)
    {
        while (arr[i] < half)
        {
            ++i;
        }
        while (arr[j] > half)
        {
            --j;
        }
        if (i <= j)
        {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }
    quick(arr, size, left, j, max_depth, current_depth + 1);
    quick(arr, size, i, right, max_depth, current_depth + 1);
}

void merge(int *arr, int left, int mid, int right)
{
    size_t leftpart = mid - left + 1;
    size_t rightpart = right - mid;
    int *timeleft = new int[leftpart];
    int *timeright = new int[rightpart];
    for (size_t i = 0; i < leftpart; ++i)
    {
        timeleft[i] = arr[left + i];
    }
    for (size_t j = 0; j < rightpart; ++j)
    {
        timeright[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < leftpart && j < rightpart)
    {
        if (timeleft[i] <= timeright[j])
        {
            arr[k++] = timeleft[i++];
        }
        else
        {
            arr[k++] = timeright[j++];
        }
    }
    while (i < leftpart)
    {
        arr[k++] = timeleft[i++];
    }
    while (j < rightpart)
    {
        arr[k++] = timeright[j++];
    }
    delete[] timeleft;
    delete[] timeright;
}

void merge_sort(int *arr, int left, int right, int &max_depth, int current_depth = 1)
{
    if (current_depth > max_depth)
    {
        max_depth = current_depth;
    }
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid, max_depth, current_depth + 1);
        merge_sort(arr, mid + 1, right, max_depth, current_depth + 1);
        merge(arr, left, mid, right);
    }
}

template <class T>
bool comparator(const T &a, const T &b)
{
    return a < b;
}

int leftchild(int number)
{
    return 2 * number + 1;
}

int rightchild(int number)
{
    return 2 * number + 2;
}

template <class T>
void heapify(T *arr, size_t size, int root, bool (*compare)(const T &a, const T &b), int &max_depth, int current_depth = 1)
{
    if (current_depth > max_depth)
    {
        max_depth = current_depth;
    }
    int left = leftchild(root);
    int right = rightchild(root);
    int largest = root;
    if (left < size && compare(arr[largest], arr[left]))
    {
        largest = left;
    }
    if (right < size && compare(arr[largest], arr[right]))
    {
        largest = right;
    }
    if (largest != root)
    {
        std::swap(arr[largest], arr[root]);
        heapify(arr, size, largest, compare, max_depth, current_depth + 1);
    }
}

template <class T>
void heap_build(T *arr, size_t size, bool (*compare)(const T &a, const T &b), int &max_depth)
{
    for (int i = size / 2 - 1; i >= 0; --i)
    {
        heapify(arr, size, i, compare, max_depth, 1);
    }
}

template <class T>
void heap_sort(T *arr, size_t size, bool (*compare)(const T &a, const T &b), int &max_depth)
{
    heap_build(arr, size, compare, max_depth);
    for (int i = size - 1; i > 0; --i)
    {
        std::swap(arr[i], arr[0]);
        heapify(arr, i, 0, compare, max_depth, 1);
    }
}

void countingSort(int *arr, size_t size)
{
    if (size <= 1)
    {
        return;
    }
    int max_value = arr[0];
    for (int i = 1; i < size; ++i)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    int *counter = new int[max_value + 1]{};
    for (int i = 0; i < size; ++i)
    {
        counter[arr[i]]++;
    }
    int index = 0;
    for (int i = 0; i <= max_value; ++i)
    {
        while (counter[i] > 0)
        {
            arr[index++] = i;
            counter[i]--;
        }
    }
    delete[] counter;
}

void countSortDigit(int *arr, size_t size, int exp)
{
    int *output = new int[size];
    int count[10] = {0};
    for (int i = 0; i < size; ++i)
    {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; ++i)
    {
        count[i] += count[i - 1];
    }
    for (int i = static_cast<int>(size) - 1; i >= 0; --i)
    {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    for (int i = 0; i < size; ++i)
    {
        arr[i] = output[i];
    }
    delete[] output;
}

void radixSort(int *arr, size_t size)
{
    if (size <= 1)
    {
        return;
    }
    int max_value = arr[0];
    for (int i = 1; i < size; ++i)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    for (int rank = 1; max_value / rank > 0; rank *= 10)
    {
        countSortDigit(arr, size, rank);
    }
}

void bucketSort(int *arr, size_t size, int &max_depth)
{
    if (size <= 1)
    {
        return;
    }
    int bucketCount = 10;
    int min_value = arr[0], max_value = arr[0];
    for (size_t i = 1; i < size; ++i)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    int **buckets = new int *[bucketCount];
    int *bucketSizes = new int[bucketCount]{};

    for (int i = 0; i < bucketCount; ++i)
    {
        buckets[i] = new int[size];
    }
    int range = max_value - min_value + 1;
    for (int i = 0; i < size; ++i)
    {
        size_t bucketIndex = (arr[i] - min_value) * bucketCount / range;

        if (bucketIndex >= bucketCount)
        {
            bucketIndex = bucketCount - 1;
        }
        buckets[bucketIndex][bucketSizes[bucketIndex]] = arr[i];
        bucketSizes[bucketIndex]++;
    }
    int index = 0;
    for (int i = 0; i < bucketCount; ++i)
    {
        if (bucketSizes[i] > 0)
        {
            quick(buckets[i], bucketSizes[i], 0, bucketSizes[i] - 1, max_depth, 1);

            for (int j = 0; j < bucketSizes[i]; ++j)
            {
                arr[index++] = buckets[i][j];
            }
        }
    }
    for (int i = 0; i < bucketCount; ++i)
    {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
}

void almostSort(int *arr, size_t size)
{
    std::sort(arr, arr + size);
    size_t swaps = static_cast<size_t>(size * 0.05 / 2);
    if (swaps == 0)
    {
        swaps = 1;
    }
    for (int i = 0; i < swaps; ++i)
    {
        size_t a = rand() % size;
        size_t b = rand() % size;
        std::swap(arr[a], arr[b]);
    }
}

int main()
{
    srand(time(0));
    size_t size;
    std::cout << " Enter the size " << '\n';
    std::cin >> size;
    int *arr = new int[size];
    int *copyarr = new int[size];

    randomfill(arr, size);
    std::cout << '\n';

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    int max_depth = 0;

    std::copy(arr, arr + size, copyarr);
    start = std::chrono::high_resolution_clock::now();
    bubble(copyarr, size);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Bubble Sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << '\n';

    std::copy(arr, arr + size, copyarr);
    start = std::chrono::high_resolution_clock::now();
    select(copyarr, size);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Selection Sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << '\n';

    std::copy(arr, arr + size, copyarr);
    start = std::chrono::high_resolution_clock::now();
    insert(copyarr, size);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Insertion Sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << '\n';

    std::copy(arr, arr + size, copyarr);
    max_depth = 0;
    start = std::chrono::high_resolution_clock::now();
    quick(copyarr, size, 0, size - 1, max_depth);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Quick sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << " Max recursion depth: " << max_depth << '\n';
    std::cout << '\n';

    std::copy(arr, arr + size, copyarr);
    max_depth = 0;
    start = std::chrono::high_resolution_clock::now();
    merge_sort(copyarr, 0, size - 1, max_depth);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Merge Sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << " Max recursion depth: " << max_depth << '\n';
    std::cout << '\n';

    std::copy(arr, arr + size, copyarr);
    max_depth = 0;
    start = std::chrono::high_resolution_clock::now();
    heap_sort(copyarr, size, comparator<int>, max_depth);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Heap Sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << " Max recursion depth: " << max_depth << '\n';
    std::cout << '\n';

    std::copy(arr, arr + size, copyarr);
    start = std::chrono::high_resolution_clock::now();
    countingSort(copyarr, size);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Counting sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << '\n';

    std::copy(arr, arr + size, copyarr);
    start = std::chrono::high_resolution_clock::now();
    radixSort(copyarr, size);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Radix Sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << '\n';

    std::copy(arr, arr + size, copyarr);
    max_depth = 0;
    start = std::chrono::high_resolution_clock::now();
    bucketSort(copyarr, size, max_depth);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << " Bucket Sort " << '\n';
    std::cout << " Time: " << std::fixed << std::setprecision(10) << duration_ms << " ms " << '\n';
    std::cout << " Max recursion depth: " << max_depth << '\n';
    delete[] arr;
    return 0;
}