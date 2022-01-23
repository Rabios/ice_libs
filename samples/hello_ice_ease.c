/* Define the implementation of the library and include it */
#define ICE_EASE_IMPL 1
#include "ice_ease.h"

#include <stdio.h>

int main(void) {
    double linear1, linear4;

    /* Use linear easing, With 1 argument (easings.net) */
    linear1 = ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5.0);
    
    /* Use linear easing, But with 4 arguments (Robert Penner's version) */
    linear4 = ice_ease_linear(ICE_EASE_TYPE_PENNER, 1.0, 2.0, 3.0, 4.0);

    /* Print the results... */
    printf("Linear easing with one variable: %f\nLinear easing with four variables: %f\n",
           linear1, linear4);

    return 0;
}
