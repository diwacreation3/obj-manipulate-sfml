/*
Author: Diwakar phuyal
github: https://github.com/diwacreation3
feel free to use this template
*/

// Imgui header files
#include "imgui.h"
#include "imgui-SFML.h"

// SFML header files
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;



// window properties
int _width = 800;
int _height = 600;
string _title = "SFML and imgui ";

// main function
int main()
{
    RenderWindow window(VideoMode(_width, _height), _title);
    window.setFramerateLimit(30);
    ImGui::SFML::Init(window);

    Clock deltaClock;
    CircleShape shape;

    

    // Shape variable initial
    sf::Color shapeColor;
    float color[3] = {255.f, 155.f, 255.f};
    int shapePoint = 3;
    float shapeRadius = 30.f;
    float shapePosX = 10;
    float shapePosY = 10;

    // main loop
    while (window.isOpen())
    {
        Event event; // listen click events
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == Event::Closed) // Check if close button pressed or not
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        // Clearing the window
        window.clear();
        

        // imGui ui window
        ImGui::Begin("Object properties");

        // set object color
        if (ImGui::ColorEdit3("Shape Color", color))
        {
            shapeColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            shapeColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            shapeColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }
        // change object point count
        ImGui::SliderInt("Add vertices", &shapePoint, 3, 20);
        ImGui::SliderFloat("Change Radius", &shapeRadius, 30, 900);

        ImGui::SliderFloat("X Position", &shapePosX, 10, _width);  // according to width of screen
        ImGui::SliderFloat("Y Position", &shapePosY, 10, _height); // accoring to height of screen

        
        ImGui::End();

        // changes shape properties
        shape.setFillColor(shapeColor);
        shape.setPointCount(shapePoint);
        shape.setRadius(shapeRadius);
        shape.setPosition(shapePosX, shapePosY); // changes the shape position relative to window


        ImGui::SFML::Render(window);
        

        window.draw(shape);

        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

