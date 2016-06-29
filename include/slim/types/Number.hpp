#pragma once
#include "Object.hpp"
namespace slim
{
    class Number : public Object
    {
    public:
        static const std::string TYPE_NAME;
        explicit Number(double v) : v(v) {}

        virtual const std::string& type_name()const override { return TYPE_NAME; }
        virtual std::string to_string()const override;
        virtual bool is_true()const override { return v ? true : false; }
        virtual int cmp(const Object *rhs)const override
        {
            double v2 = ((const Number*)rhs)->v;
            if (v < v2) return -1;
            if (v > v2) return 1;
            else return 0;
        }
        double get_value()const { return v; }
    private:
        double v;
    };

    inline std::shared_ptr<Number> make_value(double v)
    {
        return create_object<Number>(v);
    }
}
