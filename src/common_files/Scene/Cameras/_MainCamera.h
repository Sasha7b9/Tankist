#pragma once


class MainCamera
{
public:

    MainCamera(Node *node, Context *context);

    void Update();

    void ConnectTo(Node *node);

private:
    SharedPtr<Node> node;
    Node *parent = nullptr;

    float yaw = 0.0f;
    float pitch = 0.0f;
};
