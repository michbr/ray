
/*
 * Cullen Eason
 * semimono
 * Assignment 5
 * CS 410
 * Ross Beveridge
 */

#include "world.h"
#include <iostream>

using namespace std;


/////////////
// General //
/////////////

void showHelpAndClose(char *progamName) {
	cout << endl << "To generate a ray traced image, enter: " << endl
		<< "\t" << progamName << " <Object File> <Command File>" << endl << endl;
	exit(-1);
}


//////////////////////
// Program Entrance //
//////////////////////

int main(int argc, char **argv) {
	
    // parse arguments
	if (argc != 3) {
        cerr << "Wrong number of arguments." << endl;
        showHelpAndClose(argv[0]);
    }
	
	
	World w;
	
	// add the .obj file to the scene
	w.addObjects(argv[1]);
	
	// render the scene with the given command file
	w.render(argv[2]);
	
	return 0;
}
