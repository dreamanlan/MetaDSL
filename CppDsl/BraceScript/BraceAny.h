#pragma once
#include "BraceScript.h"

namespace Brace
{
    class Any;
    template<typename ValueType> ValueType
        AnyCast(const Any& operand);

    class Any final
    {
    public:
        Any() : m_Content(nullptr)
        {
        }
        template<typename ValueType>
        inline Any(const ValueType& value)
            : m_Content(new holder<ValueType>(value))
        {
        }
        Any(const Any& other)
            : m_Content(other.m_Content ? other.m_Content->clone() : nullptr)
        {
        }
        Any(Any&& other)
            : m_Content(other.m_Content)
        {
            other.m_Content = nullptr;
        }
        virtual ~Any()
        {
            reset();
        }
    public:
        Any& swap(Any& rhs)
        {
            std::swap(m_Content, rhs.m_Content);
            return *this;
        }
        template<typename ValueType>
        inline Any& operator=(const ValueType& rhs)
        {
            Any(rhs).swap(*this);
            return *this;
        }
        Any& operator=(const Any& rhs)
        {
            Any(rhs).swap(*this);
            return *this;
        }
        Any& operator=(Any&& rhs)
        {
            rhs.swap(*this);
            return *this;
        }
    public:
        bool has_value() const
        {
            return m_Content != nullptr;
        }
        void reset()
        {
            delete m_Content;
            m_Content = nullptr;
        }
        template<typename ValueType>
        inline ValueType* cast()const
        {
            return holder<ValueType>::DoCast(m_Content);
        }
    private:
        class placeholder
        {
        public:
            virtual ~placeholder()
            {
            }
        public:
            virtual placeholder* clone() const = 0;
            virtual const void* typetag() const = 0;
        };

        template<typename ValueType>
        class holder final : public placeholder
        {
        public:
            holder(const ValueType& value)
                : held(value)
            {
            }
        public:
            virtual placeholder* clone() const override
            {
                return new holder(held);
            }
            virtual const void* typetag() const override
            {
                return reinterpret_cast<const void*>(&DoCast);
            }
        public:
            ValueType held;
        public:
            static ValueType* DoCast(placeholder* p)
            {
                return p && (p->typetag() == reinterpret_cast<const void*>(&DoCast))
                    ? &static_cast<holder<ValueType>*>(p)->held
                    : 0;
            }
        };
    private:
        placeholder* m_Content;
    };

    template<typename ValueType>
    inline ValueType* AnyCast(Any* operand)
    {
        return operand->cast<ValueType>();
    }

    template<typename ValueType>
    inline const ValueType* AnyCast(const Any* operand)
    {
        return operand->cast<ValueType>();
    }
}
