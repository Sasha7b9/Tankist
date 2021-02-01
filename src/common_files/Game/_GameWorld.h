#pragma once


using namespace Pi;


class GameWorld : public World
{
private:

    const LocatorMarker *spawnLocator = nullptr; //-V122

    ChaseCamera         chaseCamera;

    static const LocatorMarker *FindSpawnLocator(const Zone *zone);

public:

    GameWorld(pchar name);
    ~GameWorld();

    const LocatorMarker *GetSpawnLocator() const
    {
        return spawnLocator;
    }

    ChaseCamera *GetChaseCamera()
    {
        return &chaseCamera;
    }

    WorldResult::B Preprocess() override;
    void Render();
};
