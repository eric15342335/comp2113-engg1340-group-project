// stores the event texts and modifiers
#include "events.h"

Stock_event example {
    "The company has released a new product, received many positive reviews.",
    // and it will increase the standard deviation by 0.1 (more volatile stock price)
    +0.1,
    // decrease the skewness by 0.1 (more likely to realize at +ve side)
    -0.1,
    1,  // duration of 1 turn
    100, // this event has 10.0% chance of happening,
    1, // type of event
    0 // category
};

