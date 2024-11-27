#pragma once

class Actor;

class IPhysics
{
protected:
    ~IPhysics() = default;
};

class IOnOverlap : public IPhysics
{
public:
    virtual ~IOnOverlap() = default;

    virtual void OnOverlapping(Actor* other) = 0;
    virtual void OnOverlapEnter(Actor* other) = 0;
    virtual void OnOverlapExit(Actor* other) = 0;
    virtual const glm::vec2& GetCenter() const = 0;
    virtual float GetRadius() const = 0;
    virtual Actor* GetActor() const = 0;
    virtual bool IsOverlapping() const = 0;
    virtual void SetIsOverlapping(bool isOverlapping) = 0; 
};