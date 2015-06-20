#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "TilePosition.h"
#include "TileMapView.h"

class Model
{
    public:
        Model();
        virtual ~Model();

        void loadTextureFromFile(std::string file);
        void update();
        void render(int x, int y);

        void walk(TileOrientation direction);

        unsigned getTextureId() { return texId; }
        float getTime() { return time; }
        void setTime(float t) { time = t; }

        void setCurrentPosition(const TilePosition& tp);
        const TilePosition& getCurrentPosition() const { return currentPosition; }

        void setOldPosition(const TilePosition& tp) { oldPosition = tp; }
        const TilePosition& getOldPosition() const { return oldPosition; }
    protected:
    private:
        int width,
            height;

        unsigned texId;

        int currentFrame = 0,
            frames = 9;

        float time = 0,
            walkX, walkY, walkXFactor, walkYFactor;

        TilePosition oldPosition,
            currentPosition;

        TileOrientation direction;
};

#endif // MODEL_H
