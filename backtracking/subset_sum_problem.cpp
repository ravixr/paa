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
        arr[i] = rand() % max_val + 1;
        if (rand() % 2) {
            this->target += arr[i];
        }
    }
}

set::~set()
{
}

size_t bf_comp = 0;
size_t bt_comp = 0;

bool ssp_bruteforce(std::vector<unsigned>& set, std::vector<unsigned>& subset, unsigned n, unsigned sum)
{
    bf_comp++;
    if (sum == 0) {
        return true;
    }
    bf_comp++;
    if (n == 0 && sum != 0) {
        return false;
    }
    bf_comp++;
    if (ssp_bruteforce(set, subset, n - 1, sum))
        return true;
    bf_comp++;
    if (ssp_bruteforce(set, subset, n - 1, sum - set[n - 1])) {
        subset.push_back(set[n - 1]);
        return true;
    }

    return false;
}

bool ssp_backtracking(const std::vector<unsigned>& set, int n, int targetSum, std::vector<unsigned>& currentSubset, int currentIndex) {
    bt_comp++;
    if (targetSum == 0) {
        return true;
    }

    for (int i = currentIndex; i < n; ++i) {
        currentSubset.push_back(set[i]);
        bt_comp++;
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
    bf_comp = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    bool res = ssp_bruteforce(set.arr, subset, set.arr.size(), set.target);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "bruteforce," << set.target << "," << set.arr.size() << "," << time << "," << bf_comp << "\n";
}

void test_backtracking(set& set) {
    std::vector<unsigned> subset;
    bt_comp = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    bool res = ssp_backtracking(set.arr, set.arr.size(), set.target, subset, 0);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "backtracking," << set.target << "," << set.arr.size() << "," << time << "," << bt_comp << "\n";
}

int main()
{
    int sizes[] = { 10, 20, 30, 40, 50 };
    std::cout << "algo,target,size,time,comp\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            srand(i ^ j ^ time(NULL));
            set set(sizes[i], sizes[i]);
            std::cout << set.arr << " " <<  set.target << "\n";
            test_backtracking(set);
            test_bruteforce(set);
        }
    }
    return 0;
}
