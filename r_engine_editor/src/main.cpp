#include <iostream>
#include <memory>

#include <r_engine_core/Application.hpp>


class MyApp : public r_engine::Application {
    virtual void on_update() override {
        
    }

    int frame = 0;
};

int main() {
    std::unique_ptr myApp = std::make_unique<MyApp>();

    int returnCode = myApp->start(1024, 768, "Project");

    return returnCode;
}