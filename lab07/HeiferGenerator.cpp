#include <typeinfo>
#include "Cow.h"
#include "HeiferGenerator.h"

std::vector<Cow*>& HeiferGenerator::getCows()
{
	if (cows.empty())
	{
		// Add the "regular" cows
		for (int index = 0; index < numCows; index++)
		{
            cows.push_back(new Cow(cowNames[index]));
            cows[index]->setImage(quoteLines + cowImages[index]);
		}

		// Add the dragons
		for (int index = 0; index < numDragons; index++)
			cows.push_back((*getNewDragon[index])(dragonNames[index], quoteLines + dragonImage));
	}

	return cows;
}

// If the object is a Dragon or IceDragon, return a cast pointer; otherwise, return nullptr.
Dragon* HeiferGenerator::getDragonPointer(Cow* cow)
{
    if (typeid(Dragon) == typeid(*cow) || typeid(IceDragon) == typeid(*cow))
        return (Dragon*) cow;
    return nullptr;
}