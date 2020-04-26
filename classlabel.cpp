#include "classlabel.h"

/**
 * ClassLabel constructor
 *
 * @param QString - The name of the Class Label
 */

ClassLabel::ClassLabel(QString s)
{
    name = s;
}

/**
 * Get the name of the Class Label
 *
 * @return QString - The name of the Class Label
 */

QString ClassLabel::getName() {
    return name;
}
