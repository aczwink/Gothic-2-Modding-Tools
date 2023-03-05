//Main Header
#include "HTML.h"
//Global
#include <cstdarg>

void WriteHTMLHead(CString title, AOutputStream &refOutputStream, CString pathToRoot)
{
	refOutputStream << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">"
		<< "<html xmlns=\"http://www.w3.org/1999/xhtml\">"
		<< "<head>"
		<< "<title>" << title << "</title>"
		<< "<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />"
		<< "<link href=\"" << pathToRoot << "style.css\" rel=\"stylesheet\" type=\"text/css\" />"
		<< "<script type=\"text/javascript\" src=\"" << pathToRoot << "sort.js\"></script>"
		<< "</head>"
		<< "<body>";
}

void WriteHTMLTableHeadBegin(AOutputStream &refOutputStream)
{
	refOutputStream << "<table><thead><tr>";
}

void WriteHTMLSortableTableHeadBegin(AOutputStream &refOutputStream)
{
	refOutputStream << "<table class=\"sortable\"><thead><tr>";
}

void WriteHTMLTableHeadCol(AOutputStream &refOutputStream, const CString &refTitle)
{
	refOutputStream << "<th>" << refTitle << "</th>";
}

void WriteHTMLTableHeadCol(AOutputStream &refOutputStream, const CString &refTitle, const CString &refClass)
{
	refOutputStream << "<th class=\"" << refClass << "\">" << refTitle << "</th>";
}

void WriteHTMLTableHeadEnd(AOutputStream &refOutputStream)
{
	refOutputStream << "</tr></thead><tbody>";
}

void WriteHTMLTableFoot(AOutputStream &refOutputStream)
{
	refOutputStream << "</tbody></table>";
}

void WriteHTMLFoot(AOutputStream &refOutputStream)
{
	refOutputStream << "<script type=\"text/javascript\">window.onload = function(){ MakeSortableList(document.getElementsByClassName(\"sortable\")); };</script>";
	refOutputStream << "</body></html>";
}