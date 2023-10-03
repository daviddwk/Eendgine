#include <eendgine/sprite.hpp>

namespace Eendgine {
    bool collidesWith(Eendgine::Sprite *sprite1, Eendgine::Sprite *sprite2) {

        float xDistance = sprite1->x - sprite2->x;
        float xCollisionDepth = ((sprite1->w / 2) + (sprite2->w / 2)) - fabs(xDistance);
        float yDistance = sprite1->y - sprite2->y;
        float yCollisionDepth = ((sprite1->h / 2) + (sprite2->h / 2)) - fabs(yDistance); 

        return (xCollisionDepth > 0) && (yCollisionDepth > 0);
    }
    
}
