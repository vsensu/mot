#ifndef MOT_IEXAMPLE_H
#define MOT_IEXAMPLE_H

#include <string>

struct IExample
{
    virtual std::string Title() = 0;
    virtual void Init() = 0;
    virtual void Render() = 0;
};

#endif //MOT_IEXAMPLE_H
