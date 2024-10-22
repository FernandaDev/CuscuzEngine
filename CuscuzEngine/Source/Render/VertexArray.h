#pragma once

class VertexArray
{
    unsigned int m_NumberOfVerts;
    unsigned int m_NumberOfIndices;
    
    unsigned int m_VertexBuffer;
    unsigned int m_IndexBuffer;
    unsigned int m_VertexArray;
        
public:
    VertexArray(const float* verts, unsigned int numVerts,
                const unsigned int* indices, unsigned int numIndices);
    ~VertexArray();

    void SetActive();

    unsigned int GetNumIndices() const { return m_NumberOfIndices; }
    unsigned int GetNumVerts() const { return m_NumberOfVerts; }
};
