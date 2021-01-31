#pragma once
#include "Objects/ChaseCamera.h"


enum
{
    kLocatorSpawn = 'spwn'
};



class GameWorld : public World
{
public:
    GameWorld(const char *name);
    ~GameWorld();

    Pi::WorldResult::B Preprocess();

    void Render() override;

    void Interact();

    const LocatorMarker *GetSpawnLocator() const
    {
        return spawnLocator;
    }

    ChaseCamera *GetChaseCamera()
    {
        return &chaseCamera;
    }

private:
    ChaseCamera         chaseCamera;
    const LocatorMarker *spawnLocator = nullptr;

    static const LocatorMarker *FindSpawnLocator(const Zone *zone);
};


