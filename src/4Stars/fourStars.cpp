#include "fourStars.hpp"

void mosaique(sil::Image &image)
{

    int rows{5};
    int cols{5};

    sil::Image new_image{image.width() * 5, image.height() * 5};

    for (int i{0}; i < rows; i++)
    {
        for (int j{0}; j < cols; j++)
        {
            for (int x{0}; x < image.width(); x++)
            {
                for (int y{0}; y < image.height(); y++)
                {
                    new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(x, y);
                }
            }
        }
    }

    new_image.save("output/mosaique.png");
}

void mosaiqueMirror(sil::Image &image)
{
    int rows{5};
    int cols{5};

    sil::Image new_image{image.width() * 5, image.height() * 5};

    for (int i{0}; i < rows; i++)
    {
        for (int j{0}; j < cols; j++)
        {
            for (int x{0}; x < image.width(); x++)
            {
                for (int y{0}; y < image.height(); y++)
                {
                    int newX{image.width() - 1 - x};
                    int newY{image.height() - 1 - y};

                    if (i % 2 == 1 && j % 2 == 1)
                    {
                        new_image.pixel(newX + i * image.width(), newY + j * image.height()) = image.pixel(x, y);
                    }
                    else if (i % 2 == 1)
                    {
                        new_image.pixel(newX + i * image.width(), y + j * image.height()) = image.pixel(x, y);
                    }
                    else if (j % 2 == 1)
                    {
                        new_image.pixel(x + i * image.width(), newY + j * image.height()) = image.pixel(x, y);
                    }
                    else
                    {
                        new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(x, y);
                    }
                }
            }
        }
    }

    new_image.save("output/mosaiqueMirror.png");
}

void fractalMandelbrot(sil::Image &image)
{

    int maxInteration{1000};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::complex<float> c{(static_cast<float>(x) / image.width() * 3.f - 2.f), (static_cast<float>(y) / image.height() * 3.f - 1.5f)};
            std::complex<float> z{0.f, 0.f};

            for (int i{0}; i < maxInteration && std::abs(z) < 2.f; i++)
            {
                z = z * z + c;

                if (i == maxInteration - 1)
                {
                    image.pixel(x, y) = glm::vec3{1.f};
                    break;
                }
                else
                {
                    float color = static_cast<float>(i) / maxInteration;
                    image.pixel(x, y) = glm::vec3{color, color, color};
                }
            }
        }
    }
}

std::vector<std::vector<float>> generateBayerMatrix(int bayer_n)
{

    std::vector<std::vector<float>> bayerMatrix{{0.f/4.f, 2.f/4.f}, {3.f/4.f, 1.f/4.f}};

    while (bayerMatrix.size() < bayer_n)
    {
        int size = bayerMatrix.size();
        std::vector<std::vector<float>> newMatrix(size * 2, std::vector<float>(size * 2));

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                newMatrix[i][j] = (bayerMatrix[i][j] * pow(bayerMatrix.size() * 2, 2) )  / pow(bayerMatrix.size() * 2, 2) ;
                newMatrix[i][j + size] = (bayerMatrix[i][j]  * pow(bayerMatrix.size() * 2, 2) + 2) / pow(bayerMatrix.size() * 2, 2)  ;
                newMatrix[i + size][j] = (bayerMatrix[i][j]  * pow(bayerMatrix.size() * 2, 2) + 3) / pow(bayerMatrix.size() * 2, 2)  ;
                newMatrix[i + size][j + size] = (bayerMatrix[i][j]  * pow(bayerMatrix.size() * 2, 2) +1 ) / pow(bayerMatrix.size() * 2, 2) ;
            }
        }
        bayerMatrix = std::move(newMatrix);
    }

    return bayerMatrix;
}

void dithering(sil::Image &image)
{

    int bayer_n{4};
    std::cout << "Entrez la taille de la matrice de Bayer : ";
    std::cin >> bayer_n;


    std::vector<std::vector<float>> bayer_matrix = generateBayerMatrix(bayer_n);


    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            glm::vec3 inputColor = image.pixel(x, y);

            float luminance{0.2126f * image.pixel(x, y).r + 0.7152f * image.pixel(x, y).g + 0.0722f * image.pixel(x, y).b};

            float value = luminance + bayer_matrix[x % bayer_n][y % bayer_n] - 0.5f> 0.5f ? 1.f : 0.f;
            image.pixel(x, y) = glm::vec3{value, value, value};

        }
    }
}