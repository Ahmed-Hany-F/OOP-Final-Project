#include "Close.h"
#include "..\ApplicationManager.h"
Close::Close(ApplicationManager* pApp) :Action(pApp)
{
}

Close::~Close(void)
{
}

void Close::ReadActionParameters()
{
	//Get a Pointer to the Output Interfaces
	//pout = pManager->GetOutput();


}

void Close::Execute()
{
	//ReadActionParameters();
	Output* pout;
	pout = pManager->GetOutput();
	pout->CleartoolbarArea1();
	pout->CreateDesignToolBar();
}

void Close::Undo()
{}

void Close::Redo()
{}

