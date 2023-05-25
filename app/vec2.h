#ifndef VEC2_H
#define VEC2_H

class vec2 {
public:
    vec2(float x, float y): m_x(x), m_y(y) {}
    ~vec2()=default;

    int x() const { return m_x; }
    int y() const { return m_y; }

private:
    int m_x = 0;
    int m_y = 0;
};

#endif // VEC2_H
