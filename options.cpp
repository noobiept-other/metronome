#include "options.h"


Options::Options()

    : isOpened (false)

{
set_title("Options");
}



void Options::open()
{
isOpened = true;

show();
}
