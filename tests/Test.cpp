#include <ege3d/window/Window.h>
#include <ege3d/window/WindowSettings.h>

void eventHandler(const EGE3d::SystemEvent& event)
{
    if(event.getType() == EGE3d::EventType::EClose)
    {
        event.getWindow().close();
    }
}

int main()
{
    EGE3d::Window window;
    window.setEventHandler(eventHandler);
    window.create(300, 300, "EGE3d Test", EGE3d::WindowSettings()
                  .setBackgroundColor({255, 0, 255})
                  .setForegroundColor({0, 255, 0}));

    while(window.isOpen())
    {
        window.dispatchAllEvents();
    }

    window.close();
    return 0;
}
