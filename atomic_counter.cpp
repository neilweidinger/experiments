#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

void incrementCounter(std::atomic<int>& counter, int iterations);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Bruh pass in an iteration amount\n";
        return 1;
    }

    int iterations = std::atoi(argv[1]);
    int num_threads = 3;
    std::atomic<int> counter(0);

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

void incrementCounter(std::atomic<int>& counter, int iterations) {
    for (int i = 0; i < iterations; i++) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}
