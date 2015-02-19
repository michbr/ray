
#ifndef DRACO_VOX_ATOM_H
#define DRACO_VOX_ATOM_H


#include "block.h"

#include <iostream>


namespace Vox {

	class Block;

	class Atom: Block {
	public:
		// members
		byte opacity;
		unsigned short material;

		// constructors
		Atom(byte opacity, unsigned short material);
		Atom(const Atom& other);

		// methods
		bool compact() const;
		bool empty() const;
		byte average() const;

	private:

	};

}


#endif // DRACO_VOX_ATOM_H