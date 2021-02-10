#pragma once


class MainCamera
{
public:

    MainCamera(Context *context);

    void SetOnNode(Node *target, float yaw, float pitch);

private:
    SharedPtr<Node> node;
};
