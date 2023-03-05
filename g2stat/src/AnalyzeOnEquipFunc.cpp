//Class Header
#include "CAnalyzer.h"

/*//Local
#include "CreateDocs.h"
#include "Daedalus.h"
//Namespaces
using namespace SJCPBLib;
using namespace Daedalus;

void AnalyzeOnEquipFunc(SFunction *pFunc, SOnEquipAnalizationInfo &refOutInfo, CCompilePreprocessor &refCompilePreproc)
{
	SStatements *pStatements;
	
	MemZero(&refOutInfo, sizeof(refOutInfo));

	for(pStatements = pFunc->pStatements; pStatements; pStatements = pStatements->pNext)
	{
		switch(pStatements->pStatement->type)
		{
		case STATEMENTTYPE_ASSIGNEXPR:
			{
				if(pStatements->pStatement->value.assign.pLeftValue->type == LEFTVALUETYPE_MEMBER || pStatements->pStatement->value.assign.pLeftValue->type == LEFTVALUETYPE_MEMBERARRAY)
				{
					if(*pStatements->pStatement->value.assign.pLeftValue->pIdentifier == "self")
					{
						switch(pStatements->pStatement->value.assign.pExpr->type)
						{
						case EXPRESSIONTYPE_PLUS:
							{
								SExpression *pLeft, *pRight;
								UValue valRight;

								pLeft = pStatements->pStatement->value.assign.pExpr->value.binaryOp.pLeft;
								pRight = pStatements->pStatement->value.assign.pExpr->value.binaryOp.pRight;
								
								if(pLeft->type == EXPRESSIONTYPE_LEFTVALUE && pLeft->value.pLeftValue->type == pStatements->pStatement->value.assign.pLeftValue->type && *pLeft->value.pLeftValue->pMemberIdentifier == *pStatements->pStatement->value.assign.pLeftValue->pMemberIdentifier && refCompilePreproc.EvalExpression(*pRight, valRight))
								{
									if(*pLeft->value.pLeftValue->pMemberIdentifier == "attribute")
									{
										switch(pLeft->value.pLeftValue->pArrayIndex->index)
										{
										case 1: //ATR_HITPOINTS_MAX
											{
												refOutInfo.toLife += valRight.i;
											}
											break;
										case 3: //ATR_MANA_MAX
											{
												refOutInfo.toMana += valRight.i;
											}
											break;
										}
									}
								}
							}
							break;
						}
					}
				}
			}
			break;
		case STATEMENTTYPE_CALL:
			{
				SExpression *pArg1, *pArg2, *pArg3;
				UValue valArg2, valArg3;

				MemZero(&valArg2, sizeof(valArg2));
				MemZero(&valArg3, sizeof(valArg3));
				
				if(*pStatements->pStatement->value.call.pFunctionName == "Npc_ChangeAttribute")
				{
					pArg1 = pStatements->pStatement->value.call.pArgs->pExpr;
					pArg2 = pStatements->pStatement->value.call.pArgs->pNext->pExpr;
					pArg3 = pStatements->pStatement->value.call.pArgs->pNext->pNext->pExpr;
					
					if(pArg1->type == EXPRESSIONTYPE_LEFTVALUE && pArg1->value.pLeftValue->type == LEFTVALUETYPE_IDENTIFIER && *pArg1->value.pLeftValue->pIdentifier == "self")
					{
						if(refCompilePreproc.EvalExpression(*pArg2, valArg2) && refCompilePreproc.EvalExpression(*pArg3, valArg3))
						{
							switch(valArg2.i)
							{
							case 4: //strength
								{
									refOutInfo.toStr += valArg3.i;
								}
								break;
							case 5: //dexterity
								{
									refOutInfo.toDex += valArg3.i;
								}
								break;
							}
						}
					}
				}
			}
			break;
		case STATEMENTTYPE_PLUSASSIGNEXPR:
			{
				if(pStatements->pStatement->value.assign.pLeftValue->type == LEFTVALUETYPE_MEMBER || pStatements->pStatement->value.assign.pLeftValue->type == LEFTVALUETYPE_MEMBERARRAY)
				{
					UValue valRight;
					
					if(*pStatements->pStatement->value.assign.pLeftValue->pIdentifier == "self" && refCompilePreproc.EvalExpression(*pStatements->pStatement->value.assign.pExpr, valRight))
					{
						if(*pStatements->pStatement->value.assign.pLeftValue->pMemberIdentifier == "attribute")
						{
							switch(pStatements->pStatement->value.assign.pLeftValue->pArrayIndex->index)
							{
							case 1: //ATR_HITPOINTS_MAX
								{
									refOutInfo.toLife += valRight.i;
								}
								break;
							case 3: //ATR_MANA_MAX
								{
									refOutInfo.toMana += valRight.i;
								}
								break;
							case 4: //strength
								{
									refOutInfo.toStr += valRight.i;
								}
								break;
							case 5: //dexterity
								{
									refOutInfo.toDex += valRight.i;
								}
								break;
							}
						}
						else if(*pStatements->pStatement->value.assign.pLeftValue->pMemberIdentifier == "protection")
						{
							switch(pStatements->pStatement->value.assign.pLeftValue->pArrayIndex->index)
							{
							case 2: //PROT_EDGE
								{
									refOutInfo.toProtEdge += valRight.i;
								}
								break;
							case 3: //PROT_FIRE
								{
									refOutInfo.toProtFire += valRight.i;
								}
								break;
							case 5: //PROT_MAGIC
								{
									refOutInfo.toProtMagic += valRight.i;
								}
								break;
							case 6: //PROT_POINT
								{
									refOutInfo.toProtPoint += valRight.i;
								}
								break;
							}
						}
					}
				}
			}
			break;
		}
	}
}*/