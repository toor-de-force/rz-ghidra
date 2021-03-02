// SPDX-License-Identifier: LGPL-3.0-or-later

#include "printpcode.hh"

class R2PrintPCode : public PrintPCode
{
	protected:
		void pushUnnamedLocation(const Address &addr, const Varnode *vn,const PcodeOp *op) override;

	public:
		explicit R2PrintPCode(Architecture *g, const string &nm = "pcode-language");

};

class R2PrintPCodeCapability : public PrintLanguageCapability
{
	private:
		static R2PrintPCodeCapability inst;
		R2PrintPCodeCapability();

	public:
		PrintLanguage *buildLanguage(Architecture *glb) override;
};
