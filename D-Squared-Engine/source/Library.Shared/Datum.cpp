#include "pch.h"
#include "Datum.h"


using namespace glm;

namespace Library
{
    Datum::Datum() :
        m_typeState(nullptr),
        m_type(DatumType::Unknown),
        m_data(),
        m_capacity(0),
        m_size(0),
        m_dataIsExternal(false)
    {}

    Datum::Datum(const DatumType& type) :
        m_typeState(nullptr),
        m_type(DatumType::Unknown),
        m_data(),
        m_capacity(0),
        m_size(0),
        m_dataIsExternal(false)
    {
        SetType(type);
        if (type != DatumType::Unknown)
        {
            Reserve(m_capacity);
        }
    }

    Datum::~Datum()
    {
        if (m_capacity > 0 && !m_dataIsExternal)
        {	// Don't bother clearing memory if there isn't any reserved space
            SetSize(0); // Remove all elements, allowing us to shrink buffer to zero
        }
    }

    Datum::Datum(const Datum& rhs) :
        m_typeState(nullptr),
        m_type(DatumType::Unknown),
        m_data(),
        m_capacity(0),
        m_size(0),
        m_dataIsExternal(false)
    {
        operator=(rhs); // Perform a deep copy of all the data
    }

    Datum& Datum::operator=(const Datum& rhs)
    {
        if (this != &rhs)
        {

            SetType(rhs.m_type); // Must Set Type in order to instantiate mTypeState
            if (rhs.m_dataIsExternal)
            {
                m_typeState->SetStorage(rhs);
            }
            else
            {
                Reserve(rhs.m_capacity);
                switch (rhs.m_type)
                {
                case DatumType::Integer:
                    for (std::uint32_t i = 0; i < rhs.m_size; i++)
                    {
                        PushBack(rhs.Get<std::int32_t>(i));
                    }
                    break;
                case DatumType::Float:
                    for (std::uint32_t i = 0; i < rhs.m_size; i++)
                    {
                        PushBack(rhs.Get<float>(i));
                    }
                    break;
                case DatumType::Vector:
                    for (std::uint32_t i = 0; i < rhs.m_size; i++)
                    {
                        PushBack(rhs.Get<vec4>(i));
                    }
                    break;
                case DatumType::Matrix:
                    for (std::uint32_t i = 0; i < rhs.m_size; i++)
                    {
                        PushBack(rhs.Get<mat4x4>(i));
                    }
                    break;
                case DatumType::String:
                    for (std::uint32_t i = 0; i < rhs.m_size; i++)
                    {
                        PushBack(rhs.Get<std::string>(i));
                    }
                    break;
                case DatumType::Pointer:
                    for (std::uint32_t i = 0; i < rhs.m_size; i++)
                    {
                        PushBack(rhs.Get<Library::RTTI*>(i));
                    }
                    break;
                default: break;
                }
            }
        }

        return *this;
    }

    Datum::Datum(Datum&& rhs) noexcept :
        m_typeState(nullptr), m_type(DatumType::Unknown), m_capacity(0), m_size(0), m_dataIsExternal(false)
    {
        operator=(std::move(rhs)); // Perform a deep copy of all the data
    }

    Datum& Datum::operator=(Datum&& rhs) noexcept
    {
        if (this != &rhs)
        {
            SetType(rhs.m_type); // Must Set Type in order to instantiate mTypeState
            if (rhs.m_dataIsExternal)
            {
                m_typeState->SetStorage(rhs);
            }
            else
            {
                m_data = std::move(rhs.m_data);
                m_type = std::move(rhs.m_type);
                m_capacity = std::move(rhs.m_capacity);
                m_size = std::move(rhs.m_size);
            }

            rhs.m_type = DatumType::Unknown;
            rhs.m_capacity = NULL;
            rhs.m_size = NULL;
        }

        return *this;
    }

    Scope& Datum::operator[](const std::uint32_t& index)
    {
        return Get<Scope>(index);
    }

