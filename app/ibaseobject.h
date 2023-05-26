#ifndef IBASEOBJECT_H
#define IBASEOBJECT_H

namespace core {

class Image;

class IBaseObject
{
public:
    IBaseObject();
    virtual ~IBaseObject()=default;

    virtual void update(int frameDeltaTimeMs)=0;

    long long id() const { return m_id; }

private:
    long long m_id = -1;

    static long long s_counter;
};

} // namespace core

#endif // IBASEOBJECT_H
