#ifndef SEKAS_INDEX_REGISTER_H
#define SEKAS_INDEX_REGISTER_H

#include <cstdint>
#include <memory>

class index_register {
public:
    enum class type : uint8_t {
        DATA,
        ADDRESS
    };

    enum class size : uint8_t {
        WORD,
        LONG_WORD
    };

    enum class scale : uint8_t {
        ONE,
        TWO,
        FOUR,
        EIGHT
    };

    typedef std::unique_ptr<index_register> ptr;

    explicit index_register(const uint8_t register_number, type type, size size, scale scale);
    virtual ~index_register();

    uint8_t get_register_number() const;

    type get_type() const;
    size get_size() const;
    scale get_scale() const;

    uint8_t encode() const;

private:
    const uint8_t register_number;
    const type index_type;
    const size index_size;
    const scale index_scale;
};

#endif
