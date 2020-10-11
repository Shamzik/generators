#include <functional>
#include <optional>

#define YIELD(x) _codePointer = __LINE__; return x; case __LINE__:;
#define GENERATE _Result generate() override {switch (_codePointer) { default:;
#define TERMINATE return std::nullopt;}}

template<typename T>
class Generator
{
protected:
    typedef std::optional<T> _Result;
    int _codePointer = -1;
private:
    class TerminateState {};
    class StateIterator
    {
        std::function<_Result()> func;
        _Result value;

    public:
        StateIterator(std::function<_Result()> f)
            : func(f)
            , value(func()) {}
        StateIterator& operator++() {
            value = func();
            return *this;
        }
        T operator*() {
            return *value;
        }
        bool operator!=(const TerminateState&) const
        {
            return value.has_value();
        }
    };

    virtual _Result generate() = 0;
public:
    StateIterator begin()
    {
        return StateIterator(std::bind(&Generator<T>::generate, this));
    }
    TerminateState end()
    {
        return {};
    }
};
