#ifndef ANY_JSON_H
#define ANY_JSON_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

struct base { virtual ~base() = default; };

template<typename _T>
struct data: base {
    data(_T t) : v(t) { }
    _T v;
};

struct json {
    typedef std::vector<json>                       array;
    typedef std::unordered_map<std::string, json>   object;

    json() = default;

    struct null{ };
    struct infinity{ bool neg; infinity(bool negative = false): neg(negative){} };
    struct boolean{ bool yes; boolean(bool y=false): yes(y){} };
    struct hex {
        hex() = default;
        hex(long t, std::string v) : value(t), raw_value(v) {}
        long value;
        std::string raw_value;
    };

    template<typename _T>
    json(_T t) { ptr = std::make_shared<data<_T>>(t); name = typeid(t).name(); }

    template<typename _T>
    bool is() { if (typeid(_T).name() == name) { return true; } else { return false; } }

    bool is_array() { return this->is<array>(); }
    bool is_object() { return this->is<object>(); }
    bool is_int() { return this->is<int>(); }
    bool is_long() { return this->is<long>(); }
    bool is_double() { return this->is<double>(); }
    bool is_float() { return this->is<float>(); }
    bool is_string() { return this->is<const char *>() || this->is<std::string>(); }
    bool is_null() { return this->is<null>(); }
    bool is_bool() { return this->is<boolean>(); }
    bool is_infinity() { return this->is<infinity>(); }
    bool is_hex() { return this->is<hex>(); }

    int get_int() { return this->get<int>(); }
    long get_long() { return this->get<long>(); }
    double get_double() { return this->get<double>(); }
    float get_float() { return this->get<float>(); }
    infinity get_infinity() { return this->get<infinity>(); }
    boolean get_bool() { return this->get<boolean>(); }
    hex get_hex() { return this->get<hex>(); }

    std::string get_string();
    array get_array() { return this->get<array>();    }
    object get_object() { return this->get<object>(); }

    std::string toString(bool hex = false);

    template<class T>
    T get() { return this->template cast<T>(); }

    template<typename _T>
    _T cast() { return dynamic_cast<data<_T>*>(ptr.get())->v; }

    std::shared_ptr<base> ptr{nullptr};
    const char *name = nullptr;
};


#endif