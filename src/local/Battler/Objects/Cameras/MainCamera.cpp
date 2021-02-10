#include "stdafx.h"


const float CAMERA_DISTANCE = 10.0f;


MainCamera::MainCamera(Node *node, Context *context)
{
    Camera *camera = (new Node(context))->CreateComponent<Camera>();
    camera->GetNode()->SetPosition({ 0.0, 2.0, -1.0 });
    camera->SetFarClip(500.0f);
    TheRenderer->SetViewport(0, new Viewport(context, TheScene, camera));
    this->node = camera->GetNode();
    node->AddChild(this->node);
}


void MainCamera::Update()
{
    yaw += (float)TheInput->GetMouseMoveX() * YAW_SENSITIVITY;

    Node *target = node->GetParent();

    Quaternion dir(target->GetRotation().YawAngle(), Vector3::UP);  // ����������� ������� � ��������������� ���������

    dir = dir * Quaternion(yaw, Vector3::UP);                       // ��������� �������� ������

    node->SetWorldRotation(dir);
}
