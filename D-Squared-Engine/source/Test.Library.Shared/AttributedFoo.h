#pragma once
#include <Attributed.h>
#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)

namespace Library
{
    class AttributedFoo : public Attributed
    {
    public:
        AttributedFoo();
        ~AttributedFoo();

        AttributedFoo(const AttributedFoo& rhs);
        AttributedFoo& operator=(const AttributedFoo& rhs);

        AttributedFoo(AttributedFoo&& rhs) noexcept;
        AttributedFoo& operator=(AttributedFoo&& rhs) noexcept;

    private:
        void init();

    public:
        // Individual members
        std::int32_t m_int;
        float m_float;
        glm::vec4 m_vector;
        glm::mat4 m_matrix;
        std::string m_string;
        Scope* m_scope;

        // Array members
        std::int32_t* iArray;
        float* fArray;
        glm::vec4* vArray;
        glm::mat4* mArray;
        std::string* sArray;
    };
}