#pragma once
#include <eendgine/camera.hpp>

namespace Eend = Eendgine;


class Cameras {
    public:
        Cameras(Eend::Camera2D hudCamera, Eend::Camera3D sceneCamera);
        Eend::Camera2D& getHud() { return _hud; }; 
        Eend::Camera3D& getScene() { return _scene; };
    private:
        Eend::Camera2D _hud;
        Eend::Camera3D _scene;
};
