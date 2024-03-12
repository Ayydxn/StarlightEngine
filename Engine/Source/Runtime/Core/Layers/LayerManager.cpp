#include "StarlightPCH.h"
#include "LayerManager.h"

void CLayerManager::PushLayer(ILayer* Layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, Layer);
    Layer->OnAttach();

    m_LayerInsertIndex++;
}

void CLayerManager::PushOverlay(ILayer* Overlay)
{
    m_Layers.emplace_back(Overlay);
    Overlay->OnAttach();
}

void CLayerManager::PopLayer(ILayer* Layer)
{
    if (const auto Iterator = std::ranges::find(m_Layers, Layer); Iterator != m_Layers.end())
    {
        m_Layers.erase(Iterator);
        
        m_LayerInsertIndex--;
    }

    Layer->OnDetach();
}

void CLayerManager::PopOverlay(ILayer* Overlay)
{
    if (const auto Iterator = std::ranges::find(m_Layers, Overlay); Iterator != m_Layers.end())
        m_Layers.erase(Iterator);

    Overlay->OnDetach();
}
