/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "KeySet.h"
#include "Game/Console.h"
#include "Game/Action.h"

class CUnit;
class CSimpleParser;


class CKeyBindings : public CommandReceiver
{
	public:
		CKeyBindings();
		~CKeyBindings();

		bool Load(const std::string& filename);
		bool Save(const std::string& filename) const;
		void Print() const;

		typedef std::vector<Action> ActionList;
		typedef std::vector<std::string> HotkeyList;

		const ActionList& GetActionList(const CKeySet& ks) const;
		const HotkeyList& GetHotkeys(const std::string& action) const;

		virtual void PushAction(const Action&);
		bool ExecuteCommand(const std::string& line);

		int GetFakeMetaKey() const { return fakeMetaKey; }


	protected:
		void LoadDefaults();
		void Sanitize();
		void BuildHotkeyMap();

		bool Bind(const std::string& keystring, const std::string& action);
		bool UnBind(const std::string& keystring, const std::string& action);
		bool UnBindKeyset(const std::string& keystr);
		bool UnBindAction(const std::string& action);
		bool SetFakeMetaKey(const std::string& keystring);
		bool AddKeySymbol(const std::string& keysym, const std::string& code);

		bool ParseKeySet(const std::string& keystr, CKeySet& ks) const;
		bool RemoveCommandFromList(ActionList& al, const std::string& command);

		bool FileSave(FILE* file) const;

	protected:
		typedef std::map<CKeySet, ActionList> KeyMap; // keyset to action
		KeyMap bindings;

		typedef std::map<std::string, HotkeyList> ActionMap; // action to keyset
		ActionMap hotkeys;

	protected:
		// commands that use both Up and Down key presses
		std::set<std::string> statefulCommands;

		int fakeMetaKey;
		bool userCommand;
	private:
		bool debugEnabled;
};


extern CKeyBindings* keyBindings;


#endif /* KEYBINDINGS_H */
