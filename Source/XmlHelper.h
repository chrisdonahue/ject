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
		id = 1,
		path,
		name,
		include,
		pValue,
		rValue
	};

	extern XmlElement* fileListColumns;
	extern XmlElement* loadDataFromResource();
	extern String getAttributeNameForColumnId(const int columnId);
	extern String getStringAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId);
	extern int getIntAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId);
	extern double getDoubleAttributeForRowColumnId(XmlElement* fileListData, const int columnId, const int rowId);
}

#endif  // XMLHELPER_H_INCLUDED
