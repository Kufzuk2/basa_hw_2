#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>

void process_file(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream input(input_filename);
    std::ofstream output(output_filename);
    
    if (!input.is_open() || !output.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) continue;
        
        std::vector<int> numbers;
        std::istringstream iss(line);
        int first_num;
        
        if (!(iss >> first_num)) {
            continue;
        }
        
        int num;
        while (iss >> num) {
            numbers.push_back(num);
        }
        
        if (numbers.empty()) {
            continue;
        }
        
        clock_t start = clock();
        std::sort(numbers.begin(), numbers.end());
        clock_t end = clock();
        double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        
        output << first_num << " " << time << "\n";
    }
}

int main() {
    process_file("text_data/input_size.txt",   "text_data/std_sort_size.txt");
    process_file("text_data/input_unsort.txt", "text_data/std_sort_unsort.txt");
    process_file("text_data/input_radix.txt",  "text_data/std_sort_radix.txt");
    return 0;
}