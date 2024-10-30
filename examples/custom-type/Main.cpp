#include <slim/Template.hpp>
#include "Vector2.hpp"

#include <fstream>
#include <iostream>
#include <memory>

int main()
{
    try
    {
        // Check if the template file exists
        std::ifstream infile("view.html.slim");
        if (!infile.good()) {
            throw std::runtime_error("Template file 'view.html.slim' not found.");
        }

        auto tpl = slim::parse_template_file("view.html.slim");

        auto model = slim::create_view_model();
        model->add_constant("Vector2", slim::create_object<slim::SimpleClass<Vector2>>());
        model->set_attr("pos", slim::create_object<Vector2>(50, 30));
        model->set_attr("move", slim::create_object<Vector2>(5, 5));

        auto html = tpl.render(model);

        std::fstream fs("output.html", std::ios::out | std::ios::binary);
        if (!fs.is_open()) {
            throw std::runtime_error("Failed to open 'output.html' for writing.");
        }
        fs.write(html.data(), html.size());
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "Memory allocation failed: " << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return 0;
}