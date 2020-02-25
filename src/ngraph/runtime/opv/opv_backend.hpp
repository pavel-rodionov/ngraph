//*****************************************************************************
// Copyright 2017-2020 Intel Corporation
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

#include <ie_core.hpp>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "ngraph/runtime/opv/opv_backend_visibility.hpp"

#include "ngraph/runtime/backend_manager.hpp"
#include "ngraph/runtime/tensor.hpp"
#include "ngraph/runtime/opv/opv_tensor.hpp"


namespace ngraph
{
    namespace runtime
    {
        namespace opv
        {
            class OPVBackend;
            class OPVExecutable;
            class OPVBackendConstructor;
        }
    }
}

class ngraph::runtime::opv::OPVBackend : public Backend
{
public:
    OPVBackend();
    OPVBackend(const std::vector<std::string>& unsupported_op_name_list);
    OPVBackend(const OPVBackend&) = delete;
    OPVBackend(OPVBackend&&) = delete;
    OPVBackend& operator=(const OPVBackend&) = delete;

    std::shared_ptr<Tensor>
        create_tensor(const element::Type& type, const Shape& shape, void* memory_pointer) override;

    std::shared_ptr<Tensor> create_tensor(const element::Type& type, const Shape& shape) override;

    std::shared_ptr<Executable> compile(std::shared_ptr<Function> function,
                                        bool enable_performance_data = false) override;
    std::shared_ptr<Executable> load(std::istream& input_stream) override;

    bool is_supported(const Node& node) const override;

    bool set_config(const std::map<std::string, std::string>& config, std::string& error) override;

private:
    std::set<std::string> m_unsupported_op_name_list;
}; 