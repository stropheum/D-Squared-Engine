#include "pch.h"
#include "Attributed.h"


namespace Library
{
    RTTI_DEFINITIONS(Attributed);

    Attributed::Attributed()
    {
        (*this)["this"] = static_cast<RTTI*>(this);
        m_prescribedAttributes.PushBack(
            Signature("this", DatumType::Pointer, 1u, static_cast<RTTI * *>(nullptr)));
    }

    Attributed::~Attributed()
    {
        m_prescribedAttributes.Clear();
    }

    Attributed::Attributed(const Attributed& rhs)
    {
        operator=(rhs);
    }

    Attributed& Attributed::operator=(const Attributed& rhs)
    {
        if (this != &rhs)
        {
            (*this)["this"] = static_cast<RTTI*>(this);

            m_prescribedAttributes = rhs.m_prescribedAttributes;
        }
        return *this;
    }

    Attributed::Attributed(Attributed&& rhs) noexcept :
        Scope(), m_prescribedAttributes()
    {
        (*this)["this"] = static_cast<RTTI*>(this);
        operator=(std::move(rhs));
    }

    Attributed& Attributed::operator=(Attributed&& rhs) noexcept
    {
        if (this != &rhs)
        {
            Scope::operator=(std::move(rhs));
            m_prescribedAttributes = std::move(rhs.m_prescribedAttributes);
        }
        return *this;
    }

    void Attributed::Populate()
    {
        for (std::uint32_t i = 0; i < m_prescribedAttributes.Size(); i++)
        {
            Signature& attribute = m_prescribedAttributes[i];
            auto& appendedScope = Append(attribute.Name);
            appendedScope = attribute.Type;

            switch (attribute.Type)
            {
            case DatumType::Integer:
                if (attribute.Storage.i != nullptr)
                {
                    appendedScope.SetType(DatumType::Integer);
                    appendedScope.SetStorage(attribute.Storage.i, attribute.Size);
                }
                break;

            case DatumType::Float:
                if (attribute.Storage.f != nullptr)
                {
                    appendedScope.SetType(DatumType::Float);
                    appendedScope.SetStorage(attribute.Storage.f, attribute.Size);
                }
                break;

            case DatumType::Vector:
                if (attribute.Storage.v != nullptr)
                {
                    appendedScope.SetType(DatumType::Vector);
                    appendedScope.SetStorage(attribute.Storage.v, attribute.Size);
                }
                break;

            case DatumType::Matrix:
                if (attribute.Storage.m != nullptr)
                {
                    appendedScope.SetType(DatumType::Matrix);
                    appendedScope.SetStorage(attribute.Storage.m, attribute.Size);
                }
                break;

            case DatumType::Scope:
                // Scopes don't have storage so do nothing
                break;

            case DatumType::String:
                if (attribute.Storage.s != nullptr)
                {
                    appendedScope.SetType(DatumType::String);
                    appendedScope.SetStorage(attribute.Storage.s, attribute.Size);
                }
                break;

            case DatumType::Pointer:
                if (attribute.Storage.r != nullptr)
                {
                    appendedScope.SetType(DatumType::Pointer);
                    appendedScope.SetStorage(attribute.Storage.r, attribute.Size);
                }
                break;

            default:
                throw std::exception("Setting storage of invalid/unknown type");
            }
        }
    }

    bool Attributed::IsPrescribedAttribute(const std::string& name) const
    {
        if (IsAttribute(name))
        {
            for (auto iter = m_prescribedAttributes.begin(); iter != m_prescribedAttributes.end(); ++iter)
            {
                if ((*iter).Name == name)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
    {
        return !IsPrescribedAttribute(name);
    }

    bool Attributed::IsAttribute(const std::string& name) const
    {
        return Find(name) != nullptr;
    }

    Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
    {
        return Append(name);
    }

}