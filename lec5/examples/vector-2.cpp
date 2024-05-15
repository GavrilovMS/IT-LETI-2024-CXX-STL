#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

int main() {
    size_t N;
    std::cin >> N;

    // плохо
    std::vector<int> vec1;
    for (size_t i = 0; i < N; i++) {
        int temp;
        std::cin >> temp;
        vec1.push_back(i);
    }

    // хорошо
    std::vector<int> vec2;
    vec2.reserve(N);
    std::istream_iterator<int> in_it(std::cin);
    std::copy_n(in_it, N, std::back_inserter(vec2));
    return 0;
}