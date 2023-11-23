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
int _width = 900;
int _height = 800;

// main function
int main()
{
    // realtime title and background color
    RenderWindow window(VideoMode(_width, _height), "");
    window.setVerticalSyncEnabled(true);

    // setting up window icon
    // loading image
    sf::Image icon;
    if (!icon.loadFromFile("assets/logo.png"))
    {
        cout << "unable to load image";
    }

    //imgui image example with sfml 
    sf::Texture texture;
    if (!texture.loadFromFile("assets/logo.png"))
    {
        cout << "unable to load image";
    }
    Sprite sprite(texture);
    ImTextureID textureID = (void*)(intptr_t)texture.getNativeHandle();



    // icon setup
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Color bgColor;
    float color[3] = {0.f, 0.f, 0.f};

    // Let's use char array as buffer
    char windowTitle[255] = "ImGUI & SFML ";
    window.setTitle(windowTitle);

    ImGui::SFML::Init(window);

    // changing default font
    sf::Font customFont;
    if (!customFont.loadFromFile("assets/Playfair.ttf"))
    {
        std::cout << "unable to load font" << std::endl;
    }
    Text text;
    text.setFont(customFont);

    text.setPosition(200.f, 200.f);

    char word[255] = "";

    Clock deltaClock;

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
        // custom style
        ImGuiStyle &style = ImGui::GetStyle();
        style.WindowRounding = 9.3f;
        style.FrameRounding = 2.3f;
        style.ScrollbarRounding = 0;

        // custom style
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.4f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.7f, 1.0f));

        bool show;

        // imgui window manipulation
        ImGui::Begin("Window Setting");

        // background color edit
        if (ImGui::ColorEdit3("Text Color", color))
        {
            // this code gets called if color value changes, so
            //  the backgound color is upgrade automatically
            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }
        text.setColor(bgColor);
        // Window title text edit
        ImGui::InputText("Window Title", windowTitle, 255);

        if (ImGui::Button("Update window title"))
        {
            // this code gets if user clicks on the button
            // yes we could have written if(ImGui::InputText(....))
            // but i do this to show how button works
            window.setTitle(windowTitle);
        }
        int fontSizes;
        ImGui::InputText("Enter text", word, 255);
        ImGui::InputInt("font size", &fontSizes);

        if (ImGui::Button("change text"))
        {
            text.setString(word);
            text.setCharacterSize(fontSizes);
        }

        if (ImGui::Button("show window"))
        {
            show = true;
        }
        if (ImGui::Button("Hide window"))
        {
            show = false;
        }

        ImGui::End();

        ImGui::Begin("Custom Button Resizing and Positioning");

        // Define your custom button size and position
        ImVec2 buttonSize(100, 40);    // Customize the size
        ImVec2 buttonPosition(50, 50); // Customize the position

        // Use ImGui::SetCursorPos to set the position of the button
        ImGui::SetCursorPos(buttonPosition);

        // Create a button with the specified size
        if (ImGui::Button("Custom Button", buttonSize))
        {
            // Button click action
        }

        // End the window
        ImGui::End();

        if (show == true)
        {
            ImGui::Begin("Button Style bro ");
            if (ImGui::Button("custom button"))
            {
                cout << "i am pressed baby" << endl;
            }
            ImGui::Text("hello");
            // checkbox
            static bool check = true;
            ImGui::Checkbox("checkBox", &check);
            // radio
            static int e = 0;
            ImGui::RadioButton("radio a", &e, 0);
            ImGui::SameLine();
            ImGui::RadioButton("radio b", &e, 1);
            ImGui::SameLine();
            ImGui::RadioButton("radio c ", &e, 2);
            // label
            ImGui::LabelText("label", "value");

            // textbox
            static char text[128] = "";
            if (ImGui::InputTextWithHint("Name", "Enter your name", text, IM_ARRAYSIZE(text)))
                cout << text << endl;

            // items
            const char *items[] = {"aaa", "bbb", "cccc", "ddd"};
            static int item_current = 0;
            ImGui::Combo("Combo", &item_current, items, IM_ARRAYSIZE(items));
            ImGui::SameLine();

            // integer input
            static int i0 = 369;
            ImGui::InputInt("input int", &i0);

            // Drag input int
            static int i1 = 50, i2 = 42;
            ImGui::DragInt("Drag int 0.. 100", &i2, 1, 0, 100, "%d%%", ImGuiSliderFlags_AlwaysClamp);

            // Drag float
            static float f1 = 1.00f, f2 = 0.0067f;
            ImGui::DragFloat("drag float", &f1, 0.005f);
            ImGui::DragFloat("drag small float", &f2, 0.0001f, 0.0f, 0.0f, "%.06f ns");

            // Histogram
            static float arr2[] = {0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f};
            ImGui::PlotHistogram("Histogram", arr2, IM_ARRAYSIZE(arr2), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));

            // progress Bar
            static float progress = 0.0f, progress_dir = 1.0f;
            bool animate = false;
            if(ImGui::Checkbox("animate", &animate))
            {
            animate = true;
            }
            
            if (animate)
            {
                progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
                if (progress >= +1.1f)
                {
                    progress = +1.1f;
                    progress_dir *= -1.0f;
                }
                if (progress <= -0.1f)
                {
                    progress = -0.1f;
                    progress_dir *= -1.0f;
                }
            }
            ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::Text("progress bar");

            //Display Image
            ImGui::Image(textureID, ImVec2(texture.getSize().x, texture.getSize().y));

            // main menu
            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {

                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Edit"))
                {
                    if (ImGui::MenuItem("Undo", "CTRL+Z"))
                    {
                    }
                    if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
                    {
                    } // Disabled item
                    ImGui::Separator();
                    if (ImGui::MenuItem("Cut", "CTRL+X"))
                    {
                    }
                    if (ImGui::MenuItem("Copy", "CTRL+C"))
                    {
                    }
                    if (ImGui::MenuItem("Paste", "CTRL+V"))
                    {
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            ImGui::End();
        }
        ImGui::PopStyleColor(3);

        //transparent window example
         // Set ImGui window flags to enable a translucent background
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize;
        ImGui::SetNextWindowBgAlpha(0.7f); // Adjust the alpha value as needed (0.7 is 70% opacity)

        ImGui::Begin("Translucent Window", nullptr, windowFlags);

        // Inside the window, you can add your ImGui content as usual
        ImGui::Text("This is a translucent ImGui window!");
        if (ImGui::Button("Close")) {
            window.close();
        }

        ImGui::End();

        // Clearing the window
        window.clear();
        ImGui::SFML::Render(window);
        window.draw(text);

        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}