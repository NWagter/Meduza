#include "MePCH.h"
#include "Platform/General/ContextBase.h"

#include "Platform/General/Window.h"

Me::Renderer::ContextBase::ContextBase(Me::Window& a_window)
{
    a_window.m_context = this;
}

Me::Renderer::ContextBase::~ContextBase()
{
    
}