#pragma once
#include "types.hpp"

namespace Eendgine {
class Camera2D {
    public:
        Camera2D(int width, int height);
        Point2D convertScreenToWorld(Point2D screenChoords);

        void setPosition(float x, float y) {
            m_position = Point2D(x, y);
            update();
        }
        void setScale(float scale) {
            m_scale = scale;
            update();
        }

        Point2D getPosition() { return m_position; }
        float getScale() { return m_scale; }
        Scale2D getDimensions() { return Scale2D(m_width, m_height); }
        TransformationMatrix getCameraMatrix() { return m_cameraMatrix; }

    private:
        void update();

        int m_width, m_height;
        float m_scale;
        Point2D m_position;
        TransformationMatrix m_orthoMatrix;
        TransformationMatrix m_cameraMatrix;
};
class Camera3D {
    public:
        Camera3D(float aspectRatio, Point position, Point target);

        // concider not updating and making do manually
        void setAspectRatio(float aspectRatio) {
            m_aspectRatio = aspectRatio;
            update();
        };
        void setPosition(Point position) {
            m_position = position;
            update();
        };
        void setTarget(Point target) {
            m_target = target;
            update();
        };

        float getAspectRatio() { return m_aspectRatio; };
        Point getPosition() { return m_position; };
        Point getTarget() { return m_target; };
        TransformationMatrix getViewMat() { return m_viewMat; };
        TransformationMatrix getProjectionMat() { return m_projectionMat; };

    private:
        void update();

        float m_aspectRatio;
        Point m_position;
        Point m_target;
        TransformationMatrix m_viewMat;
        TransformationMatrix m_projectionMat;
};

class Cameras {
    public:
        static void construct(const Camera2D& hudCamera, const Camera3D& sceneCamera);
        static void destruct();

        static Camera2D& getHud();
        static Camera3D& getScene();

    private:
        Cameras() = default;
        ~Cameras() = default;

        Cameras(const Cameras&) = delete;
        Cameras& operator=(const Cameras&) = delete;

        Cameras(Cameras&& other) = delete;
        Cameras& operator=(Cameras&& other) = delete;

        static Camera2D* m_instance2D;
        static Camera3D* m_instance3D;
};

} // namespace Eendgine
