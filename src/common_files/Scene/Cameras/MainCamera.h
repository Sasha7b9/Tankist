#pragma once


class MainCamera
{
public:

    MainCamera(Node *node, Context *context);

    void Update();

private:
    SharedPtr<Node> node;

    float yaw = 0.0f;
    float pitch = 0.0f;
};
