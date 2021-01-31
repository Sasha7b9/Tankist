#include "stdafx.h"


ChaseCamera::ChaseCamera() : FrustumCamera(2.0F, 1.0F)
{
    targetModel = nullptr;
}


ChaseCamera::~ChaseCamera()
{
}


void ChaseCamera::Move(void)
{
//    Model *model = GetTargetModel();
//    if(model)
//    {
//        CollisionData	data;
//
//        float x, y, z;
//
//        model->GetNodeTransform().GetEulerAngles(&x, &y, &z);
//
//        float azm = z;
//        float alt = 0.0F;
//
//        // Здесь мы рассчитываем локальную систему координат для камеры погони в зависимости от направления, которое смотрит игрок.
//
//        float cp = Cos(alt);
//        float sp = Sin(alt);
//
//        float ct = Cos(azm);
//        float st = Sin(azm);
//
//        Vector3D view(ct * cp, st * cp, sp);
//        Vector3D right(st, -ct, 0.0F);
//        Vector3D down = view % right;
//
//        // Мы собираемся разместить камеру позади плеера, но мы не хочу, чтобы камера прошла через любую геометрию, поэтому мы сделаем быстрый проверить на столкновение.
//
//        const Point3D &position = model->GetWorldPosition();
//        Point3D p1(position.x, position.y, position.z + 0.5F);
//        Point3D p2 = p1 - view * distance;
//
//        if(GetWorld()->DetectCollision(p1, p2, 0.3F, CollisionKind::Camera, &data))
//        {
//            // Что - то мешает, так что пододвиньте камеру ближе  игроку.
//
//            float t = data.param;
//            p2 = p1 * (1.0F - t) + p2 * t;
//        }
//
//        // Установите положение камеры и ориентацию.
//
//        SetNodeTransform(right, down, view, p2);
//    }
}
