#include "stdafx.h"


const float CAMERA_DISTANCE = 10.0f;


MainCamera::MainCamera(Context *context)
{
    node = new Node(context);
    Camera *camera = node->CreateComponent<Camera>();
    camera->SetFarClip(500.0f);
    TheRenderer->SetViewport(0, new Viewport(context, TheScene, camera));
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
