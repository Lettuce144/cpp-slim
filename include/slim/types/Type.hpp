#pragma once
#include "Object.hpp"
#include "Symbol.hpp"
#include "../Error.hpp"
#include "Function.hpp"
namespace slim
{
    /**Class/Module type object helper.*/
    class Type : public Object
    {
    public:
        virtual std::string inspect()const override
        {
            return type_name();
        }

        virtual ObjectPtr get_constant(SymPtr name)override
        {
            ObjectPtr key = std::static_pointer_cast<Object>(name);
            auto it = constants.find(key);
            if (it != constants.end()) return it->second;
            else throw NoConstantError(this, name);
        }

    protected:
        ObjectMap constants;
    };

    /**Provides a single Class instance with a "new" method to create instances of type T.
     *
     * The "new" method uses T::new_instance as an implementation, and so that static function
     * must exist, and follow the slim::Method rules regarding parameters.
     */
    template<class T> class SimpleClass : public Type
    {
    public:
        static const std::string &name() { return T::name(); }
        virtual const std::string& type_name()const override { return T::name(); }
        virtual const slim::MethodTable &method_table()const
        {
            static const slim::MethodTable table(slim::Object::method_table(),
            {
                { &T::new_instance, "new" }
            });
            return table;
        }
    private:
    };
}
