#include "canvas.hpp"
#include <algorithm>
#include <fstream>
#include <ostream>

Vec3 & Canvas::get_pixel(int x,int y) {
    return pixels[y*res_x+x];
}

const Vec3 & Canvas::get_pixel(int x,int y) const {
    return pixels[y*res_x+x];
}

void Canvas::put_pixel(Vec3 color, int x,int y) {
    pixels[y*res_x+x] = color;
}

std::ostream & operator << (std::ostream & out, const Canvas & c) {
    out << c.res_x << "x" << c.res_y << "\n";
    for (int y=0;y<c.res_y;y++) {
        for (int x=0;x<c.res_x;x++) {
            const Vec3 & pixel = c.get_pixel(x,y);

            out << pixel << ",";
        }
        out << "\n";
    }

    return out;
}

void save_img(const Canvas & canvas,const std::string & path) {
    std::ofstream out(path.c_str());

    out << "P3\n" << canvas.res_x << " " << canvas.res_y << "\n255\n";

    for (int y=0;y<canvas.res_y;y++) {
        for (int x=0;x<canvas.res_x;x++) {
            const Vec3 & pixel = canvas.get_pixel(x,y);

            int r = (int)(255.99*std::clamp(pixel.x,0.0,1.0));
            int g = (int)(255.99*std::clamp(pixel.y,0.0,1.0));
            int b = (int)(255.99*std::clamp(pixel.z,0.0,1.0));

            out << r << " " << g << " " << b << "\n";
        }
    }

    out.close();
}
