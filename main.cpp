#include <fstream>
#include <string>
#include <vector>

void renderImage(std::vector<int> const &pixels, int dimx, int dimy) {
    std::string WHITE{static_cast<char>(255), static_cast<char>(255), static_cast<char>(255)};
    std::string BLACK{static_cast<char>(0), static_cast<char>(0), static_cast<char>(0)};
    std::string output = "";

    for (auto const &i : pixels) {
        output += (i % 2 == 1) ? WHITE : BLACK;
    }

    std::ofstream file("out.ppm", std::ios_base::out | std::ios_base::binary);
    file << "P6\n"
         << dimx << " " << dimy << " "
         << "\n255\n";

    file << output;
    file.close();
}

void addTrackers(std::vector<int> &pixels, int dimx, int dimy) {
    for (int n = 0; n < dimx * dimy; n++) {
        int x = n % dimx;
        int y = (n - x) / dimx;
        int &pixel = pixels[n];

        if ((x < 6 && (y == 0 || y == 24)) || (x > 18 && y == 0)) {
            pixel = 2;
        } else if ((y < 6 && (x == 0 || x == 24)) || (y > 18 && x == 0)) {
            pixel = 2;
        } else if (y == 6) {
            pixel = (6 < x && x < 18 && x % 2 == 1) ? 3 : 2;
        } else if (x == 6) {
            pixel = (6 < y && y < 18 && y % 2 == 1) ? 3 : 2;
        } else if (x == 18 && y < 6) {
            pixel = 2;
        } else if (y == 18 && x < 6) {
            pixel = 2;
        } else if ((1 < y && y < 5) && ((1 < x && x < 5) || (19 < x && x < 23))) {
            pixel = 2;
        } else if ((19 < y && y < 23) && (1 < x && x < 5)) {
            pixel = 2;
        }
        if (pixel == 1 && ((y < 6 && (x < 6 || x > 18)) || (y > 19 && x < 6))) {
            pixel = 3;
        }
    }


}

int main() {
    constexpr auto dimx = 25;
    constexpr auto dimy = 25;

    std::vector<int> pixels{};
    for (int i = 0; i < dimx * dimy; i++) {
        pixels.push_back(1);
    }

    addTrackers(pixels, dimx, dimy);

    // for (auto j = 0u; j < dimy; ++j) {
    //     for (auto i = 0u; i < dimx; ++i) {
    //         // bool pixel = (((i * j) % 2 + (i * j) % 3) % 2) ? 1 : 0;
    //         int pixel = 1;
    //     }
    // }

    renderImage(pixels, dimx, dimy);

    return 0;
}
