#pragma once
#include <string>
namespace slim
{
    namespace tpl
    {
        /**A token in the template source, as read by Lexer. */
        struct Token
        {
            enum Type
            {
                /**End of input. */
                END,
                /**End of line (if not END, or by defintion consumed by previous symbol). */
                EOL,
                /**Indentation at the start of a line.*/
                INDENT,
                /**An element, atttribute, id or class name.
                 * Allows numbers, letters, underscores and hyphens.
                 */
                NAME
            };

            Token() {}
            Token(Type type) : type(type), str() {}
            Token(Type type, const std::string &str) : type(type), str(str) {}

            Type type;
            std::string str;
        };
    }
}