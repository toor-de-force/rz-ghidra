#include "printpcode.hh"

class RizinPrintPCode : public PrintPCode
{
	protected:
		void pushUnnamedLocation(const Address &addr, const Varnode *vn,const PcodeOp *op) override;

	public:
		explicit RizinPrintPCode(Architecture *g, const string &nm = "rizin-pcode-language");

};

class RizinPrintPCodeCapability : public PrintLanguageCapability
{
	private:
		static RizinPrintPCodeCapability inst;
		RizinPrintPCodeCapability();

	public:
		PrintLanguage *buildLanguage(Architecture *glb) override;
};
