#pragma once


class MainCamera
{
public:

    MainCamera(Node *node, Context *context);

    void SetOnNode(Node *target, float yaw, float pitch);

private:
    SharedPtr<Node> node;
};
