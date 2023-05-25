#ifndef SIZE_H
#define SIZE_H

class Size {
public:
    Size(int width, int height): m_width(width), m_height(height) {}
    ~Size()=default;

    bool operator<(const Size& rhs) const {
        return width()*height() < rhs.width()*rhs.height();
    }
    bool operator!=(const Size& rhs) const {
        return (width() != rhs.width()) || (height() != rhs.height());
    }

    int width() const { return m_width; }
    int height() const { return m_height; }

private:
    int m_width = 0;
    int m_height = 0;
};

#endif // SIZE_H
