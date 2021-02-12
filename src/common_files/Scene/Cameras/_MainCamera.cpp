#include "stdafx.h"


const float CAMERA_DISTANCE = 10.0f;


MainCamera::MainCamera(Node *node, Context *context)
{
    Camera *camera = (new Node(context))->CreateComponent<Camera>();
    this->node = camera->GetNode();
    this->node->SetPosition({ 0.0f, 30.0f, -0.1f });
    camera->SetFarClip(500.0f);
    TheRenderer->SetViewport(0, new Viewport(context, TheScene, camera));

    ConnectTo(node);
}


void MainCamera::ConnectTo(Node *n)
{
    if (parent)
    {
        parent->RemoveChild(this->node);
    }

    parent = n;

    if (parent)
    {
        parent->AddChild(this->node);
    }
}


void MainCamera::Update()
{
    yaw += (float)TheMouse->GetMoveX() * YAW_SENSITIVITY;
    pitch += (float)TheMouse->GetMoveY() * YAW_SENSITIVITY;

    pitch = Clamp(pitch, 0.0f, 80.0f);

    Quaternion dir(parent ? parent->GetRotation().YawAngle() : 0.0f, Vector3::UP);  // Ќаправление машинки в горизонатальной плоскости

    dir = dir * Quaternion(yaw, Vector3::UP);                       // ƒобавл€ем рысканье камеры
    dir = dir * Quaternion(pitch, Vector3::RIGHT);                  // ƒобавл€ем поворот камеры по вертикали

    node->SetWorldRotation(dir);
}
