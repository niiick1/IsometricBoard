#ifndef IMAGE_H
#define IMAGE_H


class Image
{
    public:
        Image(int w, int h);
        Image(const Image &img);

        void setPixel(unsigned argb, int x, int y);

        int getWidth() { return this->width; }
        int getHeight() { return this->height; }
        unsigned getPixel(int x, int y) { return pixels[x+y*this->width]; };
        unsigned* getPixels() { return this->pixels; }

        virtual ~Image();

    private:
        int width,
            height;

        unsigned* pixels;
};

#endif // IMAGE_H
