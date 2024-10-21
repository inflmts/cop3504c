#pragma once

#include <string>
#include <vector>
#include "Cow.h"
#include "Dragon.h"
#include "IceDragon.h"

class HeiferGenerator
{
public:
	static std::vector<Cow*>& getCows();
    static Dragon* getDragonPointer(Cow* cow);

private:
    inline static std::vector<Cow*> cows;

	// Hard-coded values for some of the cows
	static const int numCows = 2;
	static const int numDragons = 2;
	inline static const std::string cowNames[] = { "heifer", "kitteh" };
	inline static const std::string dragonNames[] = { "dragon", "ice-dragon" };

	// Function pointers that return new Cow object pointers. (We'll learn this later!)
    inline static Cow* (*getNewDragon[2])(const std::string&, const std::string&) =
	{
		[](const std::string& name, const std::string& image) -> Cow* { return new Dragon(name, image); },
		[](const std::string& name, const std::string& image) -> Cow* { return new IceDragon(name, image); }
	};

    inline static const std::string quoteLines =	"       \\\n"
									        		"        \\\n"
									        		"         \\\n";

    inline static const std::string cowImages[] = {	"        ^__^\n"
								    				"        (oo)\\_______\n"
							    					"        (__)\\       )\\/\\\n"
								    				"            ||----w |\n"
									    			"            ||     ||\n",

										    		"       (\"`-'  '-/\") .___..--' ' \"`-._\n"
											    	"         ` *_ *  )    `-.   (      ) .`-.__. `)\n"
				    								    "         (_Y_.) ' ._   )   `._` ;  `` -. .-'\n"
					    							"      _.. `--'_..-_/   /--' _ .' ,4\n"
						    						"   ( i l ),-''  ( l i),'  ( ( ! .-'\n"
							    			   };

    inline static const std::string dragonImage =	"           |\\___/|       /\\  //|\\\\\n"
							        				"           /0  0  \\__   /  \\// | \\ \\\n"
									        		"          /     /  \\/_ /   //  |  \\  \\\n"
											        "          \\_^_\\'/   \\/_   //   |   \\   \\\n"
	        										"          //_^_/     \\/_ //    |    \\    \\\n"
			        								"       ( //) |        \\ //     |     \\     \\\n"
					        						"     ( / /) _|_ /   )   //     |      \\     _\\\n"
							        				"   ( // /) '/,_ _ _/  ( ; -.   |    _ _\\.-~       .-~~~^-.\n"
									        		" (( / / )) ,-{        _      `.|.-~-.          .~         `.\n"
											        "(( // / ))  '/\\      /                ~-. _.-~      .-~^-.  \\\n"
	        										"(( /// ))      `.   {            }                 /      \\  \\\n"
			        								" (( / ))     .----~-.\\        \\-'               .~         \\  `.   __\n"
					        						"            ///.----..>        \\            _ -~            `.  ^-`  \\\n"
							        				"              ///-._ _ _ _ _ _ _}^ - - - - ~                   `-----'\n";
};
