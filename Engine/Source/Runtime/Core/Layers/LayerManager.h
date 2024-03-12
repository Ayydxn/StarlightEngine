#pragma once

#include "Layers/Layer.h"

class CLayerManager
{
public:
    CLayerManager() = default;
    ~CLayerManager() = default;

    void PushLayer(ILayer* Layer);
    void PushOverlay(ILayer* Overlay);
    void PopLayer(ILayer* Layer);
    void PopOverlay(ILayer* Overlay);

    std::vector<ILayer*> GetLayers() const { return m_Layers; }
    size_t GetLayerCount() const { return m_Layers.size(); }
private:
    std::vector<ILayer*> m_Layers;

    uint32 m_LayerInsertIndex = 0;
};
