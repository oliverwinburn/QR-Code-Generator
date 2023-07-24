#include <fstream>
#include <iostream>
#include <string>

int main() {
    constexpr auto dimx = 16u;
    constexpr auto dimy = 16u;
    std::string WHITE{static_cast<char>(255), static_cast<char>(255), static_cast<char>(255)};
    std::string BLACK{static_cast<char>(0), static_cast<char>(0), static_cast<char>(0)};

    std::ofstream file("out.ppm", std::ios_base::out | std::ios_base::binary);
    file << "";
    file << "P6\n"
         << dimx << " " << dimy << " "
         << "\n255\n";

    std::string output = "";

    for (auto j = 0u; j < dimy; ++j) {
        for (auto i = 0u; i < dimx; ++i) {
            output += (i < 7 && j < 10) ? WHITE : BLACK;
        }
    }
    file << output;
    file.close();

    return 0;
}
