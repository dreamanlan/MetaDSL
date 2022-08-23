#pragma once
//Modified from Ogre::Any

#include "BraceScript.h"

namespace Brace
{
    class Any;
    template<typename ValueType> ValueType
        AnyCast(const Any& operand);

    class Any final : public IBraceObject
    {
    public:
        Any(void) : m_Content(nullptr)
        {
        }
        template<typename ValueType>
        Any(const ValueType& value)
            : m_Content(new(holder<ValueType>)(value))
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
        virtual ~Any(void)
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
        Any& operator=(const ValueType& rhs)
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
        bool has_value(void) const
        {
            return m_Content != nullptr;
        }
        const std::type_info& type(void) const
        {
            return m_Content ? m_Content->getType() : typeid(void);
        }
        void reset(void)
        {
            delete m_Content;
            m_Content = nullptr;
        }
    protected:
        class placeholder
        {
        public:
            virtual ~placeholder(void)
            {
            }
        public:
            virtual const std::type_info& getType(void) const = 0;
            virtual placeholder* clone(void) const = 0;
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
            virtual const std::type_info& getType(void) const override
            {
                return typeid(ValueType);
            }
            virtual placeholder* clone(void) const override
            {
                return new holder(held);
            }
        public:
            ValueType held;
        };
    protected:
        placeholder* m_Content;

        template<typename ValueType>
        friend ValueType* AnyCast(Any*);
    };

    template<typename ValueType>
    ValueType* AnyCast(Any* operand)
    {
        return operand && (operand->type() == typeid(ValueType))
            ? &static_cast<Any::holder<ValueType>*>(operand->m_Content)->held
            : 0;
    }

    template<typename ValueType>
    const ValueType* AnyCast(const Any* operand)
    {
        return AnyCast<ValueType>(const_cast<Any*>(operand));
    }
}
