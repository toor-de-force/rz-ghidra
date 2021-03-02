// SPDX-License-Identifier: LGPL-3.0-or-later

#include "RizinPrintPCode.h"

#include <varnode.hh>
#include <architecture.hh>

// Constructing this registers the capability

RizinPrintPCodeCapability RizinPrintPCodeCapability::inst;

RizinPrintPCodeCapability::RizinPrintPCodeCapability()
{
	name = "rizin-pcode-language";
	isdefault = false;
}

PrintLanguage *RizinPrintPCodeCapability::buildLanguage(Architecture *glb)
{
	return new RizinPrintPCode(glb, name);
}

RizinPrintPCode::RizinPrintPCode(Architecture *g, const string &nm)
	: PrintPCode(g, nm)
{
}

void RizinPrintPCode::pushUnnamedLocation(const Address &addr, const Varnode *vn, const PcodeOp *op)
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