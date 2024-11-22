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
    image.save("output/pouet.png");
}