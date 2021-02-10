#include "stdafx.h"


const float CAMERA_DISTANCE = 10.0f;


MainCamera::MainCamera(Node *node, Context *context)
{
    Camera *camera = (new Node(context))->CreateComponent<Camera>();
    camera->GetNode()->SetPosition({ 0.0, 2.0, -3.0 });
    camera->SetFarClip(500.0f);
    TheRenderer->SetViewport(0, new Viewport(context, TheScene, camera));
    node->AddChild(camera->GetNode());
}


void MainCamera::SetOnNode(Node *target, float yaw, float pitch)
{
    // Physics update has completed. Position camera behind vehicle
    Quaternion dir(target->GetRotation().YawAngle(), Vector3::UP);
    dir = dir * Quaternion(yaw, Vector3::UP);
    dir = dir * Quaternion(pitch, Vector3::RIGHT);

    Vector3 cameraTargetPos = target->GetPosition() - dir * Vector3(0.0f, 0.0f, CAMERA_DISTANCE);
    Vector3 cameraStartPos = target->GetPosition();

    // Raycast camera against static objects (physics collision mask 2)
    // and move it closer to the vehicle if something in between
    Ray cameraRay(cameraStartPos, cameraTargetPos - cameraStartPos);

    float cameraRayLength = (cameraTargetPos - cameraStartPos).Length();

    PhysicsRaycastResult result;

    TheScene->GetComponent<PhysicsWorld>()->RaycastSingle(result, cameraRay, cameraRayLength, 2);

    if (result.body_)
    {
        cameraTargetPos = cameraStartPos + cameraRay.direction_ * (result.distance_ - 0.5f);
    }

    node->SetPosition(cameraTargetPos);
    node->SetRotation(dir);
}
