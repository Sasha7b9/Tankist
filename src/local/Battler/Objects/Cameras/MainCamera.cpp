#include "stdafx.h"



MainCamera::MainCamera(Context *context)
{
    node = new Node(context);
    Camera *camera = node->CreateComponent<Camera>();
    camera->SetFarClip(500.0f);
    TheRenderer->SetViewport(0, new Viewport(context, TheScene, camera));
}
