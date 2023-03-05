//Class Header
#include "CDaedalusVM.h"
//Global
#include <iostream>
//Local
#include "CGame.h"
#include "CItem.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Private Functions
void CDaedalusVM::CallConstructor(AAccessable *pInstance, uint32 instanceSymbolIndex)
{
	CDaedalusVM vm(this->pProgram);
	
	SSymbol &refSymbol = this->pProgram->GetSymbol(instanceSymbolIndex);
	
	refSymbol.pCurrentInstance = pInstance;
	vm.pCurrentInstance = pInstance;
	vm.Run(refSymbol.data.programOffset); //Call the constructor
}

void CDaedalusVM::CallExtern(uint32 callOffset, uint32 symbolIndex)
{
	switch(callOffset)
	{
	case EXTERNAL_AI_OUTPUT:
		{
			/*
			FUNC VOID AI_Output (VAR C_NPC self, VAR C_NPC target, VAR STRING outputName);

			Play the cutscene with name 'outputName'. 'self' says it to 'target'
			*/

			this->PopString();
			this->dataStack.Pop();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_OUTPUTSVM:
		{
			/*
			FUNC VOID AI_OutputSVM(VAR C_NPC self, VAR C_NPC target, VAR STRING svmname);

			Outputbefehl um Svms abzuspielen
			*/

			this->PopString();
			this->dataStack.Pop();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_OUTPUTSVM_OVERLAY:
		{
			/*
			FUNC VOID	AI_OutputSVM_Overlay		(VAR C_NPC self, VAR C_NPC target, VAR STRING svmname) {};
// wie AI_OutputSVM, wartet jedoch NICHT mit der Ausführung des nächsten AI_...-Befehls, bis
// das SVM zuende gespielt wird. (Für Kommentare kurz vor und während dem Kampf!)
			*/
			this->PopString();
			this->dataStack.Pop();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_PLAYANI:
		{
			/*
			FUNC VOID 	AI_PlayAni 				(VAR C_NPC n0, VAR STRING s0 ) { };
			// Npc-Instanz spielt die angegebene Animation ab
			*/

			this->PopString();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_PRINTSCREEN:
		{
			/*
			NO DOC!
			
			func void AI_PrintScreen(var string message, var int ?1, var int ?2, var string font, var int ?3);
			*/

			this->PopInt();
			this->PopString();
			this->PopInt();
			this->PopInt();
			this->PopString();
		}
		break;
	case EXTERNAL_AI_REMOVEWEAPON:
		{
			/*
			FUNC VOID 	AI_RemoveWeapon 			(VAR C_NPC n0 ) { };
// Gezogene Waffe wird weggesteckt
			*/

			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_STANDUP:
		{
			/*
			FUNC VOID	AI_StandUp				(VAR C_NPC self) {};
			// - Ist der Nsc in einem Animatinsstate, wird die passende Rücktransition abgespielt.
			// - Benutzt der NSC gerade ein MOBSI, poppt er ins stehen.
			*/
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_STOPFX:
		{
			/*
			NO DOC!

			func void AI_StopFX(C_NPC, string)
			*/

			this->PopString();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_STOPPROCESSINFOS:
		{
			/*
			func void	AI_StopProcessInfos			(var C_NPC npc)
// ???
			*/
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_TELEPORT:
		{
			/*
			FUNC VOID AI_Teleport(VAR C_NPC self, VAR STRING waypoint);
			// teleportiert den NSC zur angegebenene Location
			*/

			this->PopString();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_USEITEMTOSTATE:
		{
			/*
			FUNC VOID 	AI_UseItemToState		(VAR C_NPC self, VAR INT itemInstance, VAR INT state) 	{ };
// Item benutzen bis zum angegebenen State
			*/
			this->PopInt();
			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_AI_WAIT:
		{
			/*
			FUNC VOID 	AI_Wait 			( VAR C_NPC n0, VAR float n1 ) { };
// Character wird für n1 Sekunden in einen Wait-Zustand versetzt,
// d.h. er tut nichts, aber Treffer etc.(passive Wahrnehmung) werden registriert
			*/
			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_CONCATSTRINGS:
		{
			this->stringExternalResult = *this->PopString() + *this->PopString();
			this->PushVar(&this->stringExternalResult);
		}
		break;
	case EXTERNAL_CREATEINVITEM:
		{
			uint32 itemInstanceSymbolIndex;
			CItem *pItem;
			CNPC *pNpc;
			
			/*
			FUNC VOID CreateInvItem (VAR C_NPC npc, VAR INT itemInstanceSymbolIndex);
			
			gibt der angegebenen Instanz (self oder other) ein Item ins Inventory
			*/

			itemInstanceSymbolIndex = this->PopInt();

			SSymbol &refSymbol = this->pProgram->GetSymbol((uint32)this->dataStack.Pop());
			SSymbol &refItemSymbol = this->pProgram->GetSymbol(itemInstanceSymbolIndex);

			pItem = new CItem(refItemSymbol.name);
			pNpc = (CNPC *)refSymbol.pCurrentInstance;
			
			pNpc->AddItem(pItem);
		}
		break;
	case EXTERNAL_CREATEINVITEMS:
		{
			int32 count;
			uint32 itemSymbolIndex;
			CItem *pItem;
			CNPC *pNpc;

			/*
			FUNC VOID CreateInvItems (VAR C_NPC npc, VAR INT itemInstanceSymbolIndex, VAR INT count);

			instanciates an item of 'itemInstanceSymbolIndex' with multiplicity 'count' and puts it into the inventory of 'npc'
			*/
			
			count = this->PopInt();
			itemSymbolIndex = this->PopInt();
			
			SSymbol &refSymbol = this->pProgram->GetSymbol((uint32)this->dataStack.Pop());
			SSymbol &refItemSymbol = this->pProgram->GetSymbol(itemSymbolIndex);

			pItem = new CItem(refItemSymbol.name);
			pItem->SetMultiplicity(count);
			pNpc = (CNPC *)refSymbol.pCurrentInstance;
			
			pNpc->AddItem(pItem);
		}
		break;
	case EXTERNAL_DOC_CREATE:
		{
			/*
			func int	Doc_Create			() {};

								// Erzeugt ein Dokument.
								//
								//	[result]	- Handle auf das Dokument (-1 = konnte nicht erzeugt werden)
			*/
			
			this->PushInt(-1);
		}
		break;
	case EXTERNAL_DOC_CREATEMAP:
		{
			/*
			func int	Doc_CreateMap		() {};

								// Erzeugt ein Dokument (Karte).
								//
								//	[result]	- Handle auf das Dokument (-1 = konnte nicht erzeugt werden)
			*/

			this->PushInt(-1);
		}
		break;
	case EXTERNAL_DOC_PRINTLINE:
		{
			/*
			func void	Doc_PrintLine		(var int Document, var int Page, var string Text) {};

								// Setzt den Text einer Seite. Der Text wird _nicht_ umgebrochen.
								//
								//	Document	- Handle auf das Dokument
								//	Page		- Index der Seite (beginnt mit 0)
								//	Text		- Textzeile
			*/

			this->PopString();
			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_DOC_PRINTLINES:
		{
			/*
			func void	Doc_PrintLines		(var int Document, var int Page, var string Text) {};

								// Setzt den Text einer Seite. Der Text wird umgebrochen falls notwendig.
								//
								//	Document	- Handle auf das Dokument
								//	Page		- Index der Seite (beginnt mit 0)
								//	Text		- Textzeilen
			*/
			this->PopString();
			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_DOC_SETFONT:
		{
			/*
			func void	Doc_SetFont			(var int Document, var int Page, var string Font) {};

								// Setzt den Font einer/aller Seite(n).
								//
								//	Document	- Handle auf das Dokument
								//	Page		- Index der Seite (beginnt mit 0, -1 = alle)
								//	Font		- Dateiname der Font-Textur (ohne Pfad - z.B. 'Font_Default.tga')
			*/
			this->PopString();
			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_DOC_SETLEVEL:
		{
			/*
			func void	Doc_SetLevel		(var int Document, var string Level) {};

								// Setzt das Level-ZEN zur Anzeige der Spieler-Position (Karten).
								//
								// (als Grenze gilt die BBox des statischen Level-Meshes)
								//	Document	- Handle auf das Dokument
								//	Level		- Dateiname des Level-ZENs (mit Pfad ab WORLDS - z.B. 'NewWorld\NewWorld.zen')
			*/
			this->PopString();
			this->PopInt();
		}
		break;
	case EXTERNAL_DOC_SETLEVELCOORDS:
		{
			/*
			func void	Doc_SetLevelCoords	(var int Document, var int Left, var int Top, var int Right, var int Bottom) {};

								// Setzt die Grenzen des Level-Bereichs, der durch die Textur abgedeckt wird (Karten).
								//
								// (als Grenzen werden _absolute_ Level-Koordinaten angegeben - z.B.: '..., -28000, 50500, 95500, -42500')
								//	Document	- Handle auf das Dokument
								//	Left		- linke Grenze
								//	Top			- obere Grenze
								//	Right		- rechte Grenze
								//	Bottom		- untere Grenze
			*/
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_DOC_SETMARGINS:
		{
			/*
			func void	Doc_SetMargins		(var int Document, var int Page, var int Left, var int Top, var int Right, var int Bottom, var int Pixels) {};

								// Setzt den jeweiligen Rand einer/aller Seite(n) (vom Rand der mit Doc_SetPage gesetzten Textur aus gesehen).
								//
								//	Document	- Handle auf das Dokument
								//	Page		- Index der Seite (beginnt mit 0, -1 = alle)
								//	Left		- linker Rand
								//	Top			- oberer Rand
								//	Right		- rechter Rand
								//	Bottom		- unterer Rand
								//	Pixel		- Flag ob Angaben in Pixeln (Bildschirm) oder virtuellen Koordinaten (0-8192)
			*/
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_DOC_SETPAGE:
		{
			/*
			func void	Doc_SetPage			(var int Document, var int Page, var string Texture, var int Scale) {};

								// Setzt die Hintergrund-Textur der Seite eines Dokuments.
								//
								//	Document	- Handle auf das Dokument
								//	Page		- Index der Seite (beginnt mit 0, -1 = alle)
								//	Scale		- Flag ob Textur gestreckt werden soll
			*/

			this->PopInt();
			this->PopString();
			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_DOC_SETPAGES:
		{
			/*
			func void	Doc_SetPages		(var int Document, var int Count) {};

								// Setzt die Anzahl der Seiten eines Dokuments.
								//
								//	Document	- Handle auf das Dokument
								//	Count		- Anzahl der Seiten
			*/

			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_DOC_SHOW:
		{
			/*
			func void	Doc_Show			(var int Document) {};

								// Zeigt das Dokument auf dem Bildschirm an.
								//
								//	Document	- Handle auf das Dokument
			*/
			this->PopInt();
		}
		break;
	case EXTERNAL_EQUIPITEM:
		{
			uint32 itemSymbolIndex;
			CNPC *pNpc;
			CItem *pItem;

			/*
			FUNC VOID EquipItem (VAR C_NPC npc, VAR INT itemInstanceSymbolIndex);
			instanciates an item of 'itemInstanceSymbolIndex' and gives it directly to the "belt" of 'npc'
			*/
			
			itemSymbolIndex = this->PopInt();

			SSymbol &refSymbol = this->pProgram->GetSymbol((uint32)this->dataStack.Pop());
			SSymbol &refItemSymbol = this->pProgram->GetSymbol(itemSymbolIndex);
			
			pItem = new CItem(refItemSymbol.name);
			pNpc = (CNPC *)refSymbol.pCurrentInstance;

			pNpc->AddItem(pItem);
			pNpc->EquipItem(pItem);
		}
		break;
	case EXTERNAL_HLP_GETINSTANCEID:
		{
			CNPC *pNPC;
			
			/*
			G2MDK Scripts:
			liefert die interne ID ( nicht Var aus der Instanz) zurück, um z.B. other mit self vergleichen zu können ( integer Vergleich)

			SJC:
			FUNC INT Hlp_GetInstanceID (VAR C_NPC npc);

			Returns an internal ID of the object in npc (there might be more than one object of the same "daedalus instance").
			If npc is not existant then returns -1.
			*/

			SSymbol &refNPCSymbol = this->pProgram->GetSymbol((uint32)this->dataStack.Pop());
			
			pNPC = (CNPC *)refNPCSymbol.pCurrentInstance;
			if(pNPC)
			{
				this->PushInt(pNPC->GetInternalId());
			}
			else
			{
				this->PushInt(-1);
			}
		}
		break;
	case EXTERNAL_HLP_GETNPC:
		{
			/*
			FUNC C_NPC Hlp_GetNpc (VAR INT instanceName);
			
			Ermittle einen NSC über den Instanznamen. Dieser kann einer Variablen zugewiesen werden und ist somit gezielt verfügbar

			Important by NicoDE:
			Externals die eine instance zurückgeben, schreiben das Ergebnis in ein globales Symbol (ÿINSTANCE_HELP).
			*/
			
			SSymbol &refParam1Symbol = this->pProgram->GetSymbol(this->PopInt());
			SSymbol &refRetSymbol = this->pProgram->GetSymbol(this->instance_helpSymbolIndex);
			
			refRetSymbol.pCurrentInstance = refParam1Symbol.pCurrentInstance;

			this->dataStack.Push(this->instance_helpSymbolIndex);
		}
		break;
	case EXTERNAL_HLP_ISVALIDNPC:
		{
			//!!!!!!!!!!!!!!!!!!!!NOT IMPLEMENTED CORRECTLY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			/*
			FUNC INT Hlp_IsValidNpc (VAR C_NPC self);
			
			Prüfe ob NSC-Instanz gültig und initialisiert ist. True/False
			*/

			this->dataStack.Pop();
			this->PushInt(0);
		}
		break;
	case EXTERNAL_HLP_RANDOM:
		{
			/*
			FUNC INT Hlp_Random (VAR INT max);

			returns an random integer in range 0 to max-1
			*/
			
			this->PushInt(Random(0, this->PopInt()));
		}
		break;
	case EXTERNAL_INTRODUCECHAPTER:
		{
			/*
			func void	IntroduceChapter	(var string Titel, var string Untertitel, var string Texture, var string Sound, var int WaitTime) {};

								// Zeigt den Kapitelwechsel-Bildschirm an.
								//
								//	Titel		- Text des Titels
								//	Untertitel	- text des Untertitels
								//	Texture		- Dateiname der Hintergrundtextur
								//	Sound		- Dateiname des abgespielten Sounds
								//	WaitTime	- Anzahl in Millisekunden, die der Bildschirm angezeigt wird
			*/

			this->PopInt();
			this->PopString();
			this->PopString();
			this->PopString();
			this->PopString();
		}
		break;
	case EXTERNAL_INTTOSTRING:
		{
			this->stringExternalResult = CString(this->PopInt());
			this->PushVar(&this->stringExternalResult);
		}
		break;
	case EXTERNAL_LOG_ADDENTRY:
		{
			/*
			func void Log_AddEntry( VAR STRING topic, VAR STRING entry )
//	Der Befehl fügt dem Topics topic ein neues Entrz namens entry hinzu. Wie auch bei der Erzeugung von Topics dient hier der
//	Name sowohl zur Identifikation als auch zur Anzeige und muss somit eindeutig sein. Doppelte Einträge werden auch hier ignoriert.
//
//	Parameter
//	topic       Diejenige Zeichenkette, die bei der Erstellung des Topics per Log_CreateTopic() angegeben wurde.
//	entry		Eine eindeutige Zeichenkette, die sowohl zur Identifikation als auch zur Anzeige des Eintrags verwendet wird.
			*/
			this->PopString();
			this->PopString();
		}
		break;
	case EXTERNAL_LOG_CREATETOPIC:
		{
			/*
			func void Log_CreateTopic( VAR STRING name, VAR INT section )
//	Der Befehl fügt unter der Sektion 'section' ein neues Topic mit Namen 'name' ein.
//	Sollte bereits ein Topic dieses Names in irgendeiner Sektion existieren, wird das Topic nicht hinzugefügt.
//
//	Parameter:
//	- name      Eine eindeutige Zeichenkette, die sowohl zur Identifikation als auch zur Anzeige des Topics verwendet wird.
//	- section	Eine, in der Constants.d definierte Konstante, die besagt, in welcher Sektion das Topic angezeigt werden soll.
//				Die Konstante kann folgende Werte annehmen:
//					- LOG_MISSION
//					- LOG_NOTE
			*/
			this->PopInt();
			this->PopString();
		}
		break;
	case EXTERNAL_LOG_SETTOPICSTATUS:
		{
			/*
			func void Log_SetTopicStatus( VAR STRING name, VAR INT status )
//	Der Befehl ändert den Status des Topics 'name' in 'status'.
//	Er sollte nur für Topics verwendet werden, die für die Sektion LOG_MISSION erzeugt wurden.
//
//	Parameter:
//	- name      Diejenige Zeichenkette, die bei der Erstellung des Topics per Log_CreateTopic() angegeben wurde.
//	- status	Eine, in der Constants.d definierte Konstante, die besagt, unter welchem Status die Mission dargestellt werden soll.
//				Folgende Werte sind möglich:
//					- LOG_RUNNING
//					- LOG_SUCCESS
//					- LOG_FAILED
//					- LOG_OBSOLETE
			*/
			this->PopInt();
			this->PopString();
		}
		break;
	case EXTERNAL_MDL_APPLYOVERLAYMDS:
		{
			/*
			FUNC VOID Mdl_ApplyOverlayMds (var C_NPC npc, VAR STRING s1);
			
			mit diesem Befehl werden Animationen auf einem höheren Layer gestartet
			(z.B. hat der Zombie ein Overlay über die normalen Human-Animationen)
			*/
			this->PopString();
			this->PopInt();
		}
		break;
	case EXTERNAL_MDL_APPLYOVERLAYMDSTIMED:
		{
			/*
			func VOID	Mdl_ApplyOverlayMDSTimed	(VAR C_NPC self, VAR STRING overlayname, VAR FLOAT timeTicks );
// Overlay-MDS wird gestartet und automatisch nach der angegebenen Zeit abgeschaltet
			*/
			
			this->PopInt();
			this->PopString();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_MDL_SETMODELFATNESS:
		{
			/*
			func VOID Mdl_SetModelFatness (var C_NPC self, VAR FLOAT fatness);
			
			Setzt Model-Z-Skalierung
			*/
			
			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_MDL_SETMODELSCALE:
		{
			/*
			FUNC VOID Mdl_SetModelScale (VAR C_NPC self, VAR FLOAT x, VAR FLOAT y, VAR FLOAT z);
			
			zum skalieren des Meshes (Breite,Höhe,Tiefe) 1 = 100%, also Normalgröße!
			*/
			
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_MDL_SETVISUAL:
		{
			/*
			
			NO DOC!
			
			func void Mdl_SetVisual(npc, string);
			*/
			
			this->PopString();
			this->PopInt();
		}
		break;
	case EXTERNAL_MDL_SETVISUALBODY:
		{
			int32 armorSymbolIndex, npcSymbolIndex;
			CItem *pArmor;
			CNPC *pNPC;
			
			/*
			NO DOC!
			
			func void Mdl_SetVisualBody(npc, string, int, int, string, int, int, int armorInstance);

			armorInstance - Instance of armor gets inserted in the inventory and gets equipped
			*/
			
			armorSymbolIndex = this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopString();
			this->PopInt();
			this->PopInt();
			this->PopString();
			npcSymbolIndex = (int32)this->dataStack.Pop();

			if(armorSymbolIndex > 0) //-1 is NO_ARMOR constant in Daedalus, 0 seems to be invalid too-.-
			{
				SSymbol &refNPCSymbol = this->pProgram->GetSymbol(npcSymbolIndex);
				SSymbol &refArmorSymbol = this->pProgram->GetSymbol(armorSymbolIndex);
				
				pArmor = new CItem(refArmorSymbol.name);
				pNPC = (CNPC *)refNPCSymbol.pCurrentInstance;
				
				pNPC->AddItem(pArmor);
				pNPC->EquipArmor(pArmor);
			}
		}
		break;
	case EXTERNAL_NPC_CHANGEATTRIBUTE:
		{
			int32 value;
			int32 attribute;
			CNPC *pNPC;
			
			/*
			FUNC VOID Npc_ChangeAttribute(var C_NPC self, VAR INT attribute, VAR INT value);
			// ändert den Wert des Attributs (attribute) um (value) Einheiten.
			*/
			value = this->PopInt();
			attribute = this->PopInt();

			SSymbol &refNPCSymbol = this->pProgram->GetSymbol((uint32)this->dataStack.Pop());
			
			pNPC = (CNPC *)refNPCSymbol.pCurrentInstance;
			pNPC->SetAttribute(attribute, pNPC->GetAttribute(attribute) + value);
		}
		break;
	case EXTERNAL_NPC_EXCHANGEROUTINE:
		{
			/*
			FUNC VOID Npc_ExchangeRoutine(VAR C_NPC self, VAR STRING routineName);
			
			Tausche meherere Tagesabläufe aus
			*/
			this->PopString();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_NPC_GETBODYSTATE:
		{
			/*
			FUNC INT  	Npc_GetBodyState			(VAR C_NPC self)					{ return 0; };
// Ermittle BodyState ( Liefert BS_-Konstanten )
// !!! VORSICHT !!!: Diese Funktion gibt den Bodystate mit allen eventuellen
// ver-oderten Modifiern wie "brennend". Besser 'C_BodyStateContains(self,bodystate)' benutzen
			*/
			this->dataStack.Pop();

			this->PushInt(0);
		}
		break;
	case EXTERNAL_NPC_GETDISTTOWP:
		{
			/*
			FUNC INT	Npc_GetDistToWP				(VAR C_NPC self, VAR STRING wpName)
// liefert die Entfernung vom NSC 'self' zum angegebenen Waypoint in cm
			*/

			this->PopString();
			this->dataStack.Pop();

			this->PushInt(0);
		}
		break;
	case EXTERNAL_NPC_GETLOOKATTARGET:
		{
			/*
			NO DOC!

			func C_NPC Npc_GetLookAtTarget(C_NPC);
			*/

			this->dataStack.Pop();
			this->dataStack.Push(0);
		}
		break;
	case EXTERNAL_NPC_GETTALENTSKILL:
		{
			/*
			FUNC INT Npc_GetTalentSkill(VAR C_NPC npc, VAR INT skill);

			NO DOC!
			*/
			this->PopInt();
			this->dataStack.Pop();

			this->PushInt(0);
		}
		break;
	case EXTERNAL_NPC_HASITEMS:
		{
			uint32 itemSymbolIndex, npcSymbolIndex;
			CNPC *pNPC;

			/*
			FUNC INT Npc_HasItems (VAR C_NPC n0, VAR INT itemInstance);

			returns the multiplicity of 'itemInstance' in 'n0's inventory or 0 if not in inventory
			*/
			
			itemSymbolIndex = this->PopInt();
			npcSymbolIndex = (uint32)this->dataStack.Pop();

			SSymbol &refNPCSymbol = this->pProgram->GetSymbol(npcSymbolIndex);
			SSymbol &refItemSymbol = this->pProgram->GetSymbol(itemSymbolIndex);
			pNPC = (CNPC *)refNPCSymbol.pCurrentInstance;
			
			this->PushInt(pNPC->GetItemMultiplicity(refItemSymbol.name));
		}
		break;
	case EXTERNAL_NPC_ISDEAD:
		{
			//!!!!!!!!!!!!!!!!!!!!NOT IMPLEMENTED CORRECTLY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			/*
			FUNC INT Npc_IsDead (VAR C_NPC npc);
			
			True if npc is dead
			*/
			this->dataStack.Pop();
			
			this->PushInt(0);
		}
		break;
	case EXTERNAL_NPC_ISINFIGHTMODE:
		{
			/*
			FUNC INT Npc_IsInFightMode(VAR C_NPC self, VAR INT fmode);
			
			liefert eins zurück, wenn der Charakter im angegebenen Fightmode (z.B. FMODE_MAGIC) ist
			*/

			this->PopInt();
			this->dataStack.Pop();

			this->PushInt(0);
		}
		break;
	case EXTERNAL_NPC_ISINSTATE:
		{
			/*
			FUNC INT Npc_IsInState (VAR C_NPC self, VAR FUNC state);
			
			Abfrage auf den aktuellen Zustand einer Spielfigur True/False
			*/

			this->PopInt();
			this->dataStack.Pop();
			
			this->PushInt(0);
		}
		break;
	case EXTERNAL_NPC_ISPLAYER:
		{
			/*
			FUNC INT	Npc_IsPlayer				(VAR C_NPC player)			{ return 0; };
			// liefert eins zurück, wenn der geprüfte Charakter der Spieler himself ist
			*/
			this->dataStack.Pop();
			this->PushInt(0);
		}
		break;
	case EXTERNAL_NPC_KNOWSINFO:
		{
			/*
			FUNC INT Npc_KnowsInfo(VAR C_NPC self, VAR INT infoInstance);
			
			Liefert TRUE, wenn der angegebene Spieler die Info schon einmal erhalten hat.
			VORSICHT: auch wenn eine permanente Info schon einmal dem Spieler erzählt wurde, so gibt diese Funktion trotzdem FALSE zurück!
			*/

			this->PopInt();
			this->dataStack.Pop();

			this->PushInt(0);
		}
		break;
	case EXTERNAL_NPC_PERCEIVEALL:
		{
			/*
			FUNC VOID 	Npc_PerceiveAll				(VAR C_NPC self) 		  {};
// Nimm alle Objekte in Wahrnehmungsreichweite wahr, die dann mit WLD_DetectNpc und Wld_DetectItem auswertbar sind
			*/
			
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_NPC_REMOVEINVITEMS:
		{
			uint32 amount, itemSymbolIndex, npcSymbolIndex;
			CNPC *pNPC;
			
			/*
			func void Npc_RemoveInvItems (VAR C_NPC owner, VAR int itemInstance, VAR INT amount);

			removes 'amount' instances of 'itemInstance' of 'owner's inventory
			*/

			amount = this->PopInt();
			itemSymbolIndex = this->PopInt();
			npcSymbolIndex = (uint32)this->dataStack.Pop();
			
			SSymbol &refNPCSymbol = this->pProgram->GetSymbol(npcSymbolIndex);
			SSymbol &refItemSymbol = this->pProgram->GetSymbol(itemSymbolIndex);
			
			pNPC = (CNPC *)refNPCSymbol.pCurrentInstance;

			pNPC->RemoveItems(refItemSymbol.name, amount);
		}
		break;
	case EXTERNAL_NPC_SETATTITUDE:
		{
			/*
			FUNC VOID Npc_SetAttitude (VAR C_NPC self, VAR INT att);

			Sets permanent attitude of npc 'self' to 'att'
			*/

			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_NPC_SETTALENTSKILL:
		{
			/*
			NO DOC!
			
			func void Npc_SetTalentSkill(npc, int, int);
			*/
			
			this->PopInt();
			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_NPC_SETTEMPATTITUDE:
		{
			/*
			FUNC VOID Npc_SetTempAttitude (VAR C_NPC self, VAR INT att);
			
			Sets temporary attitude of npc 'self' to 'att'
			*/
			
			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_NPC_SETTOFIGHTMODE:
		{
			uint32 weaponInstanceSymbolIndex;
			CItem *pItem;
			CNPC *pNpc;
			
			/*
			FUNC VOID Npc_SetToFightMode (VAR C_NPC self, VAR INT weapon);
			
			Setzt den NSC beim Start in den der Waffe entsprechenden Kampfmodus (Waffe wird erzeugt)
			*/
			
			weaponInstanceSymbolIndex = this->PopInt();
			
			SSymbol &refSymbol = this->pProgram->GetSymbol((uint32)this->dataStack.Pop());
			SSymbol &refWeaponSymbol = this->pProgram->GetSymbol(weaponInstanceSymbolIndex);
			
			pItem = new CItem(refWeaponSymbol.name);
			pNpc = (CNPC *)refSymbol.pCurrentInstance;
			
			pNpc->AddItem(pItem);
			pNpc->EquipItem(pItem);
		}
		break;
	case EXTERNAL_NPC_SETTOFISTMODE:
		{
			/*
			FUNC VOID Npc_SetToFistMode (VAR C_NPC self);
			
			Setzt den NSC beim Start in den Faustkampfmodus (zB.Monster)
			*/
			
			this->PopInt();
		}
		break;
	case EXTERNAL_NPC_STOPANI:
		{
			/*
			NO DOC!
			
			func void Npc_StopAni(C_NPC, string)
			*/

			this->PopString();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_PLAYVIDEO:
		{
			/*
			func int PlayVideo (var string Filename);
			
			Spielt eine Videodatei ab.
			Filename	- Dateiname des Videos (mit Dateierweiterung, relativ zu [VIDEOS]\ )
			[result]	- Boolean ob erfolgreich abgespielt
			*/

			this->PopString();
			this->PushInt(1); //was played fine ;)
		}
		break;
	case EXTERNAL_PLAYVIDEOEX:
		{
			/*
			func int	PlayVideoEx			(var string Filename, var int ScreenBlend, var int ExitSession) {};

								// Spielt eine Videodatei mit erweiterten Optionen ab.
								//
								//	Filename	- Dateiname des Videos (mit Dateierweiterung, relativ zu [VIDEOS]\ )
								//	ScreenBlend	- Boolean ob Effekt 'BLACK_SCREEN' danach abgespielt wird (nicht bei ExitSession)
								//	ExitSession	- Boolean ob nach dem Video die Session beendet wird
								//	[result]	- Boolean ob erfolgreich abgespielt, bei ExitSession immer erfolgreich
			*/
			this->PopInt();
			this->PopInt();
			this->PopString();
			
			this->PushInt(0);
		}
		break;
	case EXTERNAL_PRINT:
		{
			/*
			FUNC VOID Print(VAR STRING s0);
			Ausgabebefehl, der Text ins Game schreibt (wie OutputunitTexte)
			*/
			this->PopString();
		}
		break;
	case EXTERNAL_PRINTDEBUG:
		{
			/*
			FUNC VOID PrintDebug			(VAR STRING s)	 { };
			// Printausgabe, die nur bei eingeschaltetem Debugmodus (Alt+D) im Spy/logfile ausgegeben wird
			*/
			this->PopString();
		}
		break;
	case EXTERNAL_PRINTSCREEN:
		{
			/*
			func VOID PrintScreen(VAR STRING msg, VAR INT posx, VAR INT posy, VAR STRING font, VAR INT timeSec);
			
			Gibt den Text 'msg' auf dem Bildschrim aus und benutzt dabei den Font 'font'.
			Die Position ist für jede Koordinate eine Zahl zwischen 0 und 99 und gibt die prozentuale Position an.
			Der Ursprung befindet sich oben links (also 0% X und 0% Y)
			*/
			this->PopInt();
			this->PopString();
			this->PopInt();
			this->PopInt();
			this->PopString();
		}
		break;
	case EXTERNAL_SND_PLAY:
		{
			/*
			FUNC VOID 	Snd_Play 					(VAR STRING s0 ) { };
// spielt einen Sound ab
			*/
			this->PopString();
		}
		break;
	case EXTERNAL_TA_MIN:
		{
			/*
			FUNC VOID TA_Min (var c_npc self, var int start_h, var int start_m, var int stop_h, var int stop_m, VAR func state, VAR string waypoint);
			
			Tagesablaufpunkt minutengenau angeben
			*/
			this->PopString();
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	case EXTERNAL_WLD_ASSIGNROOMTOGUILD:
		{
			//!!!!!!!!!!!!!!!!!!!!NOT IMPLEMENTED CORRECTLY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			/*
			FUNC VOID Wld_AssignRoomToGuild (VAR STRING s0, VAR INT guild);
			
			Ordnet den Raum: 's0' der Gilde 'guild' zu
			*/

			this->PopInt();
			this->PopString();
		}
		break;
	case EXTERNAL_WLD_GETPLAYERPORTALGUILD:
		{
			/*
			FUNC INT 	Wld_GetPlayerPortalGuild 	()
// liefert Gilde des aktiven Raums, in dem sich der SC gerade befindet, zurück
// - wenn der SC 'draußen' ist, dann wird GIL_NONE zurückgegeben
// - wenn der aktive Raum gildenlos ist, dann wird GIL_NONE zurückgeliefert
			*/
			this->PushInt(0); //GIL_NONE
		}
		break;
	case EXTERNAL_WLD_INSERTITEM:
		{
			uint32 itemInstanceSymbolIndex;
			CItem *pItem;

			const CString &refSpawnpoint = *this->PopString();

			/*
			FUNC VOID Wld_InsertItem (VAR INT itemInstance, VAR STRING spawnPoint);
			
			Füge Item in Welt ein entweder an einem WP oder einem FP
			*/
			
			itemInstanceSymbolIndex = this->PopInt();

			SSymbol &refSymbol = this->pProgram->GetSymbol(itemInstanceSymbolIndex);
			
			pItem = new CItem(refSymbol.name);
			CGame::GetInstance().GetActiveWorld()->InsertVob(pItem);
		}
		break;
	case EXTERNAL_WLD_INSERTNPC:
		{
			uint32 npcInstanceSymbolIndex;
			CNPC *pNpc;
			
			/*
			FUNC VOID Wld_InsertNpc (VAR INT npcInstance, VAR STRING spawnPoint);
			
			Füge NSC in Welt ein. Wobei SPawnpoint entweder ein WP oder ein FP sein darf.
			*/

			CGame &refGame = CGame::GetInstance();
			const CString &refSpawnpoint = *this->PopString();
			
			npcInstanceSymbolIndex = this->PopInt();
			SSymbol &refNPCSymbol = this->pProgram->GetSymbol(npcInstanceSymbolIndex);
			
			pNpc = new CNPC(refNPCSymbol.name);
			CGame::GetInstance().GetActiveWorld()->InsertVob(pNpc);
		}
		break;
	case EXTERNAL_WLD_ISTIME:
		{
			/*
			FUNC INT    Wld_IsTime			(VAR INT hour1, VAR INT min1, VAR INT hour2, VAR INT min2) { return 0; };
// Liefert "1" wenn aktuelle Weltzeit zwischen den beiden angegebenen Zeiten liegt (von - bis)
			*/
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();

			this->PushInt(0);
		}
		break;
	case EXTERNAL_WLD_PLAYEFFECT:
		{
			/*
			FUNC VOID Wld_PlayEffect(string, C_NPC, C_NPC, int, int, int, int)
			*/

			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->dataStack.Pop();
			this->dataStack.Pop();
			this->PopString();
		}
		break;
	case EXTERNAL_WLD_SETGUILDATTITUDE:
		{
			//!!!!!!!!!!!!!!!!!!!!NOT IMPLEMENTED CORRECTLY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			/*
			FUNC VOID Wld_SetGuildAttitude (var INT guild1, VAR INT attitude, VAR INT guild2);
			Setze Gildenattitude neu
			*/

			this->PopInt();
			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_WLD_SETMOBROUTINE:
		{
			//!!!!!!!!!!!!!!!!!!!!NOT IMPLEMENTED CORRECTLY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			
			/*
			FUNC VOID Wld_SetMobRoutine (var INT hour1, VAR INT min1, VAR STRING objName, VAR INT state);
			
			_Alle_ Mobs mit diesem _Schemanamen_ werden getriggert.
			*/

			this->PopInt();
			this->PopString();
			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_WLD_SETTIME:
		{
			/*
			NO DOC!

			void(int, int)
			*/

			this->PopInt();
			this->PopInt();
		}
		break;
	case EXTERNAL_WLD_SPAWNNPCRANGE:
		{
			/*
			FUNC VOID Wld_SpawnNpcRange(C_NPC, int, int, float)
			*/

			this->PopInt();
			this->PopInt();
			this->PopInt();
			this->dataStack.Pop();
		}
		break;
	default:
		stdOut << "UNKNOWN EXTERNAL!!! idx:" << symbolIndex << "; addr:" << this->pProgram->GetSymbol(symbolIndex).data.programOffset << endl;
		stdOut << this->pProgram->GetSymbol(symbolIndex).name << "; callOffset= " << (int32)callOffset << endl;
		ASSERT(0);
	}
}