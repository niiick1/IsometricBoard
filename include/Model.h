#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "TilePosition.h"
#include "TileMapView.h"
#include "Sprite.h"
#include <map>

//Function pointer called CallbackType
typedef void(*CallbackType)();

class Model
{
    public:
        Model();
        virtual ~Model();

//        void loadTextureFromFile(std::string file);
        void addSpriteForDirection(const Sprite& sprite, TileOrientation direction);

        void update(CallbackType callback);
        void render(int x, int y);

        void walk(TileOrientation direction);

//        unsigned getTextureId() { return texId; }
        float getTime() { return time; }
        void setTime(float t) { time = t; }

        void setCurrentPosition(const TilePosition& tp);
        const TilePosition& getCurrentPosition() const { return currentPosition; }

        void setOldPosition(const TilePosition& tp) { oldPosition = tp; }
        const TilePosition& getOldPosition() const { return oldPosition; }

    protected:
    private:
        std::map<TileOrientation, Sprite> sprites;

        float time = 0,
            walkX, walkY, walkXFactor, walkYFactor;

        TilePosition oldPosition,
            currentPosition;

        TileOrientation direction = SOUTH;
};

#endif // MODEL_H