    Datum& Datum::operator=(const DatumType& rhs)
    {
        SetType(rhs);
        return *this;
    }

    Datum& Datum::operator=(const std::int32_t& rhs)
    {
        if (m_typeState != nullptr)
        {
            return m_typeState->operator=(rhs);
        }
        SetType(DatumType::Integer);
        return m_typeState->operator=(rhs);
    }

    Datum& Datum::operator=(const float& rhs)
    {
        if (m_typeState != nullptr)
        {
            return m_typeState->operator=(rhs);
        }
        SetType(DatumType::Float);
        return m_typeState->operator=(rhs);
    }

    Datum& Datum::operator=(const vec4& rhs)
    {
        if (m_typeState != nullptr)
        {
            return m_typeState->operator=(rhs);
        }
        SetType(DatumType::Vector);
        return m_typeState->operator=(rhs);
    }

    Datum& Datum::operator=(const mat4x4& rhs)
    {
        if (m_typeState != nullptr)
        {
            return m_typeState->operator=(rhs);
        }
        SetType(DatumType::Matrix);
        return m_typeState->operator=(rhs);
    }

    Datum& Datum::operator=(Scope* const rhs)
    {
        if (m_typeState != nullptr)
        {
            return m_typeState->operator=(rhs);
        }
        SetType(DatumType::Scope);
        return m_typeState->operator=(rhs);
    }

    Datum& Datum::operator=(const std::string& rhs)
    {
        if (m_typeState != nullptr)
        {
            return m_typeState->operator=(rhs);
        }
        SetType(DatumType::String);
        return m_typeState->operator=(rhs);
    }

    Datum& Datum::operator=(Library::RTTI* const& rhs)
    {
        if (m_typeState != nullptr)
        {
            return m_typeState->operator=(rhs);
        }
        SetType(DatumType::Pointer);
        return m_typeState->operator=(rhs);
    }

    bool Datum::operator==(const Datum& rhs) const
    {
        if (m_type == DatumType::Unknown && rhs.m_type == DatumType::Unknown)
        {
            return true;
        }
        return m_typeState->operator==(rhs);
    }

    bool Datum::operator==(const DatumType& rhs) const
    {
        return m_type == rhs;
    }

    bool Datum::operator==(const std::int32_t& rhs) const
    {
        return m_type == DatumType::Integer &&
            m_size == 1 && m_data.i[0] == rhs;
    }

    bool Datum::operator==(const float& rhs) const
    {
        return 
            m_type == DatumType::Float &&
            m_size == 1 && 
            m_data.f[0] == rhs;
    }

    bool Datum::operator==(const vec4& rhs) const
    {
        return 
            m_type == DatumType::Vector &&
            m_size == 1 && 
            m_data.v[0] == rhs;
    }

    bool Datum::operator==(const mat4x4& rhs) const
    {
        return 
            m_type == DatumType::Matrix &&
            m_size == 1 && 
            m_data.m[0] == rhs;
    }

    bool Datum::operator==(const Scope* rhs) const
    {
        return 
            m_type == DatumType::Scope &&
            m_size == 1 && 
            m_data.sc[0] == rhs;
    }

    bool Datum::operator==(const std::string& rhs) const
    {
        return m_type == DatumType::String &&
            m_size == 1 && m_data.s[0] == rhs;
    }

    bool Datum::operator==(Library::RTTI* const& rhs) const
    {
        return 
            m_type == DatumType::Pointer &&
            m_size == 1 && 
            m_data.r[0] == rhs;
    }

    bool Datum::operator!=(const Datum& rhs) const
    {
        return !(m_typeState->operator==(rhs));
    }

    bool Datum::operator!=(const DatumType& rhs) const
    {
        return !(operator==(rhs));
    }

    bool Datum::operator!=(const std::int32_t& rhs) const
    {
        return !(operator==(rhs));
    }

