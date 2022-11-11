#ifndef AEL_ARRAY_H
#define AEL_ARRAY_H
#include <cstddef>

namespace ael {

/*
 * @brief This class is meant as a replacement for the std::array, since that is made constexpr and
 * I need to be able to interface with C code.
 */
template <typename T, size_t SIZE>
class array {
    T m_array[SIZE];
    size_t m_len = SIZE;

   public:
    array() = default;
    ~array() = default;
    size_t size() const { return this->m_len; }
    T* raw_ptr() { return this->m_array; }
    /*
     * TODO: - Add bounds checking
     *       - wrap in something like std::optional
     */
    T operator[](const size_t& i) { return this->m_array[i]; }
};

}  // namespace ael

#endif  // !AEL_ARRAY_H
