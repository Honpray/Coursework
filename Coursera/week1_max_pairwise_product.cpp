#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int64_t MaxPairwiseProductFast(const vector<int>& numbers)
{
    int index1 = 0, index2 = 0;
    int n = numbers.size();
    for (int i = 1; i < n; ++i) {
        if (numbers[i] > numbers[index1])
            index1 = i;
    }
    if (index1 == 0)
        index2 = 1; // let index2 skip the largest and first number
    for (int i = 1; i < n; ++i) {
        if (numbers[i] > numbers[index2] && i != index1)
            index2 = i;
    }
    return numbers[index1] * numbers[index2];
}

int main()
{
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    int64_t result = MaxPairwiseProductFast(numbers);
    cout << result << "\n";
    return 0;
}
// Sort and select is faster.
