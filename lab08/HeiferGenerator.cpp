#include <filesystem>
#include <typeinfo>

#include "Cow.h"
#include "HeiferGenerator.h"

std::vector<Cow*>& HeiferGenerator::getFileCows()
{
	if (fileCows.empty())
	{
		// Add file cows
		for (auto &entry : std::filesystem::directory_iterator(std::filesystem::path("cows")))
			if (entry.path().extension() == ".cow")
			    fileCows.push_back(new FileCow(entry.path().stem().string(), entry.path().string()));
	}
	
	return fileCows;
}

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