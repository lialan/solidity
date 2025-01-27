/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Compiler that transforms Yul Objects to LLVMIR text representation.
 */

#include <libyul/backends/llvmir/LLVMIRObjectCompiler.h>

#include <libyul/backends/llvmir/LLVMIRCodeTransform.h>

#include <libyul/Object.h>
#include <libyul/Exceptions.h>

using namespace yul;
using namespace std;

string LLVMIRObjectCompiler::compile(Object& _object, Dialect const& _dialect)
{
	LLVMIRObjectCompiler compiler(_dialect);
	return compiler.run(_object);
}

string LLVMIRObjectCompiler::run(Object& _object)
{
	string ret;

	for (auto& subNode: _object.subObjects)
		if (Object* subObject = dynamic_cast<Object*>(subNode.get()))
			ret += compile(*subObject, m_dialect);
		else
			yulAssert(false, "Data is not yet supported for LLVMIR.");

	yulAssert(_object.analysisInfo, "No analysis info.");
	yulAssert(_object.code, "No code.");
	ret += LLVMIRCodeTransform::run(m_dialect, *_object.code);

	return ret;
}
