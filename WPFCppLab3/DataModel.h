#include <windows.h>
using namespace System::Reflection;
using namespace System::Security;

typedef System::Collections::ObjectModel::ObservableCollection<MethodInfo^> myList;

ref class DataModel {
	SecurityZone selectedSecurityZone = System::Security::SecurityZone::MyComputer;
	myList^ methods = gcnew myList;
	// tutaj zdefiniuj pozosta³e zmienne modelu danych

public:
	property SecurityZone SelectedSecurityZone {
		SecurityZone get() {
			return selectedSecurityZone;
		}

		void set(SecurityZone value) {
			selectedSecurityZone = value;
		}
	}
	property myList^ Methods {
		myList^ get() {
			return methods;
		}

		void set(myList^ value) {
			methods = value;
		}
	}

	// tutaj zdefiniuj pozosta³e w³aœciwiœci modelu danych

};