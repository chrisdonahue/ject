/*
==============================================================================

InputFileTableListBox.h
Created: 6 May 2016 1:21:53pm
Author:  Chris

==============================================================================
*/

#ifndef INPUTFILETABLELISTBOX_H_INCLUDED
#define INPUTFILETABLELISTBOX_H_INCLUDED

#include <algorithm>
#include <vector>
#include <unordered_map>

#include "../JuceLibraryCode/JuceHeader.h"

#include "Sound.h"

using std::unordered_map;

class InputFileTableListBox : public TableListBox, public ChangeListener, public ChangeBroadcaster {
public:
	enum FileListChangeMessage {
		noChange = 0,
		includeChange,
		previewChange,
		prValueChange,
		selectionChange
	};

private:
	class SelectableLabel : public Label
	{
	public:
		SelectableLabel(InputFileTableListBox& table, int row) :
			table(table), row(row) {
			setColour(textColourId, Colours::black);
		};

		void mouseDown(const MouseEvent& event) override {
			table.selectRowsBasedOnModifierKeys(row, event.mods, false);
			Label::mouseDown(event);
		};

		void setRow(int rowNew) {
			row = rowNew;
		};

	private:
		InputFileTableListBox& table;
		int row;
	};

	enum Column {
		id = 1,
		path,
		name,
		include,
		pValue,
		rValue,
		preview
	};

	class InputFileTableListBoxModel : public TableListBoxModel, public ChangeBroadcaster, public ButtonListener, public SliderListener {
	public:
		InputFileTableListBoxModel(InputFileTableListBox& table) : table(table) {};

		int getNumRows() override {
			return table.idToSound.size();
		};

		void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override {
			if (rowIsSelected)
				g.fillAll(Colours::lightblue);
			else if (rowNumber % 2)
				g.fillAll(Colour(0xffeeeeee));
		};

		void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override {};

		Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override {
			jassert(rowNumber < table.rowToId.size());

			int id = table.rowToId[rowNumber];
			const Sound* sound = table.idToSound[id];

			if (columnId == Column::id) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
				}

				label->setText(String(id), dontSendNotification);

				return label;
			}
			else if (columnId == Column::path) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
				}

				label->setText(sound->getFilePath(), dontSendNotification);

				return label;
			}
			else if (columnId == Column::name) {
				Label* label = static_cast<Label*>(existingComponentToUpdate);

				if (label == nullptr) {
					label = new Label();
				}

				label->setText(sound->getName(), dontSendNotification);

				return label;
			}
			else if (columnId == Column::include) {
				ToggleButton* toggleButton = static_cast<ToggleButton*>(existingComponentToUpdate);

				if (toggleButton == nullptr) {
					toggleButton = new ToggleButton();
					toggleButton->addListener(this);
				}

				includeButtonToId[toggleButton] = id;
				toggleButton->setToggleState(sound->isIncluded(), dontSendNotification);

				return toggleButton;
			}
			else if (columnId == Column::pValue) {
				Slider* slider = static_cast<Slider*>(existingComponentToUpdate);

				if (slider == nullptr) {
					slider = new Slider();
					slider->setRange(0.0, 1.0, 0.01);
					slider->setSliderStyle(Slider::LinearHorizontal);
					slider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
					slider->addListener(this);
				}

				idToPSlider[id] = slider;
				pSliderToId[slider] = id;
				slider->setValue(sound->getPValue(), dontSendNotification);

				return slider;
			}
			else if (columnId == Column::rValue) {
				Slider* slider = static_cast<Slider*>(existingComponentToUpdate);

				if (slider == nullptr) {
					slider = new Slider();
					slider->setRange(0.0, 1.0, 0.01);
					slider->setSliderStyle(Slider::LinearHorizontal);
					slider->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 20);
					slider->addListener(this);
				}

				idToRSlider[id] = slider;
				rSliderToId[slider] = id;
				slider->setValue(sound->getRValue(), dontSendNotification);

				return slider;
			}
			else if (columnId == Column::preview) {
				TextButton* textButton = static_cast<TextButton*>(existingComponentToUpdate);

				if (textButton == nullptr) {
					textButton = new TextButton();
					textButton->addListener(this);
					textButton->setButtonText("Preview");
				}

				previewButtonToId[textButton] = id;

				return textButton;
			}
			else {
				jassertfalse;
				return nullptr;
			}
		};

		void sortOrderChanged(int newSortColumnId, bool isForwards) override {
			jassertfalse;
		};

		void selectedRowsChanged(int lastRowSelected) override {
			table.lastChangeMessageType = FileListChangeMessage::selectionChange;
			sendChangeMessage();
		};

		void buttonClicked(Button* button) override {
			auto previewButtonItr = previewButtonToId.find(button);
			bool isPreviewButton = previewButtonItr != previewButtonToId.end();
			auto includeButtonItr = includeButtonToId.find(button);
			bool isIncludeButton = includeButtonItr != includeButtonToId.end();
			jassert(isPreviewButton != isIncludeButton);

			if (isPreviewButton) {
				int id = previewButtonItr->second;
				table.previewId = id;
				table.lastChangeMessageType = FileListChangeMessage::previewChange;
			}
			else if (isIncludeButton) {
				int id = includeButtonItr->second;
				auto soundItr = table.idToSound.find(id);
				jassert(soundItr != table.idToSound.end());
				
				Sound* sound = soundItr->second;
				jassert(sound != nullptr);

				sound->setInclude(button->getToggleState());

				table.lastChangeMessageType = FileListChangeMessage::includeChange;
			}
			else {
				jassertfalse;
			}

			sendChangeMessage();
		};

		void sliderValueChanged(Slider* slider) override {
			int id = -1;
			Slider* other = nullptr;
			auto pSliderItr = pSliderToId.find(slider);
			auto rSliderItr = rSliderToId.find(slider);
			bool isPSlider = pSliderItr != pSliderToId.end();
			bool isRSlider = rSliderItr != rSliderToId.end();
			jassert(isPSlider != isRSlider);

			if (isPSlider) {
				id = pSliderItr->second;
				other = idToRSlider[id];
			}
			else {
				id = rSliderItr->second;
				other = idToPSlider[id];
			}
			jassert(id != -1);
			jassert(other != nullptr);

			const PrBehavior& behavior = table.prBehavior;
			if (behavior != PrBehavior::independent) {
				if (behavior == PrBehavior::linked) {
					other->setValue(slider->getValue());
				}
				else if (behavior == PrBehavior::inverse) {
					other->setValue(1.0 - slider->getValue());
				}
				else {
					jassertfalse;
				}
			}

			auto soundItr = table.idToSound.find(id);
			jassert(soundItr != table.idToSound.end());
			Sound* sound = soundItr->second;
			jassert(sound != nullptr);

			sound->setPValue(idToPSlider[id]->getValue());
			sound->setRValue(idToRSlider[id]->getValue());

			table.lastChangeMessageType = FileListChangeMessage::prValueChange;
			sendChangeMessage();
		};

	private:
		InputFileTableListBox& table;
		unordered_map<int, Slider*> idToPSlider;
		unordered_map<Slider*, int> pSliderToId;
		unordered_map<int, Slider*> idToRSlider;
		unordered_map<Slider*, int> rSliderToId;
		unordered_map<Button*, int> includeButtonToId;
		unordered_map<Button*, int> previewButtonToId;
	};

