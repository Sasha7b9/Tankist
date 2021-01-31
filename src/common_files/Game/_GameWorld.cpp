#include "stdafx.h"


GameWorld::GameWorld(pchar name) : World(name)
{
    // Этот конструктор вызывается, когда функция Game::ConstructWorld() призвал создать новый мировой класс.Мир на самом деле не был загружен с диска еще, когда мы доберемся сюда.
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

        // Получить следующий маркер в списке.

        marker = marker->Next();
    }

    // Посмотрите на все подзоны.

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
    // Функция Preprocess () вызывается после создания мира. Мы всегда должны сначала вызывать функцию базового класса Preprocess().Если он вернется ошибка, тогда мы просто возвращаем тот
    // же код результата.

    WorldResult::B result = World::Preprocess();
    if(result != WorldResult::Okay)
    {
        return result;
    }

    // Мир сейчас полностью загружен. Мы ищем локаторный узел, который представляет позицию появления игрока.Будет локатор тип kLocatorSpawn.

    spawnLocator = FindSpawnLocator(GetRootNode());

    return WorldResult::Okay;
}


void GameWorld::Render(void)
{
    // Эта функция вызывается один раз за кадр для визуализации мира. Подкласс может делать все, что ему нужно, до или после рендеринга, но в какой - то момент должен вызвать
    // World::Render().

    World::Render();
}
