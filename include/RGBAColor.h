#ifndef RGBACOLOR_H
#define RGBACOLOR_H

class RGBAColor
{
    public:
        RGBAColor();
        RGBAColor(unsigned r, unsigned g, unsigned b, unsigned a = 255);
        RGBAColor(unsigned argb);
        virtual ~RGBAColor();

        unsigned toARGB();

        unsigned getARGB() { return this->argb; }
        unsigned getR() { return r; }
        void setR(unsigned val) { r = val; this->toARGB(); }
        unsigned getG() { return g; }
        void setG(unsigned val) { g = val; this->toARGB(); }
        unsigned getB() { return b; }
        void setB(unsigned val) { b = val; this->toARGB(); }
        unsigned getA() { return a; }
        void setA(unsigned val) { a = val; this->toARGB(); }
    protected:
    private:
        unsigned r;
        unsigned g;
        unsigned b;
        unsigned a;
        unsigned argb;
};

#endif // RGBACOLOR_H
