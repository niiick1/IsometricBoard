#ifndef PTMREADER_H
#define PTMREADER_H

#include <string>
#include "Image.h"

using std::string;

class PTMReader
{
    public:
        PTMReader();

        Image* readFile(string);

        virtual ~PTMReader();
    protected:
    private:
};

#endif // PTMREADER_H
