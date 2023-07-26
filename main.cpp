#include <fstream>
#include <string>
#include <vector>

void renderImage(std::vector<int> const &pixels, int dimx, int dimy) {
    std::string WHITE{(char)255, (char)255, (char)255};
    std::string BLACK{(char)0, (char)0, (char)0};
    std::string RED{(char)255, (char)0, (char)0};
    std::string GREEN{(char)0, (char)255, (char)0};
    std::string BLUE{(char)0, (char)0, (char)255};
    std::vector<std::string> colours = {BLACK, WHITE, RED, GREEN, BLUE};

    std::string output = "";

    for (auto const &i : pixels) {
        output += colours[i]; //(i % 2 == 1) ? WHITE : BLACK;
    }

    std::ofstream file("out.ppm", std::ios_base::out | std::ios_base::binary);
    file << "P6\n"
         << dimx << " " << dimy << " "
         << "\n255\n";

    file << output;
    file.close();
}

void addTrackers(std::vector<int> &pixels, int dim) {
    for (int n = 0; n < dim * dim; n++) {
        int x = n % dim;
        int y = (n - x) / dim;
        int &pixel = pixels[n];
        int boxEdge = dim - 7;

        if ((x < 6 && (y == 0 || y == (dim - 1) || y == boxEdge)) || (x > boxEdge && y == 0)) {
            pixel = 0; // lines on top and bottom
        } else if ((y < 6 && (x == 0 || x == (dim - 1) || x == boxEdge)) || (y > boxEdge && x == 0)) {
            pixel = 0; // lines on left and right
        } else if (y == 6) { // horizontal dotted lines
            pixel = (6 < x && x < boxEdge && x % 2 == 1) ? 1 : 0;
        } else if (x == 6) { // vertical dotted lines
            pixel = (6 < y && y < boxEdge && y % 2 == 1) ? 1 : 0;
        } else if ((1 < y && y < 5) && ((1 < x && x < 5) || ((boxEdge + 1) < x && x < (boxEdge + 5)))) {
            pixel = 0; // boxes in top trackers
        } else if (((boxEdge + 1) < y && y < (boxEdge + 5)) && (1 < x && x < 5)) {
            pixel = 0; // box in bottom tracker
        } else if ((dim - 4) > y && y > (dim - 10) && (dim - 4) > x && x > (dim - 10)) {
            // tracker in bottom right
            if (x == (dim - 7) && y == (dim - 7)) {
                pixel = 0; // black dot
            } else if (x == (dim - 9) || y == (dim - 9) || x == (dim - 5) || y == (dim - 5)) {
                pixel = 0; // black ring
            } else {
                pixel = 1; // white ring
            }
        }

        if (pixel != 0 && ((y < 8 && (x < 8 || x > (boxEdge - 2))) || (y > (boxEdge - 2) && x < 8))) {
            pixel = 1; // white fill
        }
    }
}

int main() {
    constexpr auto dimx = 29;
    constexpr auto dimy = 29;

    std::vector<int> pixels{};
    for (int i = 0; i < dimx * dimy; i++) {
        pixels.push_back(2);
    }

    addTrackers(pixels, dimx);

    // for (auto j = 0u; j < dimy; ++j) {
    //     for (auto i = 0u; i < dimx; ++i) {
    //         // bool pixel = (((i * j) % 2 + (i * j) % 3) % 2) ? 1 : 0;
    //         int pixel = 1;
    //     }
    // }

    renderImage(pixels, dimx, dimy);

    return 0;
}
