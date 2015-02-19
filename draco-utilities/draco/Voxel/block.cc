

#include "block.h"

namespace Vox {

    ostream &operator<<(ostream& out, byte value) {
	    return out << (unsigned int) value;
    }

}