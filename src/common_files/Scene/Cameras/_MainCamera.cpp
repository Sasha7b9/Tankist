#include "stdafx.h"


const float CAMERA_DISTANCE = 10.0f;


MainCamera::MainCamera(Node *node, Context *context)
{
    Camera *camera = (new Node(context))->CreateComponent<Camera>();
    this->node = camera->GetNode();
    this->node->SetPosition({ 0.0f, 3.0f, -0.1f });
    camera->SetFarClip(500.0f);
    TheRenderer->SetViewport(0, new Viewport(context, TheScene->EngineScene(), camera));
    node->AddChild(this->node);
}


void MainCamera::Update()
{
    yaw += (float)TheInput->GetMouseMoveX() * YAW_SENSITIVITY;
    pitch += (float)TheInput->GetMouseMoveY() * YAW_SENSITIVITY;

    pitch = Clamp(pitch, 0.0f, 80.0f);

    Node *target = node->GetParent();

    Quaternion dir(target->GetRotation().YawAngle(), Vector3::UP);  // ����������� ������� � ��������������� ���������

    dir = dir * Quaternion(yaw, Vector3::UP);                       // ��������� �������� ������
    dir = dir * Quaternion(pitch, Vector3::RIGHT);                  // ��������� ������� ������ �� ���������

    node->SetWorldRotation(dir);
}
