#pragma once

#include <ranges>
#include <vector>

#include "ImGui/imgui.h"
#include "Editor_Resources.h"
#include "Editor_Utils.h"
#include "Cuscuz/World/Components/SpriteRenderer.h"
#include "Cuscuz/World/Actor.h"
#include "Cuscuz/Core/ClassRegistry.h"
#include "gtc/type_ptr.hpp"

namespace Cuscuz
{
    namespace Editor
    {
        inline static bool ItemGetter(void* data, int idx, const char** out_text)
        {
            const std::vector<std::string>* items = static_cast<std::vector<std::string>*>(data);
            if (idx < 0 || idx >= items->size()) return false; // Out of bounds check
            *out_text = (*items)[idx].c_str();
            return true;
        }

        inline static void ShowAddComponentBar(Actor* actor, int index)
        {
            const auto registry = ClassRegistry::GetRegistry();

            std::vector<std::string> items;
            items.reserve(registry.size());

            for (const auto& registryKey : registry | std::views::keys)
            {
                items.emplace_back(registryKey);
            }

            static int currentItem = 0; // Index of the currently selected item

            ImGui::TextColored(ImVec4(0.8f, .8f, .1f, 1.f), "Components List");
        
            const auto componentsListLabel = "##ComponentList" + std::to_string(index);

            if (ImGui::Combo(componentsListLabel.c_str(), &currentItem, ItemGetter, &items, static_cast<int>(items.size())))
            {
                LOG_INFO("Selected component: {0}", items[currentItem]);
            }

            const auto addLabel = "Add##" + std::to_string(index);

            if (ImGui::Button(addLabel.c_str()))
            {
                auto selectedComponent = ClassRegistry::GetClassType(items[currentItem]);

                if (!selectedComponent)
                    return;

                const auto newComponent = Cuscuz::Instantiate<Component>(selectedComponent->Name);
                actor->AddComponent(newComponent);
            }
        }
    
        inline static void DrawTransformComponent(Actor* actor)
        {
             auto& transformComponent = actor->GetTransform();

             glm::vec3 pos = transformComponent.GetPosition();
             DrawVec3Control("Position", pos);
             transformComponent.SetPosition(pos);

            glm::vec3 rot = {0.0f, 0.0f, transformComponent.GetRotation()};
            DrawVec3Control("Rotation", rot);
            transformComponent.SetRotation(rot.z);

            const auto actorScale = transformComponent.GetScale();
            glm::vec3 scale = {actorScale.x, actorScale.y, 1.0f };
            DrawVec3Control("Scale", scale);
            transformComponent.SetScale(scale);
        }

        template<typename T, typename UIFunction>
        inline static void DrawComponent(const std::string& name, Actor* actor, UIFunction function)
        {
            if(actor->HasComponent<T>())
            {
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap |
                                           ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding;
                T* component = actor->GetComponent<T>();

                ImGui::Separator();
                if(ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name.c_str()))
                {
                    function(component);
                    ImGui::TreePop();
                }
            }
        }
        
        inline static void ShowActorComponents(Actor* actor)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap |
                                       ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding;
            
            if(ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), flags, "Transform"))
            {
                DrawTransformComponent(actor);
                ImGui::TreePop();
            }            

            DrawComponent<SpriteRenderer>("Sprite Renderer", actor,
                [](auto& component)
                {
                    ImGui::Text("Color");
                    ImGui::SameLine();
                    static glm::vec4 spriteColor = component->GetColor();
                    ImGui::ColorEdit4("##SpriteColor", glm::value_ptr(spriteColor));

                    if(spriteColor != component->GetColor())
                         component->SetColor(spriteColor);

                    ImGui::Dummy({0.0f, 1.f});
                    
                    ImGui::Text("Sprite");
                    ImGui::SameLine();

                    const ImVec2 initialPoint = ImGui::GetCursorScreenPos();
                    constexpr ImVec4 color(.5f,.8f,1.f,1.f);
    
                    ImDrawList* draw_list = ImGui::GetWindowDrawList();
                    if(auto& sprite = component->GetSprite())
                    {
                        if (const auto texture = sprite->GetTexture())
                        {
                            const auto width = sprite->GetWidthF();
                            const auto height = sprite->GetHeightF();
                            constexpr float offset = 1.f;

                            draw_list->AddRect(ImVec2(initialPoint.x - offset, initialPoint.y - offset),
                                               ImVec2(initialPoint.x + width + offset, initialPoint.y + height + offset),
                                               ImColor(color));

                            ImGui::Image(texture->GetRendererID(), ImVec2{sprite->GetWidthF(),sprite->GetHeightF()}, ImVec2{0,1}, ImVec2{1,0});

                            ImGui::TextColored(ImVec4(0.6f, .6f, .6f, .8f), "Width:%.1f | Height:%.1f", width, height);
                        }
                    }
                    else
                    {
                        constexpr float squareSize = 64.f;
                        const float x = initialPoint.x + 4.0f;
                        const float y = initialPoint.y + 4.0f;

                        draw_list->AddRect(ImVec2(x, y), ImVec2(x + squareSize, y + squareSize), ImColor(color));

                        ImGui::Dummy(ImVec2(0.0f, squareSize));
                    }
                });
        }
        
    }
}
