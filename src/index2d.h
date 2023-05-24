#ifndef INDEX2D_H
#define INDEX2D_H

class Index2D {
public:
    Index2D(int i, int j): m_i(i), m_j(j) {}
    Index2D():Index2D(0,0) {}

    bool isMach(int i, int j) { return (m_i == i) && (m_j == j); }

    void set(int i, int j) { m_i = i; m_j = j; }
    int i() const { return m_i; }
    int j() const { return m_j; }

    Index2D& operator+=(const Index2D& rhs) {
        m_i += rhs.i();
        m_j += rhs.j();
        return *this;
    }

private:
    int m_i = 0;
    int m_j = 0;
};

#endif // INDEX2D_H
