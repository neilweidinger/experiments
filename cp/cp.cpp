#include <iostream>
#include <array>
#include <cstddef>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/errno.h>
#include <unistd.h>
#include <fcntl.h>

auto main(int argc, char* argv[]) -> int {
    if (argc != 3) {
        std::cerr << "Usage: cp source_file target_file\n";
        return 1;
    }

    auto source = open(argv[1], O_RDONLY);
    if (source == -1) {
        std::cerr << "Error opening source file: " << errno << "\n";
        return errno;
    }

    auto dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (source == -1) {
        std::cerr << "Error opening dest file: " << errno << "\n";
        return errno;
    }

    auto buf = std::array<std::byte, 4096> {};

    while (true) {
        ssize_t bytes_read = read(source, buf.data(), buf.max_size());

        if (bytes_read == -1) {
            std::cerr << "Error reading source: " << errno << "\n";
            return errno;
        }
        
        if (bytes_read == 0) {
            break;
        }

        if (auto ret = write(dest, buf.data(), bytes_read); ret == -1) {
            std::cerr << "Error writing to dest: " << errno << "\n";
            return errno;
        }
    }

    if (auto ret = close(source); ret == -1) {
        std::cerr << "Error closing source file: " << errno << "\n";
        return errno;
    }

    if (auto ret = close(dest); ret == -1) {
        std::cerr << "Error closing dest file: " << errno << "\n";
        return errno;
    }

    return 0;
}
