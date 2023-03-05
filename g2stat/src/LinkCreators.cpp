/*//Local
#include "CreateDocs.h"

void PrintLink(const CItem *pItem, AOutputStream &refOutput, CString path)
{
	if(pItem)
	{
		refOutput << "<a href=\"" << path << "items/" << pItem->GetInstanceName() << ".htm\">";
		if(pItem->GetMultiplicity() > 1)
		{
			refOutput << pItem->GetMultiplicity() << "x ";
		}
		refOutput << pItem->GetName() << "</a>";
	}
}*/