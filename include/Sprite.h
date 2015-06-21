#ifndef SPRITE_H
#define SPRITE_H

#include <string>

class Sprite
{
    public:
        Sprite();
        Sprite(std::string file, int frames);
        virtual ~Sprite();

        void loadTextureFromFile(std::string file, int frames);

        int getFrameWidth() { return frameWidth; }
        int getFrameHeight() { return frameHeight; }
        unsigned getTextureId() { return texId; }

        int getCurrentFrame() { return currentFrame; }
        void setCurrentFrame(int frame) { currentFrame = frame; }

        int getFrameCount() { return frames; }
    protected:
    private:
        int frameWidth,
            frameHeight;

        unsigned texId;

        int currentFrame = 0,
            frames = 0;
};

#endif // SPRITE_H
