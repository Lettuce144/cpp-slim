#pragma once
#include "types/Object.hpp"
namespace slim
{
    bool eq(const Object *lhs, const Object *rhs);
    int cmp(const Object *lhs, const Object *rhs);

    ObjectPtr op_eq(const Object *lhs, const Object *rhs);
    ObjectPtr op_ne(const Object *lhs, const Object *rhs);
    ObjectPtr op_cmp(const Object *lhs, const Object *rhs);
    ObjectPtr op_lt(const Object *lhs, const Object *rhs);
    ObjectPtr op_le(const Object *lhs, const Object *rhs);
    ObjectPtr op_gt(const Object *lhs, const Object *rhs);
    ObjectPtr op_ge(const Object *lhs, const Object *rhs);

    ObjectPtr op_mul(const Object *lhs, const Object *rhs);
    ObjectPtr op_div(const Object *lhs, const Object *rhs);
    ObjectPtr op_mod(const Object *lhs, const Object *rhs);

    ObjectPtr op_add(const Object *lhs, const Object *rhs);
    ObjectPtr op_sub(const Object *lhs, const Object *rhs);

    ObjectPtr op_not(const Object *rhs);
    ObjectPtr op_negative(const Object *rhs);

    struct ObjLess
    {
        bool operator()(const Object *lhs, const Object *rhs)const
        {
            return cmp(lhs, rhs) < 0;
        }
        bool operator()(const ObjectPtr &lhs, const ObjectPtr &rhs)const
        {
            return cmp(lhs.get(), rhs.get()) < 0;
        }
    };
}
