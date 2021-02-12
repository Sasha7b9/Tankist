#include "stdafx.h"


GameScene::GameScene(Context *context) : Scene(context)
{
}


GameScene::~GameScene()
{
}


void GameScene::Create()
{
    // Create scene subsystem components
    CreateComponent<Octree>();

#ifdef SERVER
    CreateComponent<PhysicsWorld>();
#endif

    // Create static scene content. First create a zone for ambient lighting and fog control
    Node *zoneNode = CreateChild("Zone");
    auto *zone = zoneNode->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(300.0f);
    zone->SetFogEnd(500.0f);
    zone->SetBoundingBox(BoundingBox(-2000.0f, 2000.0f));

    // Create a directional light with cascaded shadow mapping
    Node *lightNode = CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.3f, -0.5f, 0.425f));
    auto *light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetSpecularIntensity(0.5f);

    // Create heightmap terrain with collision
    Node *terrainNode = CreateChild("Terrain");
    terrainNode->SetPosition(Vector3::ZERO);
    auto *terrain = terrainNode->CreateComponent<Terrain>();
    terrain->SetPatchSize(64);
    terrain->SetSpacing(Vector3(3.0f, 0.1f, 3.0f)); // Spacing between vertices and vertical resolution of the height map
    terrain->SetSmoothing(true);
    terrain->SetHeightMap(TheCache->GetResource<Image>("Textures/HeightMap.png"));
    terrain->SetMaterial(TheCache->GetResource<Material>("Materials/Terrain.xml"));

    // The terrain consists of large triangles, which fits well for occlusion rendering, as a hill can occlude all
    // terrain patches and other objects behind it
    terrain->SetOccluder(true);
    auto *body = terrainNode->CreateComponent<RigidBody>();
    body->SetCollisionLayer(2); // Use layer bitmask 2 for static geometry
    auto *shape = terrainNode->CreateComponent<CollisionShape>();
    shape->SetTerrain();

    // Create 1000 mushrooms in the terrain. Always face outward along the terrain normal
    const unsigned NUM_MUSHROOMS = 1000;
    for (unsigned i = 0; i < NUM_MUSHROOMS; ++i)
    {
        Node *objectNode = CreateChild("Mushroom");
        Vector3 position(Random(2000.0f) - 1000.0f, 0.0f, Random(2000.0f) - 1000.0f);
        position.y_ = terrain->GetHeight(position) - 0.1f;
        objectNode->SetPosition(position);
        // Create a rotation quaternion from up vector to terrain normal
        objectNode->SetRotation(Quaternion(Vector3::UP, terrain->GetNormal(position)));
        objectNode->SetScale(3.0f);
        auto *object = objectNode->CreateComponent<StaticModel>();
        object->SetModel(TheCache->GetResource<Model>("Models/Mushroom.mdl"));
        object->SetMaterial(TheCache->GetResource<Material>("Materials/Mushroom.xml"));
        object->SetCastShadows(true);
        auto *b = objectNode->CreateComponent<RigidBody>();
        b->SetCollisionLayer(2);
        auto *s = objectNode->CreateComponent<CollisionShape>();
        s->SetTriangleMesh(object->GetModel(), 0);
    }
}
