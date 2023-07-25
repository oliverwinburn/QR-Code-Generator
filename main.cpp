#include <fstream>
#include <list>
#include <string>

void renderImage(std::list<bool> const &pixels, int dimx, int dimy) {
    std::string WHITE{static_cast<char>(255), static_cast<char>(255), static_cast<char>(255)};
    std::string BLACK{static_cast<char>(0), static_cast<char>(0), static_cast<char>(0)};
    std::string output = "";

    for (auto const &i : pixels) {
        output += (i) ? WHITE : BLACK;
    }

    std::ofstream file("out.ppm", std::ios_base::out | std::ios_base::binary);
    file << "P6\n"
         << dimx << " " << dimy << " "
         << "\n255\n";

    file << output;
    file.close();
}

int main() {
    constexpr auto dimx = 16;
    constexpr auto dimy = 16;

    std::list<bool> pixels{};

    for (auto j = 0u; j < dimy; ++j) {
        for (auto i = 0u; i < dimx; ++i) {
            bool pixel = (i % 2 && j % 2) ? 1 : 0;
            pixels.push_back(pixel);
        }
    }

    renderImage(pixels, dimx, dimy);

    return 0;
}
