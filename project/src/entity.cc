/**
* @file entity.cc
*
* @copyright 2021 3081W, All rights reserved.
*/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "entity.h"

const double& Entity::GetID() {
    // static allows us to keep the name entity for the duration
    // of the entire program.  This allows us to pass a reference back.
    // When a variable is declared static, there is only one variable per class.
    static double id(0);
    return id;
}