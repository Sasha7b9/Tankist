#include "stdafx.h"


GameWorld::GameWorld(pchar name) : World(name)
{
    // ���� ����������� ����������, ����� ������� Game::ConstructWorld() ������� ������� ����� ������� �����.��� �� ����� ���� �� ��� �������� � ����� ���, ����� �� ��������� ����.
}


GameWorld::~GameWorld()
{
}


const LocatorMarker *GameWorld::FindSpawnLocator(const Zone *zone) //-V2506
{
    //  Iterate through all of the markers in the zone.

    const Marker *marker = zone->GetFirstMarker();
    while(marker)
    {
        MarkerType::S type = marker->GetMarkerType();
        if(type == MarkerType::Locator)
        {
            const LocatorMarker *locator = static_cast<const LocatorMarker *>(marker);
            if(locator->GetLocatorType() == kLocatorSpawn)
            {
                return (locator);
            }
        }

        // �������� ��������� ������ � ������.

        marker = marker->Next();
    }

    // ���������� �� ��� �������.

    const Zone *subzone = zone->GetFirstSubzone();
    while(subzone)
    {
        const LocatorMarker *locator = FindSpawnLocator(subzone);
        if(locator)
        {
            return (locator);
        }

        subzone = subzone->Next();
    }

    return (nullptr);
}


WorldResult::B GameWorld::Preprocess(void) //-V2506
{
    // ������� Preprocess () ���������� ����� �������� ����. �� ������ ������ ������� �������� ������� �������� ������ Preprocess().���� �� �������� ������, ����� �� ������ ���������� ���
    // �� ��� ����������.

    WorldResult::B result = World::Preprocess();
    if(result != WorldResult::Okay)
    {
        return result;
    }

    // ��� ������ ��������� ��������. �� ���� ���������� ����, ������� ������������ ������� ��������� ������.����� ������� ��� kLocatorSpawn.

    spawnLocator = FindSpawnLocator(GetRootNode());

    return WorldResult::Okay;
}


void GameWorld::Render(void)
{
    // ��� ������� ���������� ���� ��� �� ���� ��� ������������ ����. �������� ����� ������ ���, ��� ��� �����, �� ��� ����� ����������, �� � ����� - �� ������ ������ �������
    // World::Render().

    World::Render();
}
