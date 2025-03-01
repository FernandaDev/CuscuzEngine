#pragma once

namespace Cuscuz
{
    class Layer;

    class LayerStack
    {
        std::vector<std::shared_ptr<Layer>> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        void PushLayer(std::shared_ptr<Layer> layer);
        void PushOverlay(std::shared_ptr<Layer> overlay);
        void PopLayer(std::shared_ptr<Layer> layer);
        void PopOverlay(std::shared_ptr<Layer> overlay);

        std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
        std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }
    };
}