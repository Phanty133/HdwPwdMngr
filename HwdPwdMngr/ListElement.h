#pragma once
#include "curses.h"
#include <string>
#include <vector>
#include <map>
#include "DrawUtil.h"
#include "Scrollbar.h"

struct ListColumn {
	std::string label;
	int width = NULL; // Width in columns
	std::string key; // Column key, defaults to `label`
	
	ListColumn(std::string label, std::string key, int width = NULL) {
		this->label = label;
		this->width = width;
		this->key = key == "" ? label : key;
	};
};

struct ListColumnMetadata {
	int width;
	int x;
	
	ListColumnMetadata(int width, int x) {
		this->width = width;
		this->x = x;
	}
};

typedef std::map<std::string, std::string> DataEntry;

class ListElement {
public:	
	ListElement(int y, int x, int h, int w, std::vector<ListColumn> cols, std::vector<DataEntry> data);
	void moveUp(); // Selects the item above the currently selected item
	void moveDown(); // Selects the item below the currently selected item
	void selectEntry(int index); // Select entry at `index`

	const int& c_cur = m_cur;
	const int& c_x = m_x;
	const int& c_y = m_y;
	const int& c_w = m_w;
	const int& c_h = m_h;

	const WINDOW* c_win = m_win;
	const std::vector<ListColumn>& c_cols = m_cols;
	const std::vector<DataEntry>& c_data = m_data;

private:
	void drawEntry(DataEntry entry, int y); // Returns entry height
	void drawHeaders();
	void drawEntries(); // Draws the visible entries (based on current scroll position)
	void drawEntryCounter(); // Draws the counter that displays the currently selected entry
	void draw();
	void highlightEntry(int index); // Highlight entry at `index`
	void unhighlightEntry(int index); // Unhighlight entry at `index`
	void updateEntryCounter();

	WINDOW* m_win; // Window of the list
	int m_cur; // Index of currently selected data entry
	std::vector<ListColumn> m_cols;
	std::map<std::string, ListColumn> m_keyedCols;
	std::map<std::string, ListColumnMetadata> m_colMetadata; // Metadata of columns, indexed by column key
	std::map<int, int> m_entryY; // Y of entries, indexed by m_data index
	std::vector<DataEntry> m_data;

	int m_x;
	int m_y;
	int m_w;
	int m_h;
	int m_wTable; // Width without the scroll bar
	int m_entryStartY; // Y of where entries start (Right after the header)
	int m_entryPageSize; // How many entries can fit on the screen at one time
	int m_counterDigitCount;
};
