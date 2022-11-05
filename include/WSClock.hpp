#include "Disc.hpp"
#include "Ram.hpp"
#include "PageSubstitutionAlgorithm.hpp"

class WSClock : PageSubstitutionAlgorithm {
    public:
        WSClock(Disc disc, Ram ram, int t);
    private:
        int lastAccessTime[RLINES]; // To keep last access time of each page in ram.

        int t;  // Aging interval.

        int currentPos;  // Current page being referenced. Defaults to 0.

        long cvt; // cvt = current virtual time.

        void substitutePageFromDisc();

        void updateData();
};
