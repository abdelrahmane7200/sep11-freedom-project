#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void testWithNumbers() {
    std::vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Original vector: ";
    for (int number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    // Sort from small -> big
    std::sort(numbers.begin(), numbers.end());

    std::cout << "Sorted vector: ";
    for (int number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    // Find the maximum element
    int max_number = *std::max_element(numbers.begin(), numbers.end());
    std::cout << "Maximum element: " << max_number << std::endl;

    // Reverse the vector
    std::reverse(numbers.begin(), numbers.end());
    std::cout << "Reversed vector: ";
    for (int number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

void testWithWords() {
    std::vector<std::string> names = {"Bob", "Alice", "Maxine", "Jackson", "Perry"};

    std::cout << "Original vector: ";
    for (std::string number : names) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    // Sort from small -> big
    std::sort(names.begin(), names.end());

    std::cout << "Sorted vector: ";
    for (std::string number : names) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    // Find the maximum element
    std::string max_name = *std::max_element(names.begin(), names.end());
    std::cout << "Maximum element: " << max_name << std::endl;

    // Reverse the vector
    std::reverse(names.begin(), names.end());
    std::cout << "Reversed vector: ";
    for (std::string number : names) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

int main() {
    testWithNumbers();
    // testWithWords();

    return 0;
}
