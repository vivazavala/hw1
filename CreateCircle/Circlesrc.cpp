#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int radius;
bool **image;

void renderPixel(int x, int y) {
    assert(x >= 0 && y >= 0 && x <= radius && y <= radius);
    image[x][y] = 1;
    image[y][x] = 1; //symmetric point of xy is yx
    // TODO:  light up the pixel's symmetric counterpart
}

void rasterizeArc(int r) {
    // TODO:  rasterize the arc using renderPixel to light up pixels
    int x = 0;
    int y = radius;
    int d = 3 - 2 * r;
    renderPixel(x, y);

    while (y >= x) {
        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;

        }
        else
            d = d + 4 * x + 6;
        renderPixel(x, y);
    }
}

// You shouldn't need to change anything below this point.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " circleSize\n";
        return 0;
    }

#ifdef _WIN32
    sscanf_s(argv[1], "%d", &radius);
#else
    sscanf(argv[1], "%d", &radius);
#endif
    if (radius <= 0) {
        cout << "Image must be of positive size.\n";
        return 0;
    }

    // reserve image as 2d array
    image = new bool*[radius+1];
    for (int i = 0; i <= radius; i++) image[i] = new bool[radius+1];

    rasterizeArc(radius);

    char filename[50];
#ifdef _WIN32
    sprintf_s(filename, 50, "circle%d.ppm", radius);
#else
    sprintf(filename, "circle%d.ppm", radius);
#endif

    ofstream outfile(filename);
    outfile << "P3\n# " << filename << "\n";
    outfile << radius+1 << ' ' << radius+1 << ' ' << 1 << endl;

    for (int i = 0; i <= radius; i++)
    for (int j = 0; j <= radius; j++)
        outfile << image[radius-i][j] << " 0 0\n";

    // delete image data
    for (int i = 0; i <= radius; i++) delete [] image[i];
    delete [] image;

    return 0;
}
