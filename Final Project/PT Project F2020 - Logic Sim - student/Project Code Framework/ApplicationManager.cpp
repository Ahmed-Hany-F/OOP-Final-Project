#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddORgate2.h"
#include "Actions\ADD_XOR_GATE_3.h"
#include "Actions\AddBuff.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddConnection.h"
#include "Actions\DSGMode.h"
#include "Actions\AddGate.h"
#include "Actions\Addswitch.h"
#include "Actions\AddXNOR2.h"
#include "Actions\AddXOR2.h"
#include "Actions\change_switch.h"
#include "Actions/select_c.h"
#include "Actions/Close.h"
#include "Actions/SIMMODE.h"
#include "Actions/AddINVgate.h"
#include "Actions/AddNANDgate2.h"
#include "Actions/AddNORgate2.h"
#include "Actions/AddLEDgate.h"
#include "Actions/MOVE.h"
#include "Actions/Save.h"
#include "Actions/Deletecomp.h"
#include "Actions/load.h"
#include<iostream>
using namespace std;


ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	counter = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
	counter++;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;
		case ADD_AND_GATE_3:
			pAct = new AddANDgate3(this);
			break;
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;
		case ADD_Buff:
			pAct = new AddBuff(this);
			break;
		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(this);
			break;
		case ADD_CONNECTION:
			pAct = new AddConnection(this);
			break;
		case DSN_MODE:
			pAct = new DSGMode(this);
			break;
		case DEL:
			pAct = new Deletecomp(this);
			break;
		case LOAD:
			pAct = new load(this);
			break;
		case ADD_XOR_GATE_3:
			pAct = new ADDXORGATE3(this);
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNOR2(this);
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXOR2(this);
			break;
		case ADD_Switch:
			pAct = new Addswitch(this);
			break;
		case Change_Switch:
			pAct = new change_switch(this);
			break;
		case SELECT:
			pAct = new select_c(this);
			break;
		case ADD_Gate:
			pAct = new AddGate(this);
			break;
		case close:
			pAct = new Close(this);
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			break;

		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;

		case ADD_INV:
			pAct = new AddINVgate(this);
			break;
		case SIM_MODE:
			pAct = new SIMMODE(this);
			break;
		case ADD_LED:
			pAct = new AddLEDgate(this);
			break;
		case MOVE:
			pAct = new Move(this);
			break;
		case SAVE:
			pAct = new Save(this);
			break;
		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(OutputInterface);

}
int ApplicationManager::get_compcount()
{
	return CompCount;
}

Component**& ApplicationManager::get_CompList()
{
	Component** x = this->CompList;
	return x;
}
////////////////////////////////////////////////////////////////////


Component* ApplicationManager::ComponentRegion(int x,int y) { // this function loop on complist
	for (int i = 0; i < CompCount; i++) {                     // and return component that point (x,y)
		Component* p = CompList[i]->ComponentRegion(x, y);    // included in its region or return NULL
		if (p != NULL){
			return p;
		}
		Component* com = CompList[i];    // included in its region or return NULL
		Connection* conn = dynamic_cast<Connection*>(com);
		if (conn != NULL)
		{
			GraphicsInfo g_conn = conn->get_GraphicsInfo();
			if ((x > g_conn.x1 && x < ((g_conn.x1 + g_conn.x2) / 2)) && ((y < g_conn.y1 + 2) && (y > g_conn.y1 - 2)))
			{
				return conn;
			}
			else if ((x < g_conn.x2 && x >((g_conn.x1 + g_conn.x2) / 2)) && ((y < g_conn.y2 + 2) && (y > g_conn.y2 - 2)))
			{
				return conn;
			}
			if (g_conn.y1 > g_conn.y2)
			{
				if (((x < ((g_conn.x1 + g_conn.x2) / 2) + 2) && (x > ((g_conn.x1 + g_conn.x2) / 2) - 2)) && (y < g_conn.y1 && y > g_conn.y2))
				{
					return conn;
				}
			}
			else if (g_conn.y1 < g_conn.y2)
			{
				if (((x < ((g_conn.x1 + g_conn.x2) / 2) + 2) && (x > ((g_conn.x1 + g_conn.x2) / 2) - 2)) && (y > g_conn.y1 && y < g_conn.y2))
				{
					return conn;
				}
			}
			else if (g_conn.y1 == g_conn.y2)
			{
				if ((x < g_conn.x2 && x > g_conn.x1) && ((y < g_conn.y2 + 2) && (y > g_conn.y2 - 2)))
				{
					return conn;
				}
			}
		}
	}
	return NULL;
	}

