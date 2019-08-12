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

#include "ngraph/attribute.hpp"
#include "ngraph/coordinate_diff.hpp"
#include "ngraph/op/op.hpp"

namespace ngraph
{
    namespace op
    {
        namespace util
        {
            class GenOp : public Op
            {
            protected:
                GenOp();
                GenOp(const OutputVector& arguments);

            public:
                virtual std::vector<std::string> get_argument_keys() const = 0;
                virtual std::vector<std::string> get_result_keys() const = 0;
                virtual std::vector<std::string> get_attribute_keys() const = 0;
                virtual Input<const Node> get_argument(const std::string& name) const = 0;
                virtual Input<Node> get_argument(const std::string& name) = 0;
                virtual Output<const Node> get_result(const std::string& name) const = 0;
                virtual Output<Node> get_result(const std::string& name) = 0;
                virtual const AttributeBase& get_attribute(const std::string& name) const = 0;
            };
        }
    }
}
