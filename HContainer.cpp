#include "HContainer.h"

HContainer::HContainer()
{
    
}

void HContainer::ResolveGeometry()
{
    unsigned int child_size_x = GetSize().first / m_children.size();
    unsigned int child_size_y = GetSize().second;
    unsigned int child_pos_x = GetPos().first;
    unsigned int child_pos_y = GetPos().second;

    for(auto child : m_children)
    {
        child->Resize(child_size_x, child_size_y);
        child->SetPos(child_pos_x, child_pos_y);
        child_pos_x += child_size_x;
    }
}

void HContainer::AddChild(BaseWidget* child)
{
    m_children.push_back(child);
}

void HContainer::Render()
{
    ResolveGeometry();
    for(auto child : m_children)
    {
        child->Render();
    }
}

void HContainer::HandleEvent(std::variant<MouseMoveEvent, MouseButtonEvent, KeyboardEvent> event)
{
    if(std::holds_alternative<MouseButtonEvent>(event))
    {
        auto e = std::get<MouseButtonEvent>(event);
        auto pos = GetPos();
        auto size = GetSize();
        SetActive((e.pos.first >= pos.first && e.pos.first <= pos.first + size.first - 1 &&
                   e.pos.second >= pos.second && e.pos.second <= pos.second + size.second - 1));
        for(auto child : m_children)
        {
            pos = child->GetPos();
            size = child->GetSize();
            if((e.pos.first >= pos.first && e.pos.first <= pos.first + size.first - 1 &&
               e.pos.second >= pos.second && e.pos.second <= pos.second + size.second - 1) || child->IsActive())
            {
                child->HandleEvent(e);
            }
        }
    }
    else if(std::holds_alternative<KeyboardEvent>(event))
    {
        auto e = std::get<KeyboardEvent>(event);
        for(auto child : m_children)
        {
            if(child->IsActive())
            {
                child->HandleEvent(e);
            }
        }
    }
}