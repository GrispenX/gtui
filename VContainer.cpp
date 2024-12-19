#include "VContainer.h"

void VContainer::ResolveGeometry()
{
    unsigned int child_size_x = GetSize().first;
    unsigned int child_size_y = GetSize().second / m_children.size();
    unsigned int child_pos_x = GetPos().first;
    unsigned int child_pos_y = GetPos().second;

    for(auto child : m_children)
    {
        child->Resize(child_size_x, child_size_y);
        child->SetPos(child_pos_x, child_pos_y);
        child_pos_y += child_size_y;
    }
}

void VContainer::AddChild(std::shared_ptr<BaseWidget> child)
{
    m_children.push_back(child);
}

void VContainer::Render()
{
    ResolveGeometry();
    for(auto child : m_children)
    {
        child->Render();
    }
}

void VContainer::HandleEvent(std::variant<MouseMoveEvent, MouseButtonEvent, KeyboardEvent> event)
{
    for(auto child : m_children)
    {
        child->HandleEvent(event);
    }
}
