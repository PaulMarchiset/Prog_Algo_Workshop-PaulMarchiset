#include <sil/sil.hpp>

void onlyGreen(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
}

int main()
{
    sil::Image image{"images/logo.png"};
    onlyGreen(image);
    image.save("output/pouet.png");
}