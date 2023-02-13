#pragma once
#include<vector>
#include"Renderable.hpp"


class RenderManager
{
public:
    static RenderManager& instance()
    {
        static RenderManager* instance = new RenderManager();
        return *instance;
    }

    void RenderAll()
    {
        for (Renderable* r : m_renderList) {
            r->Render();
        }
    }

    void AddToRenderList(Renderable* renderable)
    {
        m_renderList.push_back(renderable);
    }


private:
    RenderManager() {}
    std::vector<Renderable*> m_renderList;
};