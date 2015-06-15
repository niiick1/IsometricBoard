#ifndef MODEL_H
#define MODEL_H

#include <string>

class Model
{
    public:
        Model();
        virtual ~Model();

        void loadTextureFromFile(std::string file);
        void update();
        void render(int x, int y);

        unsigned getTextureId() { return texId; }
    protected:
    private:
        int width,
            height;

        int currentFrame = 0,
            frames = 9;

        unsigned texId;

        float* texCoord[3];
};

#endif // MODEL_H
