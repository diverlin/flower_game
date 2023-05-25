#ifndef INDEX2D_H
#define INDEX2D_H

namespace core {

class Index2D {
public:
    Index2D(int i, int j): m_i(i), m_j(j) {}
    Index2D():Index2D(-1,-1) {}

    bool isValid() const { return (m_i != -1) && (m_j != -1); }
    bool isNull() const { return (m_i == 0) && (m_j == 0); }
    bool isMach(int i, int j) const { return (m_i == i) && (m_j == j); }

    void set(int i, int j) { m_i = i; m_j = j; }
    void reset() { m_i = -1; m_j = -1; }

    int i() const { return m_i; }
    int j() const { return m_j; }

    Index2D operator+(const Index2D& rhs) const {
        Index2D result(*this);
        result+=rhs;
        return result;
    }
    Index2D& operator+=(const Index2D& rhs) {
        m_i += rhs.i();
        m_j += rhs.j();
        return *this;
    }
    bool operator==(const Index2D& rhs) const {
        return (m_i == rhs.i()) && (m_j == rhs.j());
    }

private:
    int m_i = -1;
    int m_j = -1;
};

} // namespace core

#endif // INDEX2D_H
