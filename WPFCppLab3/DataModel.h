#pragma once

using namespace System::Reflection;
using namespace System::Runtime::Remoting;
using namespace System::Security;

ref class DataModel sealed
{
	SecurityZone _selectedSecurityZone = SecurityZone::MyComputer;

	array<MethodInfo^>^ _methods = nullptr;
	array<FieldInfo^>^ _fields = nullptr;
	Object^ _instance;
    System::Type^ _type;
	ObjectHandle^ _handle;

public:
	property SecurityZone SelectedSecurityZone {
		SecurityZone get() {
			return _selectedSecurityZone;
		}

		void set(const SecurityZone value) {
			_selectedSecurityZone = value;
		}
	}

	property array<MethodInfo^>^ Methods {
		array<MethodInfo^>^ get() {
			return _methods;
		}

		void set(array<MethodInfo^>^ value) {
			_methods = value;
		}
	}

	property array<FieldInfo^>^ Fields {
		array<FieldInfo^>^ get() {
			return _fields;
		}

		void set(array<FieldInfo^>^ value) {
			_fields = value;
		}
	}

	property Object^ Instance {
		Object^ get() {
			return _instance;
		}

		void set(Object^ value) {
			_instance = value;
		}
	}

	property ObjectHandle^ Handle {
		ObjectHandle^ get() {
			return _handle;
		}

		void set(ObjectHandle^ value) {
			_handle = value;
		}
	}

	property System::Type^ Type {
		System::Type^ get() {
			return _type;
		}

		void set(System::Type^ value) {
			_type = value;
		}
	}
};