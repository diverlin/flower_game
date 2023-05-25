#ifndef FIXEDQUEUE_H
#define FIXEDQUEUE_H

#include <deque>

template<typename T>
class FixedQueue {
private:
    std::deque<T> m_elements;
    std::size_t m_maxLength;

public:
    FixedQueue(std::size_t maxLength): m_maxLength(maxLength) {}

    void push(const T& value) {
        if (m_elements.size() >= m_maxLength) {
            pop();
        }
        m_elements.push_front(value);
    }

    void setMaxLength(std::size_t maxLength) {
        m_maxLength = maxLength;
        while (m_elements.size() >= m_maxLength) {
            pop();
        }
    }

    void clear() {
        m_elements.clear();
    }

    std::size_t size() const {
        return m_elements.size();
    }

    const T& at(std::size_t n) const {
        return m_elements.at(n);
    }

    // Iterator support
    typename std::deque<T>::iterator begin() {
        return m_elements.begin();
    }

    typename std::deque<T>::const_iterator begin() const {
        return m_elements.begin();
    }

    typename std::deque<T>::iterator end() {
        return m_elements.end();
    }

    typename std::deque<T>::const_iterator end() const {
        return m_elements.end();
    }

private:
    void pop() {
        if (!m_elements.empty()) {
            m_elements.pop_back();
        }
    }
};

#endif // FIXEDQUEUE_H
