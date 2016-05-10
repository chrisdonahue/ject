/*
  ==============================================================================

    XmlHelper.h
    Created: 9 May 2016 6:10:10pm
    Author:  Chris

  ==============================================================================
*/

#ifndef XMLHELPER_H_INCLUDED
#define XMLHELPER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

namespace XmlHelper {
	enum Column {
		id=1,
		path,
		name,
		include,
		pValue,
		rValue
	};

	XmlElement* fileListColumns;

	XmlElement* loadDataFromResource() {
		XmlElement* fileList = XmlDocument::parse(BinaryData::fileListAttributes_xml);
		fileListColumns = fileList->getChildByName("COLUMNS");
		return fileList;
	};

	String getAttributeNameForColumnId(const int columnId) {
		forEachXmlChildElement(*fileListColumns, columnXml) {
			if (columnXml->getIntAttribute("columnId") == columnId)
				return columnXml->getStringAttribute("name");
		}

		return String();
	};

	String getStringAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId) {
		String attributeName = getAttributeNameForColumnId(columnId);
		XmlElement* child = fileListData->getChildElement(rowId);
		return child->getStringAttribute(attributeName);
	};

	int getIntAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId) {
		String attributeName = getAttributeNameForColumnId(columnId);
		XmlElement* child = fileListData->getChildElement(rowId);
		return child->getIntAttribute(attributeName);
	};

	double getDoubleAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId) {
		String attributeName = getAttributeNameForColumnId(columnId);
		XmlElement* child = fileListData->getChildElement(rowId);
		return child->getDoubleAttribute(attributeName);
	};
}

#endif  // XMLHELPER_H_INCLUDED
