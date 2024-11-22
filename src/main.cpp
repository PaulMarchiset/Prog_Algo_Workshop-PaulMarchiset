#include "main.hpp"

void water(sil::Image &image)
{
    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int waterX{random_int(0, 5)};
            int waterY{random_int(0, 5)};

            if (x + waterX >= image.width())
            {
                new_image.pixel(x, y) = image.pixel(x, y);
            }
            else if (y + waterY >= image.height())
            {
                new_image.pixel(x, y) = image.pixel(x, y);
            }
            else
            {
                new_image.pixel(x, y) = image.pixel(x + waterX, y + waterY);
            }
        }
    }

    new_image.save("output/water.png");
}

int main()
{
    sil::Image image{"images/photo.jpg"};
    dithering(image);
    image.save("output/dithering.jpg");
}


// void printMatrix(const std::vector<std::vector<float>>& matrix) {
//     for (const auto& row : matrix) {
//         for (const auto& value : row) {
//             std::cout << value << "\t";
//         }
//         std::cout << "\n";
//     }
// }

// int main() {

//     int bayer_n = 4;

//     try {
//         auto bayerMatrix = generateBayerMatrix(bayer_n);
//         std::cout << "Bayer Matrix of size " << bayer_n << "x" << bayer_n << ":\n";
//         printMatrix(bayerMatrix);
//     } catch (const std::invalid_argument& e) {
//         std::cerr << "Error: " << e.what() << "\n";
//     }

//     return 0;
// }