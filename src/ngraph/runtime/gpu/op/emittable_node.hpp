/*******************************************************************************
* Copyright 2017-2018 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#pragma once

#include <memory>

#include "ngraph/runtime/gpu/op/util/requires_emitter.hpp"
#include "ngraph/runtime/gpu/emitter.hpp"

namespace ngraph
{
    namespace op
    {
        namespace gpu
        {
            template <typename NODE_TYPE>
            class EmittableNode : public RequiresEmitter
            {
            public:
                EmittableNode(const std::shared_ptr<NODE_TYPE>& node)
                    : RequiresEmitter(node->description(), node->get_arguments())
                    , m_node(node)
                    , m_emitter(node.get())
                {
                }

                EmittableNode(const std::shared_ptr<NODE_TYPE>& node, const NodeVector& args)
                    : RequiresEmitter(node->description(), args)
                    , m_node(node)
                    , m_emitter(node.get())
                {
                }

                virtual std::shared_ptr<Node>
                copy_with_new_args(const NodeVector& args) const override
                {
                    auto new_node =
                        std::dynamic_pointer_cast<NODE_TYPE>(m_node->copy_with_new_args(args));
                    return std::make_shared<EmittableNode<NODE_TYPE>>(new_node, args);
                }

                virtual void emit(runtime::gpu::GPU_ExternalFunction* external_function,
                                  codegen::CodeWriter& writer,
                                  const std::vector<runtime::gpu::GPU_TensorViewWrapper>& args,
                                  const std::vector<runtime::gpu::GPU_TensorViewWrapper>& out) override
                {
                    m_emitter.emit(external_function, writer, args, out);
                }

                const std::shared_ptr<NODE_TYPE> native_node() const { return m_node; }

            protected:
                virtual void generate_adjoints(autodiff::Adjoints& adjoints,
                                               const NodeVector& deltas) override
                {
                    throw std::runtime_error(
                        "Adjoint calculation should be done prior to node replacement");
                }

                std::shared_ptr<NODE_TYPE> m_node;
                runtime::gpu::Emitter<NODE_TYPE> m_emitter;
            };
        }
    }
}