    bool Datum::operator!=(const float& rhs) const
    {
        return !(operator==(rhs));
    }

    bool Datum::operator!=(const vec4& rhs) const
    {
        return !(operator==(rhs));
    }

    bool Datum::operator!=(const mat4x4& rhs) const
    {
        return !(operator==(rhs));
    }

    bool Datum::operator!=(const std::string& rhs) const
    {
        return !(operator==(rhs));
    }

    bool Datum::operator!=(Library::RTTI* const& rhs) const
    {
        return !(operator==(rhs));
    }

    DatumType Datum::Type() const
    {
        return m_type;
    }

    void Datum::SetType(const DatumType& type)
    {
        if (m_type == type)
        {
            return; // Avoid double instantiation of state without throwing an exception
        }

        if (m_type == DatumType::Unknown)
        {
            m_type = type;
        }
        else
        {
            throw std::exception("Attempting to change Type on Datum object");
        }

        switch (m_type)
        {
        case DatumType::Integer:
            m_typeState = std::make_unique<IntegerState>(*this);
            break;
        case DatumType::Float:
            m_typeState = std::make_unique<FloatState>(*this);
            break;
        case DatumType::Vector:
            m_typeState = std::make_unique<VectorState>(*this);
            break;
        case DatumType::Matrix:
            m_typeState = std::make_unique<MatrixState>(*this);
            break;
        case DatumType::Scope:
            m_typeState = std::make_unique<ScopeState>(*this);
            break;
        case DatumType::String:
            m_typeState = std::make_unique<StringState>(*this);
            break;
        case DatumType::Pointer:
            m_typeState = std::make_unique<PointerState>(*this);
            break;
        case DatumType::Unknown:
            break;
        default:
            break;
        }
    }

    std::uint32_t Datum::Size() const
    {
        return m_size;
    }

    std::uint32_t Datum::Capacity() const
    {
        return m_capacity;
    }

    void Datum::SetSize(const std::uint32_t& size) const
    {
        if (m_type == DatumType::Unknown)
        {
            return; // We don't have a type so we won't set size
        }
        if (m_dataIsExternal)
        {
            throw std::exception("Attempting to resize external storage");
        }
        m_typeState->SetSize(size);
    }

    void Datum::Reserve(const std::uint32_t& capacity) const
    {
        if (m_type == DatumType::Unknown)
        {
            return;
        }
        if (m_dataIsExternal)
        {
            throw std::exception("Attempting to resize external storage");
        }
        m_typeState->Reserve(capacity);
    }

    void Datum::Clear() const
    {
        if (m_type == DatumType::Unknown)
        {
            return; // We don't have a type so we do nothing
        }
        m_typeState->Clear();
    }

    void Datum::SetStorage(std::int32_t* data, const std::uint32_t& size)
    {
        if (m_typeState == nullptr)
        {
            SetType(DatumType::Integer);
        }

        m_typeState->SetStorage(data, size);
    }

    void Datum::SetStorage(float* data, const std::uint32_t& size)
    {
        if (m_typeState == nullptr)
        {
            SetType(DatumType::Float);
        }

        m_typeState->SetStorage(data, size);
    }

    void Datum::SetStorage(vec4* data, const std::uint32_t& size)
    {
        if (m_typeState == nullptr)
        {
            SetType(DatumType::Vector);
        }

        m_typeState->SetStorage(data, size);
    }

    void Datum::SetStorage(mat4x4* data, const std::uint32_t& size)
    {
        if (m_typeState == nullptr)
        {
            SetType(DatumType::Matrix);
        }

        m_typeState->SetStorage(data, size);
    }

    void Datum::SetStorage(std::string* data, const std::uint32_t& size)
    {
        if (m_typeState == nullptr)
        {
            SetType(DatumType::String);
        }

        m_typeState->SetStorage(data, size);
    }

    void Datum::SetStorage(Library::RTTI** data, const std::uint32_t& size)
    {
        if (m_typeState == nullptr)
        {
            SetType(DatumType::Pointer);
        }

        m_typeState->SetStorage(data, size);
    }

