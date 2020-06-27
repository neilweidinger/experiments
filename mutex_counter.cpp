#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

static std::mutex counter_mutex;

void incrementCounter(int& counter, int iterations);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Bruh pass in an iteration amount\n";
        return 1;
    }

    int iterations = std::atoi(argv[1]);
    int num_threads = 3;
    int counter = 0;

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(incrementCounter, std::ref(counter), iterations));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Should be: " << iterations * num_threads << "\n";
    std::cout << "Counter: " << counter << "\n";

    return 0;
}

void incrementCounter(int& counter, int iterations) {
    std::lock_guard<std::mutex> lock(counter_mutex);

    for (int i = 0; i < iterations; i++) {
        counter++;
    }
}
