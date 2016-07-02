#include "expression/ArithmeticOp.hpp"
#include "expression/Scope.hpp"
#include "types/Object.hpp"
#include "Operators.hpp"
namespace slim
{
    namespace expr
    {
        ObjectPtr Negative::eval(Scope & scope) const
        {
            return arg->eval(scope)->negate();
        }
        ObjectPtr Mul::eval(Scope & scope) const
        {
            auto lhs_v = lhs->eval(scope);
            auto rhs_v = rhs->eval(scope);
            return lhs_v->mul(rhs_v.get());
        }
        ObjectPtr Div::eval(Scope & scope) const
        {
            auto lhs_v = lhs->eval(scope);
            auto rhs_v = rhs->eval(scope);
            return lhs_v->div(rhs_v.get());
        }
        ObjectPtr Mod::eval(Scope & scope) const
        {
            auto lhs_v = lhs->eval(scope);
            auto rhs_v = rhs->eval(scope);
            return lhs_v->mod(rhs_v.get());
        }
        ObjectPtr Add::eval(Scope & scope) const
        {
            auto lhs_v = lhs->eval(scope);
            auto rhs_v = rhs->eval(scope);
            return lhs_v->add(rhs_v.get());
        }
        ObjectPtr Sub::eval(Scope & scope) const
        {
            auto lhs_v = lhs->eval(scope);
            auto rhs_v = rhs->eval(scope);
            return lhs_v->sub(rhs_v.get());
        }
    }
}
