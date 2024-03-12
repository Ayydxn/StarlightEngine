#pragma once

#include "Events/Event.h"

class ILayer
{
public:
    ILayer(const std::string& Name = "Layer");
    virtual ~ILayer() = default;
    
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnPreRender() {}
    virtual void OnRender() {}
    virtual void OnPostRender() {}
    virtual void OnTick() {}
    virtual void OnEvent(IEvent& Event) {}

    const std::string& GetName() const { return LayerName; }
protected:
    std::string LayerName;
};
