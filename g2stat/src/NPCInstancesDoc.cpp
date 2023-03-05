/*//SJCLib
#include <SJCLib.h>
//Local
#include "CreateDocs.h"
#include "Definitions.h"
#include "globals.h"
#include "HTML.h"
//Namespaces
using namespace SJCLib;

bool CreateNPCInstanceDoc(CString outputPath, SNPCInstanceInfo &refInfo, CCompilePreprocessor &refCompilePreproc)
{
	uint8 chapter;
	CNPC *pNPC;
	CFileOutputStream file;

	pNPC = refInfo.pNPC;
	
	SInstanceInfo &refInstanceInfo = *refCompilePreproc.GetInstanceInfo(pNPC->GetInstanceName());
	
	if(!file.Open(outputPath + "\\instances\\" + pNPC->GetInstanceName() + ".htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\instances\\" + pNPC->GetInstanceName() + ".htm'");
	
	WriteHTMLHead(pNPC->GetInstanceName(), file, "../");
	
	file << "<h1>" << pNPC->GetInstanceName() << "</h1>";
	
	/*
	--Print standard info
	* /
	file << "<table>";
	
	//Print the class/prototype
	file << "<tr><td>Class/Prototype:</td><td><a href=\"../";
	if(refCompilePreproc.IsPrototypeDefined(*refInfo.pInstance->pClassName))
	{
		file << "prototypes";
	}
	else
	{
		file << "classes";
	}
	file << "/" << *refInfo.pInstance->pClassName << ".htm\">" << *refInfo.pInstance->pClassName << "</a></td></tr>";
	//Print defined in
	file << "<tr><td>Defined in:</td><td>" << *refInfo.pInstance->pFileName << ":" << refInfo.pInstance->lineNumber << "</td></tr>";
	//Print the number of references
	file << "<tr><td>Referenced:</td><td" << (refInstanceInfo.nReferences == 0 ? " class=\"warning\")" : "") << ">" << refInstanceInfo.nReferences << "</td></tr>";
	//Name
	file << "<tr><td>Name:</td><td>" << refInfo.pNPC->GetName() << "</td></tr>";
	//Guild
	file << "<tr><td>Guild:</td><td>" << "" << "</td></tr>";
	//Level
	file << "<tr><td>Level:</td><td>" << refInfo.pNPC->GetLevel() << "</td></tr>";
	//Strength
	file << "<tr><td>Strength:</td><td>" << refInfo.pNPC->GetAttribute(ATR_STRENGTH) << "</td></tr>";
	//Dexterity
	file << "<tr><td>Dexterity:</td><td>" << refInfo.pNPC->GetAttribute(ATR_DEXTERITY) << "</td></tr>";
	//Max Life
	file << "<tr><td>Life:</td><td>" << refInfo.pNPC->GetAttribute(ATR_HITPOINTS_MAX) << "</td></tr>";
	//Max mana
	file << "<tr><td>Mana:</td><td>" << refInfo.pNPC->GetAttribute(ATR_MANA_MAX) << "</td></tr>";
	//One-handed weapons skill
	file << "<tr><td>One-handed weapons skill:</td><td>" << refInfo.pNPC->GetHitChance(NPC_TALENT_1H) << "</td></tr>";
	//Two-handed weapons skill
	file << "<tr><td>Two-handed weapons skill:</td><td>" << refInfo.pNPC->GetHitChance(NPC_TALENT_2H) << "</td></tr>";
	//Bow skill
	file << "<tr><td>Bow skill:</td><td>" << refInfo.pNPC->GetHitChance(NPC_TALENT_BOW) << "</td></tr>";
	//Crossbow skill
	file << "<tr><td>Crossbow skill:</td><td>" << refInfo.pNPC->GetHitChance(NPC_TALENT_CROSSBOW) << "</td></tr>";
	//Melee weapon
	file << "<tr><td>Melee weapon:</td><td>";
	PrintLink(refInfo.pNPC->GetMeleeWeapon(), file, "../");
	file << "</td></tr>";
	//Ranged weapon
	file << "<tr><td>Ranged weapon:</td><td>";
	PrintLink(refInfo.pNPC->GetRangedWeapon(), file, "../");
	file << "</td></tr>";
	//Armor
	file << "<tr><td>Armor:</td><td>";
	PrintLink(refInfo.pNPC->GetArmor(), file, "../");
	file << "</td></tr>";
	//Inventory
	file << "<tr><td>Inventory:</td><td>";
	foreach(it, refInfo.pNPC->GetInventory())
	{
		PrintLink(it.GetValue(), file, "../");
		file << "<br />";
	}
	file << "</td></tr>";

	file << "</table>";
	
	/*
	--Print trader goods
	* /
	auto &refMerchantIt = g_merchantInfo.Find(pNPC->GetInstanceName());
	if(refMerchantIt.IsValid())
	{
		file << "<h2>Trading goods</h2>";
		file << "<table>";
		file << "<tr><th>Chapter</th><th>Goods</th></tr>";
		for(chapter = 1; chapter <= 6; chapter++)
		{
			file << "<tr>";

			file << "<td>" << chapter << "</td>";
			
			file << "<td>";
			foreach(it, refMerchantIt.GetValue().inventory[chapter-1])
			{
				file << it.GetValue()->GetMultiplicity() << "x " << it.GetValue()->GetInstanceName() << "<br />";
			}
			file << "</td>";

			file << "</tr>";
		}
		file << "</table>";
	}
	
	WriteHTMLFoot(file);
	
	return true;
}

bool CreateNPCInstancesDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc)
{
	SInstanceInfo *pInstanceInfo;
	CFileOutputStream file;
	
	if(!file.Open(outputPath + "\\npcs.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\npcs.htm'");
	
	WriteHTMLHead("NPCs", file);
	WriteHTMLTableHead(file, 5, "Name", "Instance name", "Class/Prototype", "Defined in", "Referenced");
	
	foreach(it, g_npcInstances)
	{
		if(!CreateNPCInstanceDoc(outputPath, it.GetValue(), refCompilePreproc))
			ERRORMSG("Couldn't create instances documentation for instance '" + it.GetValue().pNPC->GetInstanceName() + "'.");

		pInstanceInfo = refCompilePreproc.GetInstanceInfo(it.GetValue().pNPC->GetInstanceName());
		
		//Create entry...
		file << "<tr>";

		//Name
		file << "<td>" << it.GetValue().pNPC->GetName() << "</td>";
		//Instance name
		file << "<td><a href=\"instances/" << it.GetValue().pNPC->GetInstanceName() << ".htm\">" << it.GetValue().pNPC->GetInstanceName() << "</a></td>";
		//ClassnamePrototype
		file << "<td><a href=\"";
		if(it.GetValue().pInstance->pPrototypeName)
		{
			file << "prototypes/" << *it.GetValue().pInstance->pPrototypeName << ".htm\">" << *it.GetValue().pInstance->pPrototypeName << "</a>";
		}
		else
		{
			file << "classes/" << *it.GetValue().pInstance->pClassName << ".htm\">" << *it.GetValue().pInstance->pClassName << "</a>";
		}
		file << "</td>";
		//Defined in
		file << "<td>" << *it.GetValue().pInstance->pFileName << ':' << it.GetValue().pInstance->lineNumber << "</td>";
		//Referenced
		file << "<td" << (pInstanceInfo->nReferences == 0 ? " class=\"warning\")" : "") << ">" << pInstanceInfo->nReferences << "</td>";
		
		file << "</tr>";
	}
	
	WriteHTMLTableFoot(file);
	WriteHTMLFoot(file);
	
	return true;
}*/