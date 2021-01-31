#include <stdafx.h>
#include "GameWorld.h"
//#include "Objects/Tank.h"
#include "globals.h"
#include "GUI/GameGUI.h"



GameWorld::GameWorld(const char *name) :
    World(name)
{

}


GameWorld::~GameWorld()
{
//    Tank::Destruct();

    delete TheGameGUI;

    if (TheGizmo)
    {
        TheGizmo->~Gizmo();
    }
}


Pi::WorldResult::B GameWorld::Preprocess()
{
    Pi::WorldResult::B result = World::Preprocess();

    if (result != Pi::WorldResult::Okay)
    {
        return result;
    }

    spawnLocator = FindSpawnLocator(GetRootNode());

    if (PiHEADLESS)
    {
    }
    else
    {
        TheGameGUI = new GameGUI();
    }

    return Pi::WorldResult::Okay;
}


void GameWorld::Render()
{
    World::Render();

    if (TheGizmo)
    {
        TheGizmo->Draw();
    }
}


void GameWorld::Interact()
{
    World::Interact();
}


const LocatorMarker *GameWorld::FindSpawnLocator(const Zone *zone)
{
    ///  Iterate through all of the markers in the zone.

    const Marker *marker = zone->GetFirstMarker();
    while (marker)
    {
        Pi::MarkerType::S type = marker->GetMarkerType();
        if (type == Pi::MarkerType::Locator)
        {
            const LocatorMarker *locator = static_cast<const LocatorMarker *>(marker);
            if (locator->GetLocatorType() == kLocatorSpawn)
            {
                return (locator);
            }
        }

        /// Получить следующий маркер в списке.

        marker = marker->Next();
    }

    /// Посмотрите на все подзоны.

    const Zone *subzone = zone->GetFirstSubzone();
    while (subzone)
    {
        const LocatorMarker *locator = FindSpawnLocator(subzone);
        if (locator)
        {
            return (locator);
        }

        subzone = subzone->Next();
    }

    return (nullptr);
}