    void Datum::Set(const std::int32_t& value, const std::uint32_t& index)
    {
        if (m_type != DatumType::Integer)
        {
            throw std::exception("Calling Set on invalid Type");
        }
        if (index > m_size)
        {
            throw std::exception("Attempting to Set beyond current Size");
        }
        if (index == m_size)
        {
            PushBack(value); // If setting end, divert functionality to a push Back
        }
        new(m_data.i + index) std::int32_t(value);
    }

    void Datum::Set(const float& value, const std::uint32_t& index)
    {
        if (m_type != DatumType::Float)
        {
            throw std::exception("Calling Set on invalid Type");
        }
        if (index > m_size)
        {
            throw std::exception("Attempting to Set beyond current Size");
        }
        if (index == m_size)
        {
            PushBack(value); // If setting end, divert functionality to a push Back
        }
        new(m_data.f + index) float(value);
    }

    void Datum::Set(const vec4& value, const std::uint32_t& index)
    {
        if (m_type != DatumType::Vector)
        {
            throw std::exception("Calling Set on invalid Type");
        }
        if (index > m_size)
        {
            throw std::exception("Attempting to Set beyond current Size");
        }
        if (index == m_size)
        {
            PushBack(value); // If setting end, divert functionality to a push Back
        }
        new(m_data.v + index) vec4(value);
    }

    void Datum::Set(const mat4x4& value, const std::uint32_t& index)
    {
        if (m_type != DatumType::Matrix)
        {
            throw std::exception("Calling Set on invalid Type");
        }
        if (index > m_size)
        {
            throw std::exception("Attempting to Set beyond current Size");
        }
        if (index == m_size)
        {
            PushBack(value); // If setting end, divert functionality to a push Back
        }
        new(m_data.m + index) mat4x4(value);
    }

    void Datum::Set(Scope* const& value, const std::uint32_t& index)
    {
        if (m_type != DatumType::Scope)
        {
            throw std::exception("Calling Set on invalid Type");
        }
        if (index > m_size)
        {
            throw std::exception("Attempting to Set beyond current Size");
        }
        if (index == m_size)
        {
            PushBack(value); // If setting end, divert functionality to a push Back
        }
        new(m_data.sc + index) Scope* (value);
    }

    void Datum::Set(const std::string& value, const std::uint32_t& index)
    {
        if (m_type != DatumType::String)
        {
            throw std::exception("Calling Set on invalid Type");
        }
        if (index > m_size)
        {
            throw std::exception("Attempting to Set beyond current Size");
        }
        if (index == m_size)
        {
            PushBack(value); // If setting end, divert functionality to a push Back
        }

        m_data.s[index] = value;
    }

    void Datum::Set(Library::RTTI* const& value, const std::uint32_t& index)
    {
        if (m_type != DatumType::Pointer)
        {
            throw std::exception("Calling Set on invalid Type");
        }
        if (index > m_size)
        {
            throw std::exception("Attempting to Set beyond current Size");
        }
        if (index == m_size)
        {
            PushBack(value); // If setting end, divert functionality to a push Back
        }
        new(m_data.r + index) RTTI* (value);
    }

    void Datum::PushBack(const std::int32_t& value)
    {
        SetSize(m_size + 1);
        Set(value, m_size - 1);
    }

    void Datum::PushBack(const float& value)
    {
        SetSize(m_size + 1);
        Set(value, m_size - 1);
    }

    void Datum::PushBack(const vec4& value)
    {
        SetSize(m_size + 1);
        Set(value, m_size - 1);
    }

    void Datum::PushBack(const mat4x4& value)
    {
        SetSize(m_size + 1);
        Set(value, m_size - 1);
    }

    void Datum::PushBack(Scope* const& value)
    {
        SetSize(m_size + 1);
        Set(value, m_size - 1);
    }

