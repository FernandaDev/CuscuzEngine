#include "pch.h"

#include "LevelSerializer.h"
#include "Cuscuz/World/Level.h"
#include "Actor.h"
#define YAML_CPP_API
#include <yaml-cpp/yaml.h>

#include "Components/CameraComponent.h"
#include "Components/CircleDetectionComponent.h"
#include "Components/Simple2DMovementComponent.h"
#include "Components/SpriteRenderer.h"
#include "Cuscuz/Render/Sprite.h"
#include "Cuscuz/Render/Texture.h"

namespace YAML
{
    template<>
    struct convert<glm::vec2>
    {
        static Node encode(const glm::vec2& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            return node;
        }
        static bool decode(const Node& node, glm::vec2& rhs)
        {
            if(!node.IsSequence() || node.size() != 2)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();

            return true;
        }
    };
    template<>
    struct convert<glm::vec3>
    {
        static Node encode(const glm::vec3& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }
        static bool decode(const Node& node, glm::vec3& rhs)
        {
            if(!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();

            return true;
        }
    };
    template<>
    struct convert<glm::vec4>
    {
        static Node encode(const glm::vec4& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            return node;
        }
        static bool decode(const Node& node, glm::vec4& rhs)
        {
            if(!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();

            return true;
        }
    };
}

namespace Cuscuz
{
    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& value)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << value.x << value.y << YAML::EndSeq;
        return out;
    }
    
    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& value)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << value.x << value.y << value.z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& value)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << value.x << value.y << value.z << value.w << YAML::EndSeq;
        return out;
    }
        
    LevelSerializer::LevelSerializer(const CC_AssetRef<Level>& level) :
    m_Level(level) {}

    static void SerializeActor(YAML::Emitter& out, Actor* actor)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Actor" << YAML::Value << "1231232312";
        out << YAML::Key << "Name" << YAML::Value << actor->GetName();

        const auto& transform = actor->GetTransform();
        out << YAML::Key << "TransformComponent";
        out << YAML::BeginMap;
        out << YAML::Key << "Position" << YAML::Value << transform.GetPosition();
        out << YAML::Key << "Rotation" << YAML::Value << transform.GetRotation();
        out << YAML::Key << "Scale" << YAML::Value << transform.GetScale();
        out << YAML::EndMap;

        if(const auto cameraComponent = actor->GetComponent<CameraComponent>())
        {
            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap;

            const auto camera = cameraComponent->GetCamera();
            out << YAML::Key << "ProjectionType" << YAML::Value << static_cast<int>(camera.GetProjectionType());
            out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveFOV();
            out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
            out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
            out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
            out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
            out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();

            out << YAML::EndMap;
        }

        if(const auto spriteRenderer = actor->GetComponent<SpriteRenderer>())
        {
            out << YAML::Key << "SpriteRenderer";
            out << YAML::BeginMap;

            out << YAML::Key << "DrawOrder" << YAML::Value << spriteRenderer->GetDrawOrder();
            out << YAML::Key << "Color" << YAML::Value << spriteRenderer->GetColor();
            
            out << YAML::EndMap;
        }

        if(const auto circleDetection = actor->GetComponent<CircleDetectionComponent>())
        {
            out << YAML::Key << "CircleDetectionComponent";
            out << YAML::BeginMap;

            out << YAML::Key << "Radius" << YAML::Value << circleDetection->GetRadius();

            out << YAML::EndMap;
        }

        if(const auto simpleMovement = actor->GetComponent<Simple2DMovementComponent>())
        {
            out << YAML::Key << "Simple2DMovementComponent";
            out << YAML::BeginMap;

            out << YAML::Key << "MoveSpeed" << YAML::Value << simpleMovement->GetMoveSpeed();
            out << YAML::Key << "AngularSpeed" << YAML::Value << simpleMovement->GetAngularSpeed();

            out << YAML::EndMap;
        }
        
        out << YAML::EndMap;
    }
    
    void LevelSerializer::Serialize(const std::string& filepath)
    {
        YAML::Emitter out;

        out << YAML::BeginMap;
        out << YAML::Key << "Level" << YAML::Value << m_Level->GetName().data();
        out << YAML::Key << "Actors" << YAML::Value << YAML::BeginSeq;
        for (auto& actor : m_Level->GetAllActors())
        {
            SerializeActor(out, actor.get());
        }
        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fOut(filepath);
        fOut << out.c_str();
    }

    void LevelSerializer::SerializeRuntime(const std::string& filepath)
    {
        CC_ASSERT(false, "Not implemented")
    }

    bool LevelSerializer::Deserialize(const std::string& filepath)
    {
        std::ifstream stream(filepath);
        std::stringstream ss;
        ss << stream.rdbuf();

        YAML::Node data = YAML::Load(ss.str());

        if(!data["Level"])
            return false;

        auto levelName = data["Level"].as<std::string>();

        if(auto actors = data["Actors"])
        {
            for (auto actor : actors)
            {
                uint64_t uuid = actor["Actor"].as<uint64_t>();
                auto actorName = actor["Name"].as<std::string>();

                auto transform = actor["TransformComponent"];
                auto position = transform["Position"].as<glm::vec3>();
                auto rotation = transform["Rotation"].as<glm::vec3>();
                auto scale = transform["Scale"].as<glm::vec3>();
                
                auto newActor = std::make_shared<Actor>(m_Level, std::move(actorName), 
                position, scale, rotation);

                if(auto cameraCompNode = actor["CameraComponent"])
                {
                    auto& cameraComponent = newActor->AddComponent<CameraComponent>();
                    SceneCamera& camera = cameraComponent.GetCamera();

                    auto projectionType = cameraCompNode["ProjectionType"].as<int>();
                    camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(projectionType));

                    auto perspectiveFOV = cameraCompNode["PerspectiveFOV"].as<float>();
                    camera.SetPerspectiveFOV(perspectiveFOV);

                    auto perspectiveNear = cameraCompNode["PerspectiveNear"].as<float>();
                    camera.SetPerspectiveNearClip(perspectiveNear);

                    auto perspectiveFar = cameraCompNode["PerspectiveFar"].as<float>();
                    camera.SetPerspectiveFarClip(perspectiveFar);

                    auto orthographicSize = cameraCompNode["OrthographicSize"].as<float>();
                    camera.SetOrthographicSize(orthographicSize);

                    auto orthographicNear = cameraCompNode["OrthographicNear"].as<float>();
                    camera.SetOrthographicNearClip(orthographicNear);

                    auto orthographicFar = cameraCompNode["OrthographicFar"].as<float>();
                    camera.SetOrthographicFarClip(orthographicFar);
                }

                if(auto spriteRendererNode = actor["SpriteRenderer"])
                {
                    auto& spriteRenderer = newActor->AddComponent<SpriteRenderer>();

                    auto drawOrder = spriteRendererNode["DrawOrder"].as<uint32_t>();
                    spriteRenderer.SetDrawOrder(drawOrder);

                    auto spriteColor = spriteRendererNode["Color"].as<glm::vec4>();
                    spriteRenderer.SetColor(spriteColor);
                }

                if(auto circleDetectionNode = actor["CircleDetectionComponent"])
                {
                    auto& circleDetectionComp = newActor->AddComponent<CircleDetectionComponent>();

                    auto radius = circleDetectionNode["Radius"].as<float>();
                    circleDetectionComp.SetRadius(radius);
                }

                if(auto simpleMovementNode = actor["Simple2DMovementComponent"])
                {
                    auto& simpleMovementComp = newActor->AddComponent<Simple2DMovementComponent>();

                    auto moveSpeed = simpleMovementNode["MoveSpeed"].as<glm::vec2>();
                    simpleMovementComp.SetMoveSpeed(moveSpeed);

                    auto angularSpeed = simpleMovementNode["AngularSpeed"].as<float>();
                    simpleMovementComp.SetAngularSpeed(angularSpeed);
                }

                m_Level->AddActor(newActor);
            }
        }
        
        return true;
    }

    bool LevelSerializer::DeserializeRuntime(const std::string& filepath)
    {
        CC_ASSERT(false, "Not implemented")
        return false;
    }
}
