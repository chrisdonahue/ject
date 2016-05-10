/*
  ==============================================================================

	XmlHelper.cpp
	Created: 9 May 2016 8:03:43pm
	Author:  Chris

  ==============================================================================
*/

#include "XmlHelper.h"

XmlElement* XmlHelper::fileListColumns = XmlDocument::parse(BinaryData::fileListAttributes_xml)->getChildByName("COLUMNS");

XmlElement* XmlHelper::loadDataFromResource() {
	XmlElement* fileList = XmlDocument::parse(BinaryData::fileListAttributes_xml);
	return fileList;
};

String XmlHelper::getAttributeNameForColumnId(const int columnId) {
	forEachXmlChildElement(*fileListColumns, columnXml) {
		if (columnXml->getIntAttribute("columnId") == columnId)
			return columnXml->getStringAttribute("name");
	}

	return String();
};

String XmlHelper::getStringAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId) {
	String attributeName = getAttributeNameForColumnId(columnId);
	XmlElement* child = fileListData->getChildElement(rowId);
	return child->getStringAttribute(attributeName);
};

int XmlHelper::getIntAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId) {
	String attributeName = getAttributeNameForColumnId(columnId);
	XmlElement* child = fileListData->getChildElement(rowId);
	return child->getIntAttribute(attributeName);
};

double XmlHelper::getDoubleAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId) {
	String attributeName = getAttributeNameForColumnId(columnId);
	XmlElement* child = fileListData->getChildElement(rowId);
	return child->getDoubleAttribute(attributeName);
};