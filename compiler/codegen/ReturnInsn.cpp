/*
 * Copyright (c) 2021, WSO2 Inc. (http://www.wso2.org) All Rights Reserved.
 *
 * WSO2 Inc. licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "ReturnInsn.h"
#include "Function.h"
#include "Operand.h"
#include "Types.h"
#include "Variable.h"

namespace nballerina {

ReturnInsn::ReturnInsn(BasicBlock &currentBB) : TerminatorInsn(Operand("", NOT_A_KIND), currentBB, "") {}

void ReturnInsn::translate(llvm::Module &, llvm::IRBuilder<> &builder) {

    const auto &funcObj = getFunctionRef();
    if (funcObj.isMainFunction()) {
        builder.CreateRetVoid();
        return;
    }
    assert(funcObj.getReturnVar().has_value());
    auto *retValueRef =
        builder.CreateLoad(funcObj.getLLVMLocalVar(funcObj.getReturnVar()->getName()), "return_val_temp");
    builder.CreateRet(retValueRef);
}

} // namespace nballerina
