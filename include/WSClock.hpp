#include "Disc.hpp"
#include "Ram.hpp"
#include "PageSubstitutionAlgorithm.hpp"
#include "RandomNumberGenerator.hpp"

class WSClock : public PageSubstitutionAlgorithm  {
    public:
        WSClock(Disc disc, Ram ram);

        void execute();
    private:
        int lastAccessTime[RLINES]; // To keep last access time of each page in ram.

        int agingInterval;

        int currentPage;  // Current page being referenced. Defaults to 0.

        int cvt; // cvt = current virtual time.

        void updateCvt();

        int findPageInRam();
};
