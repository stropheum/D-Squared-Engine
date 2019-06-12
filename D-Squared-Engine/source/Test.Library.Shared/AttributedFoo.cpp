#include "pch.h"
#include "AttributedFoo.h"
#include "Signature.h"
#include <Datum.h>
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"


using namespace std;

namespace Library
{
    Datum::DatumValues* storage;
    AttributedFoo::AttributedFoo() :
        Attributed(), m_int(0), m_float(0.0f), m_vector(0), m_matrix(0), m_string(""), m_scope()
    {
        init();
    }

    AttributedFoo::~AttributedFoo()
    {
        delete[] iArray;
        delete[] fArray;
        delete[] vArray;
        delete[] mArray;
        delete[] sArray;
    }

    AttributedFoo::AttributedFoo(const AttributedFoo& rhs) :
        Attributed(rhs)
    {
        operator=(rhs);
    }

    AttributedFoo& AttributedFoo::operator=(const AttributedFoo& rhs)
    {
        init();

        (*this)["External Integer"].SetStorage(&m_int, 1u);
        (*this)["External Float"].SetStorage(&m_float, 1u);
        (*this)["External Vector"].SetStorage(&m_vector, 1u);
        (*this)["External Matrix"].SetStorage(&m_matrix, 1u);
        (*this)["External String"].SetStorage(&m_string, 1u);

        (*this)["External Integer Array"].SetStorage(iArray, 10u);
        (*this)["External Float Array"].SetStorage(fArray, 10u);
        (*this)["External Vector Array"].SetStorage(vArray, 10u);
        (*this)["External Matrix Array"].SetStorage(mArray, 10u);
        (*this)["External String Array"].SetStorage(sArray, 10u);

        m_int = rhs.m_int;
        m_float = rhs.m_float;
        m_vector = rhs.m_vector;
        m_matrix = rhs.m_matrix;
        m_string = rhs.m_string;
        m_scope = rhs.m_scope;

        for (std::uint32_t i = 0; i < 10; i++)
        {
            iArray[i] = rhs.iArray[i];
            fArray[i] = rhs.fArray[i];
            vArray[i] = rhs.vArray[i];
            mArray[i] = rhs.mArray[i];
            sArray[i] = rhs.sArray[i];
        }

        return (*this);
    }

    AttributedFoo::AttributedFoo(AttributedFoo&& rhs) noexcept :
        Attributed(move(rhs))
    {
        m_int = move(rhs.m_int);
        m_float = move(rhs.m_float);
        m_vector = move(rhs.m_vector);
        m_matrix = move(rhs.m_matrix);
        m_string = move(rhs.m_string);
        m_scope = move(rhs.m_scope);

        iArray = move(rhs.iArray);
        fArray = move(rhs.fArray);
        vArray = move(rhs.vArray);
        mArray = move(rhs.mArray);
        sArray = move(rhs.sArray);

        (*this)["External Integer"].SetStorage(&m_int, 1u);
        (*this)["External Float"].SetStorage(&m_float, 1u);
        (*this)["External Vector"].SetStorage(&m_vector, 1u);
        (*this)["External Matrix"].SetStorage(&m_matrix, 1u);
        (*this)["External String"].SetStorage(&m_string, 1u);

        (*this)["External Integer Array"].SetStorage(iArray, 10u);
        (*this)["External Float Array"].SetStorage(fArray, 10u);
        (*this)["External Vector Array"].SetStorage(vArray, 10u);
        (*this)["External Matrix Array"].SetStorage(mArray, 10u);
        (*this)["External String Array"].SetStorage(sArray, 10u);

        rhs.m_int = 0;
        rhs.m_float = 0.0f;
        rhs.m_vector = glm::vec4(0);
        rhs.m_matrix = glm::mat4(0);
        rhs.m_string = "";
        rhs.iArray = nullptr;
        rhs.fArray = nullptr;
        rhs.vArray = nullptr;
        rhs.mArray = nullptr;
        rhs.sArray = nullptr;
    }

    AttributedFoo& AttributedFoo::operator=(AttributedFoo&& rhs) noexcept
    {
        if (this != &rhs)
        {
            Attributed::operator=(move(rhs));

            m_int = move(rhs.m_int);
            m_float = move(rhs.m_float);
            m_vector = move(rhs.m_vector);
            m_matrix = move(rhs.m_matrix);
            m_string = move(rhs.m_string);
            m_scope = move(rhs.m_scope);

            iArray = move(rhs.iArray);
            fArray = move(rhs.fArray);
            vArray = move(rhs.vArray);
            mArray = move(rhs.mArray);
            sArray = move(rhs.sArray);

            (*this)["External Integer"].SetStorage(&m_int, 1u);
            (*this)["External Float"].SetStorage(&m_float, 1u);
            (*this)["External Vector"].SetStorage(&m_vector, 1u);
            (*this)["External Matrix"].SetStorage(&m_matrix, 1u);
            (*this)["External String"].SetStorage(&m_string, 1u);

            (*this)["External Integer Array"].SetStorage(iArray, 10u);
            (*this)["External Float Array"].SetStorage(fArray, 10u);
            (*this)["External Vector Array"].SetStorage(vArray, 10u);
            (*this)["External Matrix Array"].SetStorage(mArray, 10u);
            (*this)["External String Array"].SetStorage(sArray, 10u);

            rhs.m_int = 0;
            rhs.m_float = 0.0f;
            rhs.m_vector = glm::vec4(0);
            rhs.m_matrix = glm::mat4(0);
            rhs.m_string = "";
            rhs.iArray = nullptr;
            rhs.fArray = nullptr;
            rhs.vArray = nullptr;
            rhs.mArray = nullptr;
            rhs.sArray = nullptr;
        }

        return (*this);
    }

    void AttributedFoo::init()
    {
        m_prescribedAttributes.PushBack(
            Signature("External Integer", DatumType::Integer, 1u, &m_int)
        );

        m_prescribedAttributes.PushBack(
            Signature("External Float", DatumType::Float, 1u, &m_float)
        );

        m_prescribedAttributes.PushBack(
            Signature("External Vector", DatumType::Vector, 1u, &m_vector)
        );

        m_prescribedAttributes.PushBack(
            Signature("External Matrix", DatumType::Matrix, 1u, &m_matrix)
        );

        m_prescribedAttributes.PushBack(
            Signature("External String", DatumType::String, 1u, &m_string)
        );

        m_prescribedAttributes.PushBack(
            Signature("Internal Scope", DatumType::Scope, 1u, &m_scope)
        );

        iArray = new std::int32_t[10];
        fArray = new float[10];
        vArray = new glm::vec4[10];
        mArray = new glm::mat4[10];
        sArray = new std::string[10];

        for (std::uint32_t i = 0; i < 10; i++)
        {
            iArray[i] = 10;
            fArray[i] = 10.0f;
        }

        m_prescribedAttributes.PushBack(
            Signature("External Integer Array", DatumType::Integer, 10u, iArray)
        );

        m_prescribedAttributes.PushBack(
            Signature("External Float Array", DatumType::Float, 10u, fArray)
        );

        m_prescribedAttributes.PushBack(
            Signature("External Vector Array", DatumType::Vector, 10u, vArray)
        );

        m_prescribedAttributes.PushBack(
            Signature("External Matrix Array", DatumType::Matrix, 10u, mArray)
        );

        m_prescribedAttributes.PushBack(
            Signature("External String Array", DatumType::String, 10u, sArray)
        );

        Populate();
    }
}