public:
	enum PrBehavior {
		independent = 1,
		linked,
		inverse
	};

	friend class InputFileTableListBoxModel;

	InputFileTableListBox(PrBehavior prBehavior) : model(*this), prBehavior(prBehavior), previewId(-1), lastChangeMessageType(FileListChangeMessage::noChange) {
		setModel(&model);
		setColour(ListBox::outlineColourId, Colours::grey);
		setClickingTogglesRowSelection(true);
		setMultipleSelectionEnabled(true);
		int flags = TableHeaderComponent::defaultFlags & ~TableHeaderComponent::sortable;
		getHeader().addColumn("ID", Column::id, 32, 32, -1, flags);
		getHeader().addColumn("Name", Column::name, 128, 32, -1, flags);
		getHeader().addColumn("Use", Column::include, 32, 32, -1, flags);
		getHeader().addColumn("Mag", Column::pValue, 128, 32, -1, flags);
		getHeader().addColumn("Phase", Column::rValue, 128, 32, -1, flags);
		getHeader().addColumn("Preview", Column::preview, 64, 32, -1, flags);
		model.addChangeListener(this);
	};

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (source == &model) {
			sendChangeMessage();
		}
	};

	void setIdToSound(const std::unordered_map<int, Sound*>& idToSoundNew) {
		idToSound = idToSoundNew;
		std::vector<int> ids;
		for (auto i : idToSound) {
			ids.push_back(i.first);
		}
		std::sort(ids.begin(), ids.end());

		rowToId.clear();
		for (auto it = ids.begin(); it != ids.end(); ++it) {
			int row = std::distance(ids.begin(), it);
			int id = *it;
			rowToId.emplace(row, id);
		}
	};

	void setPrBehavior(PrBehavior prBehaviorNew) {
		prBehavior = prBehaviorNew;
	};

	PrBehavior getPrBehavior() const {
		return prBehavior;
	};

	FileListChangeMessage getLastChangeMessageType() const {
		return lastChangeMessageType;
	}

	int getPreviewId() {
		int result = previewId;
		previewId = -1;
		return result;
	};

	int getIdForRow(int row) const {
		const auto& iter = rowToId.find(row);
		if (iter == rowToId.end()) {
			return -1;
		}
		return iter->second;
	};

private:
	InputFileTableListBoxModel model;
	unordered_map<int, Sound*> idToSound;
	unordered_map<int, int> rowToId;
	PrBehavior prBehavior;
	FileListChangeMessage lastChangeMessageType;
	int previewId;
};

#endif  // INPUTFILETABLELISTBOX_H_INCLUDED