////////////////////////////////////////////////////////////////////

Component* ApplicationManager::componentreturin(int i) {
	return 	CompList[i];

}
/////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}
void ApplicationManager::save(ofstream& outputfile) // function Save in application manager
{                                                // Loop on complist and calls function save in each component
	int count = 0;
	for (int i = 0; i < CompCount; i++)
	{
		Gate* gate = dynamic_cast<Gate*>(CompList[i]);
		switch_key* Switch = dynamic_cast<switch_key*>(CompList[i]);
		LED* led = dynamic_cast<LED*>(CompList[i]);      // 1st loop to determine no. of components Except connections
		if (led != NULL|| gate!=NULL|| Switch!=NULL)
		{
			count++;
		}
	}
	outputfile << count << endl;
	for (int i = 0; i < CompCount; i++) // 2nd loop to save gates ,leds and switchs first
	{
		Gate* gate = dynamic_cast<Gate*>(CompList[i]);
		if (gate != NULL)
		{
			CompList[i]->save(outputfile);
		}
		switch_key* Switch = dynamic_cast<switch_key*>(CompList[i]);
		if (Switch != NULL)
		{
			CompList[i]->save(outputfile);
		}
		LED* led = dynamic_cast<LED*>(CompList[i]);
		if (led != NULL)
		{
			CompList[i]->save(outputfile);
		}
	}
	outputfile << connection << endl;
	for (int i = 0; i < CompCount; i++) // 3rd loop to save connections 
	{
		Connection* connection1 = dynamic_cast<Connection*>(CompList[i]);
		if (connection1 != NULL)
		{
			CompList[i]->save(outputfile);
		}
	}
	outputfile << -1<<endl;
}
/////////////////////////////
/////////////////////////////
//Delete
Component* ApplicationManager::Check(int i)
{
	if (CompList[i]->get_selected() == true)
	{
		return CompList[i];
	}
	else
	{
		return NULL;
	}
}
void ApplicationManager::Delete(int i)
{
	Component* comp = CompList[i];
	CompList[i] = CompList[CompCount - 1];
	CompList[CompCount - 1] = comp;
	CompList[CompCount - 1] = NULL;
	delete comp;
	CompCount--;
	OutputInterface->ClearDrawingArea();
	UpdateInterface();

}
Connection* ApplicationManager::Check_conn(int i)
{
	Connection* conn = dynamic_cast<Connection*>(CompList[i]);
	if (conn != NULL)
	{
		return conn;
	}
	else
	{
		return NULL;
	}
}
////////////////////////////////
//load connection
Component* ApplicationManager::load_connection(int id1)
{
	Component* p;
	for (int i = 0; i < CompCount; i++)
	{
		p = CompList[i];
		if (p->get_ID() == id1)
		{
			return p;
		}

	}
	return NULL;
}
Connection* ApplicationManager::get_connections(int id1,int &n)
{
	for (int i = n; i < CompCount; i++)
	{
		Connection* connections = dynamic_cast<Connection*>(CompList[i]);
		if (connections != NULL)
		{

			if (connections->get_ID1() == id1 || connections->get_ID2() == id1)
			{
				n = i+1;
				return connections;
			}
		}
	}
	return NULL;
}
