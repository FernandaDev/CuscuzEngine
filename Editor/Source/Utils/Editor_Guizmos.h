#pragma once

#include "ImGuizmo.h"
#include "Cuscuz/Render/Camera.h"
#include "Cuscuz/World/Actor.h"
#include "gtc/type_ptr.hpp"
#include "ImGui/imgui.h"

namespace Cuscuz::Editor
{
    static void DrawGizmos(ImGuizmo::OPERATION operation, const glm::vec2& viewportSize, Actor* actor, const OrthographicCamera& camera, ImGuizmo::MODE mode = ImGuizmo::LOCAL)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        const ImVec2 contentRegionMin = ImGui::GetWindowContentRegionMin();
        const ImVec2 windowPos = ImGui::GetWindowPos();
        const ImVec2 imagePos = { windowPos.x + contentRegionMin.x, windowPos.y + contentRegionMin.y };
        ImGuizmo::SetRect(imagePos.x, imagePos.y, viewportSize.x, viewportSize.y);

        glm::mat4 cameraProjection = camera.GetProjectionMatrix();
        glm::mat4 cameraView = camera.GetViewMatrix();
        auto actorTransform = actor->GetTransform().GetWorldTransform();

        const bool shouldSnap = Input::IsKeyPressed(CC_KeyCode::LCtrl);
        float snapValue = 0.5f;
        if(operation == ImGuizmo::OPERATION::ROTATE)
            snapValue = 45.f;

        const float snapValues[3] = { snapValue, snapValue, snapValue};
        
        ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
            operation, mode, glm::value_ptr(actorTransform), nullptr, shouldSnap ? snapValues : nullptr);

        if(ImGuizmo::IsUsing())
        {
            glm::vec3 position, rotation, scale;

            Math::DecomposeTransform(actorTransform, position, rotation, scale);

            TransformComponent& transformComp = actor->GetTransform();
            
            transformComp.SetPosition(position);

            const glm::vec3 currentRotation = transformComp.GetRotation();
            const glm::vec3 deltaRotation = rotation - currentRotation;
            transformComp.SetRotation(currentRotation + deltaRotation);

            transformComp.SetScale(scale);
        }
    }
}
