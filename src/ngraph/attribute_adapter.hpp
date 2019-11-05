//*****************************************************************************
// Copyright 2017-2019 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include <vector>

#include "ngraph/enum_names.hpp"
#include "ngraph/type.hpp"

namespace ngraph
{
    template <typename Type>
    class ValueAccessor;

    /// ValueAccessor<void> is for values that do not provide
    template <>
    class ValueAccessor<void>
    {
    public:
        virtual const DiscreteTypeInfo& get_type_info() const = 0;
    };

    /// ValueAccessor<T> represents values that support get/set through T
    template <typename T>
    class ValueAccessor : public ValueAccessor<void>
    {
    public:
        virtual ~ValueAccessor() {}
        virtual const DiscreteTypeInfo& get_type_info() const = 0;
        /// Returns the value
        virtual const T& get() = 0;
        /// Sets the value
        virtual void set(const T& value) = 0;

    protected:
        T m_buffer;
        bool m_buffer_valid{false};
    };

    template <typename Type>
    class ValueReference
    {
    public:
        operator Type&() const { return m_value; }
    protected:
        ValueReference(Type& value)
            : m_value(value)
        {
        }
        Type& m_value;
    };

    template <typename Type>
    class AttributeAdapter
    {
    };

    template <typename Type>
    class EnumAttributeAdapterBase : public ValueReference<Type>, public ValueAccessor<std::string>
    {
    public:
        EnumAttributeAdapterBase(Type& value)
            : ValueReference<Type>(value)
        {
        }

        const std::string& get() override { return as_string(ValueReference<Type>::m_value); }
        void set(const std::string& value) override
        {
            ValueReference<Type>::m_value = as_enum<Type>(value);
        }
    };

    /// Note: These class bodies cannot be defined with templates because of interactions
    /// between dllexport and templates on Windows.
    template <>
    class AttributeAdapter<std::vector<int64_t>> : public ValueReference<std::vector<int64_t>>,
                                                   public ValueAccessor<std::vector<int64_t>>
    {
    public:
        AttributeAdapter(std::vector<int64_t>& value)
            : ValueReference<std::vector<int64_t>>(value)
        {
        }
        NGRAPH_API
        static constexpr DiscreteTypeInfo type_info{"AttributeAdapter<vector<int64_t>>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    template <>
    class AttributeAdapter<std::vector<uint64_t>> : public ValueReference<std::vector<uint64_t>>,
                                                    public ValueAccessor<std::vector<int64_t>>
    {
    public:
        AttributeAdapter(std::vector<uint64_t>& value)
            : ValueReference<std::vector<uint64_t>>(value)
        {
        }
        NGRAPH_API
        static constexpr DiscreteTypeInfo type_info{"AttributeAdapter<vector<uint64_t>>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    class Shape;
    template <>
    class AttributeAdapter<Shape> : public ValueReference<Shape>,
                                    public ValueAccessor<std::vector<int64_t>>
    {
    public:
        AttributeAdapter(Shape& value)
            : ValueReference<Shape>(value)
        {
        }
        NGRAPH_API
        static constexpr DiscreteTypeInfo type_info{"AttributeAdapter<Shape>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    class Strides;
    template <>
    class AttributeAdapter<Strides> : public ValueReference<Strides>,
                                      public ValueAccessor<std::vector<int64_t>>
    {
    public:
        AttributeAdapter(Strides& value)
            : ValueReference<Strides>(value)
        {
        }
        NGRAPH_API
        static constexpr DiscreteTypeInfo type_info{"AttributeAdapter<Strides>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    class AxisSet;
    template <>
    class AttributeAdapter<AxisSet> : public ValueReference<AxisSet>,
                                      public ValueAccessor<std::vector<int64_t>>
    {
    public:
        AttributeAdapter(AxisSet& value)
            : ValueReference<AxisSet>(value)
        {
        }
        NGRAPH_API
        static constexpr DiscreteTypeInfo type_info{"AttributeAdapter<AxisSet>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
        const std::vector<int64_t>& get() override;
        void set(const std::vector<int64_t>& value) override;
    };

    class PartialShape;
    template <>
    class AttributeAdapter<PartialShape> : public ValueReference<PartialShape>,
                                           public ValueAccessor<void>
    {
    public:
        AttributeAdapter(PartialShape& value)
            : ValueReference<PartialShape>(value)
        {
        }
        NGRAPH_API
        static constexpr DiscreteTypeInfo type_info{"AttributeAdapter<PartialShape>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
    };

    namespace element
    {
        class Type;
    }

    template <>
    class AttributeAdapter<element::Type> : public ValueReference<element::Type>,
                                            public ValueAccessor<void>
    {
    public:
        AttributeAdapter(element::Type& value)
            : ValueReference<element::Type>(value)
        {
        }
        NGRAPH_API
        static constexpr DiscreteTypeInfo type_info{"AttributeAdapter<element::Type>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
    };

    namespace op
    {
        struct AutoBroadcastSpec;
    }

    template <>
    class AttributeAdapter<op::AutoBroadcastSpec> : public ValueReference<op::AutoBroadcastSpec>,
                                                    public ValueAccessor<void>
    {
    public:
        AttributeAdapter(op::AutoBroadcastSpec& value)
            : ValueReference<op::AutoBroadcastSpec>(value)
        {
        }
        NGRAPH_API
        static constexpr DiscreteTypeInfo type_info{"AttributeAdapter<op::AutoBroadcastSpec>", 0};
        const DiscreteTypeInfo& get_type_info() const override { return type_info; }
    };
}