    void Datum::PushBack(const std::string& value)
    {
        SetSize(m_size + 1);
        Set(value, m_size - 1);
    }

    void Datum::PushBack(RTTI* const& value)
    {
        if (value == nullptr)
        {
            throw std::exception("Attempting to push Back nullptr");
        }
        SetSize(m_size + 1);
        Set(value, m_size - 1);
    }

    void Datum::Remove(Scope* const scope)
    {
        if (m_type == DatumType::Scope)
        {
            for (std::uint32_t i = 0; i < m_size; i++)
            {
                if (m_data.sc[i] == scope)
                {
                    m_data.sc[i]->~Scope();
                    memmove(m_data.sc[i], m_data.sc[i + 1], m_size - i - 1);
                    m_size--;
                }
            }
        }
    }

    void Datum::SetFromString(const std::string& value, const std::uint32_t& index) const
    {
        m_typeState->SetFromString(value, index);
    }

    std::string Datum::ToString(const std::uint32_t& index) const
    {
        if (m_type == DatumType::Unknown)
        {
            return "Unknown Type";
        }
        return m_typeState->ToString(index);
    }

    template<>
    std::int32_t& Datum::Get(const std::uint32_t& index)
    {
        if (m_type != DatumType::Integer)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.i == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.i[index];
    }

    template<>
    const std::int32_t& Datum::Get(const std::uint32_t& index) const
    {
        if (m_type != DatumType::Integer)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.i == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size) 
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.i[index];
    }

    template<>
    float& Datum::Get(const std::uint32_t& index)
    {
        if (m_type != DatumType::Float)
        { 
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.f == nullptr)
        { 
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size) 
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.f[index];
    }

    template<>
    const float& Datum::Get(const std::uint32_t& index) const
    {
        if (m_type != DatumType::Float)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.f == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.f[index];
    }

    template<>
    vec4& Datum::Get(const std::uint32_t& index)
    {
        if (m_type != DatumType::Vector)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.f == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.v[index];
    }

    template<>
    const vec4& Datum::Get(const std::uint32_t& index) const
    {
        if (m_type != DatumType::Vector)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.f == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.v[index];
    }

    template<>
    mat4x4& Datum::Get(const std::uint32_t& index)
    {
        if (m_type != DatumType::Matrix)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.f == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.m[index];
    }

    template<>
    const mat4x4& Datum::Get(const std::uint32_t& index) const
    {
        if (m_type != DatumType::Matrix)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.f == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.m[index];
    }

    template<>
    Scope& Datum::Get(const std::uint32_t& index)
    {
        if (m_type != DatumType::Scope)
        {
            throw std::exception("Calling et on invalid Type");
        }
        if (m_data.sc == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return *m_data.sc[index];
    }

    template<>
    const Scope& Datum::Get(const std::uint32_t& index) const
    {
        if (m_type != DatumType::Scope)
        {
            throw std::exception("Calling et on invalid Type");
        }
        if (m_data.sc == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return *m_data.sc[index];
    }

    template<>
    std::string& Datum::Get(const std::uint32_t& index)
    {
        if (m_type != DatumType::String)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.s == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.s[index];
    }

    template<>
    const std::string& Datum::Get(const std::uint32_t& index) const
    {
        if (m_type != DatumType::String)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.s == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.s[index];
    }

    template<>
    Library::RTTI*& Datum::Get(const std::uint32_t& index)
    {
        if (m_type != DatumType::Pointer)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.r == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.r[index];
    }

    template<>
    Library::RTTI* const& Datum::Get(const std::uint32_t& index) const
    {
        if (m_type != DatumType::Pointer)
        {
            throw std::exception("Calling Get on invalid Type");
        }
        if (m_data.r == nullptr)
        {
            throw std::exception("Attempting to dereference nullptr");
        }
        if (index >= m_size)
        {
            throw std::exception("Accessing beyond array bounds");
        }
        return m_data.r[index];
    }
}