#include "NAND2.h"

NAND2::NAND2(const GraphicsInfo& r_GfxInfo, int r_FanOut, int id) :Gate(2, r_FanOut,id)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NAND2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins
	if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == HIGH)
	{
		m_OutputPin.setStatus(LOW);

	}
	else
	{
		m_OutputPin.setStatus(HIGH);

	}
	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void NAND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNAND2(m_GfxInfo, selected);
}

//returns status of outputpin
int NAND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NAND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void NAND2::save(ofstream& outputfile)
{
	outputfile << Nand2 <<" "<<  ID << " " << get_label() << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}