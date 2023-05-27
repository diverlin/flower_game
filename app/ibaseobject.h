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

    bool isAlive() const { return m_isAlive; }
    long long id() const { return m_id; }

    void setDead() { m_isAlive = false; }

private:
    long long m_id = -1;
    bool m_isAlive = true;

    static long long s_counter;
};

} // namespace core

#endif // IBASEOBJECT_H
