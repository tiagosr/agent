//
//  main.c
//  agent
//
//  Created by Tiago Rezende on 6/20/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#include <stdio.h>
#include "ent.h"

void ent_setup(void) {
    post("agent v0.0");
    setup_symbols();
    ent_class_setup();
    does_class_setup();
}