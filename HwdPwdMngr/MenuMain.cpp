#include "MenuMain.h"
#include "ListElement.h"

MenuMain::MenuMain(int h, int w): Menu(h, w) {
	m_title = "Accounts";

	m_list = new ListElement(2, 0, h - 4, w, std::vector<ListColumn>(), std::vector<DataEntry>(), m_win);
}

MenuMain::~MenuMain()
{
	delete m_list;
}

void MenuMain::draw()
{
	drawBase();

	ListColumn col1("Label", "label");
	ListColumn col2("Username", "username", 50);

	std::vector<ListColumn> cols;
	cols.push_back(col1);
	cols.push_back(col2);

	std::vector<DataEntry> data;

	for (int i = 0; i < 50; i++) {
		DataEntry entry;
		entry["label"] = "ThisIsLabel" + std::to_string(i);
		entry["username"] = "ThisIsUsername" + std::to_string(i);

		data.push_back(entry);
	}

	m_list->setCols(cols);
	m_list->setData(data);
	wrefresh(m_win);
}

void MenuMain::inputHandler(int ch)
{
	switch (ch) {
	case KEY_DOWN:
		m_list->moveDown();
		break;
	case KEY_UP:
		m_list->moveUp();
		break;
	}
}
