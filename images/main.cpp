#include "../headers/color.h"
#include "../headers/vec3.h"

#include <iostream>
#include <random>
#include <vector>

int main() {

    // Image

    int image_width = 512;
    int image_height = 512;

    // Render
    int max = 128;
    double offset = 0.5;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    int diff = 11;
    srand(time(NULL));
    int r = rand()%max;
    int g = rand()%max;
    int b = rand()%max;
    std::vector<std::vector<int>> image_row(int(image_width), {r, g, b});
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            if (j == 0) {
                for (int k = 0; k < 3; k++) {
                    image_row[i][k] = (image_row[i][k] + rand()%diff - (diff-1)/2);
                    image_row[i][k] %= max;
                }
            } else if (i == 0) {
                for (int k = 0; k < 3; k++) {
                    image_row[i][k] = (image_row[i][k] + image_row[i+1][k])/2 + rand()%diff - (diff-1)/2;
                    image_row[i][k] %= max;
                }
            }
            else if (i == image_width-1) {
                for (int k = 0; k < 3; k++) {
                    image_row[i][k] = (image_row[i][k] + image_row[i-1][k])/2 + rand()%diff - (diff-1)/2;
                    image_row[i][k] %= max;
                }
            } else {
                for (int k = 0; k < 3; k++) {
                    image_row[i][k] = (image_row[i][k] + image_row[i-1][k] + image_row[i+1][k])/3 + rand()%diff - (diff-1)/2;
                    image_row[i][k] %= max;
                }
            }
            auto pixel_color = color(offset + double(image_row[i][0]) / max, offset + double(image_row[i][1]) / max, offset + double(image_row[i][2]) / max);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}