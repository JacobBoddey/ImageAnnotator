#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <image.h>

class Annotation
{

private:

    Image* image;

public:

    Annotation();
    Image getImage();

};

#endif // ANNOTATION_H
