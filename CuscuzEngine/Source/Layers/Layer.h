#pragma once

class CC_Event;

class Layer
{
protected:
    std::string m_DebugName;
    //bool m_Enabled; 
    
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach(){}
    virtual void OnDetach(){}
    virtual void OnUpdate(){}
    virtual void OnImGuiRender(){}
    virtual void OnEvent(CC_Event& event){}

    inline const std::string& GetName() const { return m_DebugName; }
};
