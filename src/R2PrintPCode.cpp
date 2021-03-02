// SPDX-License-Identifier: LGPL-3.0-or-later

#include "R2PrintPCode.h"

#include <varnode.hh>
#include <architecture.hh>

// Constructing this registers the capability
R2PrintPCodeCapability R2PrintPCodeCapability::inst;

R2PrintPCodeCapability::R2PrintPCodeCapability()
{
	name = "r2-pcode-language";
	isdefault = false;
}

PrintLanguage *R2PrintPCodeCapability::buildLanguage(Architecture *glb)
{
	return new R2PrintPCode(glb, name);
}

R2PrintPCode::R2PrintPCode(Architecture *g, const string &nm)
	: PrintPCode(g, nm)
{
}

void R2PrintPCode::pushUnnamedLocation(const Address &addr, const Varnode *vn, const PcodeOp *op)
{
	// print (*(type *)0x0000...) instead of ram00000...
	AddrSpace *space = addr.getSpace();
	if(space->getType() == IPTR_PROCESSOR)
	{
		pushOp(&dereference, op);
		auto type = glb->types->getTypePointer(space->getAddrSize(), vn->getType(), space->getWordSize());
		pushConstant(addr.getOffset(), type, vn, op);
	}
	else
	{
		PrintPCode::pushUnnamedLocation(addr,vn, op);
	}
}