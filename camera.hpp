#pragma once
#include "types.hpp"

namespace Eendgine {
class Camera2D {
    public:
        Camera2D(int width, int height);
        Point2D convertScreenToWorld(Point2D screenChoords);

        void setPosition(float x, float y) {
            _position = Point2D(x, y);
            update();
        }
        void setScale(float scale) {
            _scale = scale;
            update();
        }

        Point2D getPosition() { return _position; }
        float getScale() { return _scale; }
        Scale2D getDimensions() { return Scale2D(_width, _height); }
        TransformationMatrix getCameraMatrix() { return _cameraMatrix; }

    private:
        void update();

        int _width, _height;
        float _scale;
        Point2D _position;
        TransformationMatrix _orthoMatrix;
        TransformationMatrix _cameraMatrix;
};
class Camera3D {
    public:
        Camera3D(float aspectRatio, Point position, Point target);

        // concider not updating and making do manually
        void setAspectRatio(float aspectRatio) {
            _aspectRatio = aspectRatio;
            update();
        };
        void setPosition(Point position) {
            _position = position;
            update();
        };
        void setTarget(Point target) {
            _target = target;
            update();
        };

        float getAspectRatio() { return _aspectRatio; };
        Point getPosition() { return _position; };
        Point getTarget() { return _target; };
        TransformationMatrix getViewMat() { return _viewMat; };
        TransformationMatrix getProjectionMat() { return _projectionMat; };

    private:
        void update();

        float _aspectRatio;
        Point _position;
        Point _target;
        TransformationMatrix _viewMat;
        TransformationMatrix _projectionMat;
};
} // namespace Eendgine
