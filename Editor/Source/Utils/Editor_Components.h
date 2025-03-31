#pragma once

#include <ranges>
#include <vector>

#include "ImGui/imgui.h"
#include "Editor_Resources.h"
#include "Editor_Utils.h"
#include "Cuscuz/World/Components/SpriteRenderer.h"
#include "Cuscuz/World/Actor.h"
#include "Cuscuz/Core/ClassRegistry.h"
#include "Cuscuz/World/Components/CameraComponent.h"
#include "gtc/type_ptr.hpp"

namespace Cuscuz
{
    namespace Editor
    {
        template<typename T>
        inline static void ShowComponentMenuItem(Actor* actor)
        {
            if(ImGui::MenuItem(T::StaticClassName().data()))
            {
                if(actor->HasComponent<T>())
                {
                    LOG_WARN("{0} already has {1}!", actor->GetName(), T::StaticClassName());
                    ImGui::CloseCurrentPopup();
                    return;
                }

                actor->AddComponent<T>();
                ImGui::CloseCurrentPopup();
            }
        }

        inline static void ShowAddComponentButton(Actor* actor)
        {
            if(ImGui::Button("Add Component"))
                ImGui::OpenPopup("AddComponent");
            
            if(ImGui::BeginPopup("AddComponent"))
            {
                ShowComponentMenuItem<SpriteRenderer>(actor);
                ShowComponentMenuItem<CircleDetectionComponent>(actor);
                ShowComponentMenuItem<Simple2DMovementComponent>(actor);
                //ShowComponentMenuItem<CameraComponent>(actor);
                
                ImGui::EndPopup();
            }
        }
        
        inline static void DrawTransformComponent(Actor* actor)
        {
             auto& transformComponent = actor->GetTransform();

             glm::vec3 pos = transformComponent.GetPosition();
             DrawVec3Control("Position", pos);
             transformComponent.SetPosition(pos);

             glm::vec3 rot = transformComponent.GetRotation();
             DrawVec3Control("Rotation", rot);
             transformComponent.SetRotation(rot);

             glm::vec3 scale = transformComponent.GetScale();
             DrawVec3Control("Scale", scale);
             transformComponent.SetScale(scale);
        }

        template<typename T, typename UIFunction>
        inline static void DrawComponent(const std::string& name, Actor* actor, UIFunction function)
        {
            if(actor->HasComponent<T>())
            {
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4,4});
                
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap |
                                           ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding;
                T* component = actor->GetComponent<T>();

                ImGui::Separator();

                bool isOpen = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name.c_str());

                ImGui::SameLine(ImGui::GetWindowWidth() - 40.f);

                if(ImGui::Button("***", ImVec2{25.f,25.f}))
                    ImGui::OpenPopup("componentPopUp");

                ImGui::PopStyleVar();
                
                bool removeComponent = false;
                if(ImGui::BeginPopup("componentPopUp"))
                {
                    if(ImGui::MenuItem("Reset"))
                    {
                        LOG_ERROR("Implement the reset function!");
                        ImGui::CloseCurrentPopup();
                    }

                    if(ImGui::MenuItem("Remove Component"))
                    {
                        removeComponent = true;
                        ImGui::CloseCurrentPopup();
                    }
                    
                    ImGui::EndPopup();
                }

                if(isOpen)
                {
                    function(component);
                    ImGui::TreePop();
                }

                if(removeComponent)
                    actor->RemoveComponent<T>();
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
                    uint32_t drawOrder = component->GetDrawOrder();
                    DrawIntControl("Draw Order", drawOrder);
                    component->SetDrawOrder(drawOrder);
                    
                    ImGui::Text("Color");
                    ImGui::SameLine();

                    glm::vec4 spriteColor = component->GetColor();
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

            DrawComponent<Simple2DMovementComponent>("Simple Movement Component", actor,
                [](auto& component)
                {
                    glm::vec2 forwardSpeed = component->GetMoveSpeed();
                    DrawVec2Control("Forward Speed", forwardSpeed, 120.f);
                    component->SetMoveSpeed(forwardSpeed); 

                    float angularSpeed = component->GetAngularSpeed();
                    DrawFloatControl("Angular Speed", angularSpeed, 120.f);
                    component->SetAngularSpeed(angularSpeed);
                });

            DrawComponent<CircleDetectionComponent>("Circle Detection Component", actor,
                [](auto& component)
                {
                    float radius = component->GetRadius();
                    DrawFloatControl("Detection Radius", radius, 140.f);
                    component->SetRadius(radius);
                });

            DrawComponent<CameraComponent>("Camera Component", actor,
                [](auto& component)
                {
                    auto& sceneCamera = component->GetCamera();

                    const char* projectionTypeStrings[] = { "Orthographic", "Perspective" };
                    const char* currentProjectionType = projectionTypeStrings[(int)sceneCamera.GetProjectionType()];
                    if(ImGui::BeginCombo("Projection", currentProjectionType))
                    {
                        for (int i = 0; i < 2; ++i)
                        {
                            const bool isSelected = currentProjectionType == projectionTypeStrings[i];
                            if(ImGui::Selectable(projectionTypeStrings[i], isSelected))
                            {
                                currentProjectionType = projectionTypeStrings[i];
                                sceneCamera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(i));
                            }

                            if(isSelected)
                                ImGui::SetItemDefaultFocus();
                        }
                        
                        ImGui::EndCombo();
                    }

                    if(currentProjectionType == projectionTypeStrings[0])
                    {
                        auto orthoSize = sceneCamera.GetOrthographicSize();
                        DrawFloatControl("Size", orthoSize);
                        sceneCamera.SetOrthographicSize(orthoSize);

                        auto orthoNear = sceneCamera.GetOrthographicNearClip();
                        DrawFloatControl("Near Clip", orthoNear);
                        sceneCamera.SetOrthographicNearClip(orthoNear);

                        auto orthoFar = sceneCamera.GetOrthographicFarClip();
                        DrawFloatControl("Far Clip", orthoFar);
                        sceneCamera.SetOrthographicFarClip(orthoFar);
                    }
                    else if (currentProjectionType == projectionTypeStrings[1])
                    {
                        auto fov = glm::degrees(sceneCamera.GetPerspectiveFOV());
                        DrawFloatControl("Field of view", fov);
                        sceneCamera.SetPerspectiveFOV(glm::radians(fov));

                        auto perspectiveNear = sceneCamera.GetPerspectiveNearClip();
                        DrawFloatControl("Near Clip", perspectiveNear);
                        sceneCamera.SetPerspectiveNearClip(perspectiveNear);

                        auto perspectiveFar = sceneCamera.GetPerspectiveFarClip();
                        DrawFloatControl("Far Clip", perspectiveFar);
                        sceneCamera.SetPerspectiveFarClip(perspectiveFar);   
                    }
                });
            
            ImGui::Separator();
            
            ShowAddComponentButton(actor);
        }
        
    }
}
