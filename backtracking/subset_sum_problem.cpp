#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <chrono>

struct set {
    std::vector<unsigned> arr;
    unsigned target;
    set(size_t size, unsigned max_val);
    ~set();
};

set::set(size_t size, unsigned max_val)
{
    this->arr = std::vector<unsigned>(size);
    this->target = 0;
    for (size_t i = 0; i < size; i++) {
        arr[i] = rand() % max_val;
        if (rand() % 2) {
            this->target += arr[i];
        }
    }
}

set::~set()
{
}

bool ssp_bruteforce(std::vector<unsigned>& set, std::vector<unsigned>& subset, unsigned n, unsigned sum)
{
    if (sum == 0)
        return true;
    
    if (n == 0 && sum != 0)
        return false;
    
    if (ssp_bruteforce(set, subset, n - 1, sum))
        return true;

    if (ssp_bruteforce(set, subset, n - 1, sum - set[n - 1])) {
        subset.push_back(set[n - 1]);
        return true;
    }

    return false;
}

bool ssp_backtracking(const std::vector<unsigned>& set, int n, int targetSum, std::vector<unsigned>& currentSubset, int currentIndex) {
    if (targetSum == 0) {
        return true;
    }

    for (int i = currentIndex; i < n; ++i) {
        currentSubset.push_back(set[i]);
        if (ssp_backtracking(set, n, targetSum - set[i], currentSubset, i + 1)) {
            return true;
        }
        currentSubset.pop_back();
    }

    return false; 
}

// Operator overload to print std::vector<unsigned>
std::ostream &operator<<(std::ostream &os, std::vector<unsigned> vec)
{
    os << "{ ";
    std::copy(vec.begin(), --vec.end(), std::ostream_iterator<unsigned>(os, ", "));
    os << vec.back() << " }";
    return os;
}

void test_bruteforce(set& set) {
    std::vector<unsigned> subset;
    auto begin = std::chrono::high_resolution_clock::now();
    bool res = ssp_bruteforce(set.arr, subset, set.arr.size(), set.target);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    if (res) {
        std::cout << "[Bruteforce] - Solution found\nset size: " << set.arr.size() << "\ntime: " << time << "us\n";
    } else {
        std::cout << "[Bruteforce] - No solution found\nset size: " << set.arr.size() << "\ntime: " << time << "us\n";
    }
}

void test_backtracking(set& set) {
    std::vector<unsigned> subset;
    auto begin = std::chrono::high_resolution_clock::now();
    bool res = ssp_backtracking(set.arr, set.arr.size(), set.target, subset, 0);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    if (res) {
        std::cout << "[Backtracking] - Solution found\nset size: " << set.arr.size() << "\ntime: " << time << "us\n";
    } else {
        std::cout << "[Backtracking] - No solution found\nset size: " << set.arr.size() << "\ntime: " << time << "us\n";
    }
}

int main()
{
    int sizes[] = { 10, 25, 50 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            srand(time(NULL));
            set set(sizes[i], sizes[i]);
            test_backtracking(set);
            test_bruteforce(set);
        }
    }
    return 0;
}
