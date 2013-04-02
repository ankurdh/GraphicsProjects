#include "DisplyaListHelper.h"

class SpaceBarHelper
    {

    private:
	Grid &g;
	DisplayListHelper *dlHelper;

    public:
	SpaceBarHelper(Grid &grid): g(grid)
	    {
	    }

	void setDLHelper(DisplayListHelper *d)
	    {
	    dlHelper = d;
	    }

	void triggerDLRefresh()
	    {
	    dlHelper->refreshDiscDL();
	    }

    };