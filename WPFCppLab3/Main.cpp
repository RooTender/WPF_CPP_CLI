#include <windows.h>
#include "DataModel.h"
using namespace System::Runtime::Remoting;
using namespace Policy;
using namespace System::Security;
using namespace System;
using namespace Windows;
using namespace IO;
using namespace Markup;
using namespace Controls;
using namespace CodeDom;
using namespace Compiler;
using namespace Reflection;
using namespace Documents;
using namespace std;


public ref class MyApplication sealed : public Application
{
	DataModel ^_dataModel;
	String ^_pathToCode, ^_code;
	Button ^_addButton, ^_invokeButton, ^_setButton;
	RichTextBox ^_richTextBox;
	ListBox ^_errorsListBox, ^_methodsListBox, ^_variablesListBox;
	Assembly ^_assembly;
	Type ^_type;
	Object ^_instance;
	ObjectHandle ^_handle;
	array<FieldInfo^> ^_fields;
	MethodInfo ^_methodInfo;
	FieldInfo ^_fieldInfo;
	TextBox ^_resultTextBox, ^_parameterTextBox, ^_setTextBox, ^_setTextBox2;
	ComboBox ^_checkZoneComboBox;

	Void OnSelectionMethodsListBoxChanged(Object^ sender, SelectionChangedEventArgs^ e)
	{

	}
	
	Void OnSelectionVariablesListBoxChanged(Object^ sender, SelectionChangedEventArgs^ e)
	{

	}

	Void OnInvokeButtonClick(Object^ sender, RoutedEventArgs^ e)
	{

	}

	Void OnSetButtonClick(Object^ sender, RoutedEventArgs^ e)
	{

	}
	
	Void OnAddButtonClick(Object^ sender, RoutedEventArgs^ e)
	{

	}

public:
	MyApplication(Window ^win)
	{
		_dataModel = gcnew DataModel();
		win->DataContext = _dataModel;

		_pathToCode = gcnew String("..\\VBCode\\Class1.vb");
		_code = File::ReadAllText(_pathToCode);

		_addButton =		 safe_cast<Button^>(win->FindName("addButton"));
		_invokeButton =		 safe_cast<Button^>(win->FindName("invokeButton"));
		_setButton =		 safe_cast<Button^>(win->FindName("setButton"));
		_methodsListBox =	 safe_cast<ListBox^>(win->FindName("methodsListBox"));
		_variablesListBox =  safe_cast<ListBox^>(win->FindName("variablesListBox"));
		_errorsListBox =	 safe_cast<ListBox^>(win->FindName("errorsListBox"));
		_resultTextBox =	 safe_cast<TextBox^>(win->FindName("resultTextBox"));
		_parameterTextBox =  safe_cast<TextBox^>(win->FindName("parameterTextBox"));
		_setTextBox =		 safe_cast<TextBox^>(win->FindName("setTextBox"));
		_setTextBox2 =		 safe_cast<TextBox^>(win->FindName("setTextBox2"));
		_checkZoneComboBox = safe_cast<ComboBox^>(win->FindName("checkZoneComboBox"));

		_addButton->Click		+= gcnew RoutedEventHandler(this, &MyApplication::OnAddButtonClick);
		_invokeButton->Click	+= gcnew RoutedEventHandler(this, &MyApplication::OnInvokeButtonClick);
		_setButton->Click		+= gcnew RoutedEventHandler(this, &MyApplication::OnSetButtonClick);
		_methodsListBox->SelectionChanged +=	gcnew SelectionChangedEventHandler(this, &MyApplication::OnSelectionMethodsListBoxChanged);
		_variablesListBox->SelectionChanged +=	gcnew SelectionChangedEventHandler(this, &MyApplication::OnSelectionVariablesListBoxChanged);

		_richTextBox = safe_cast<RichTextBox^>(win->FindName("codeRichTextBox"));
		_richTextBox->AppendText(_code);
		_richTextBox->Document->LineHeight = 0.1;
	}
};

[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Stream^ st = File::OpenRead("MainWindow.xaml");
	Window^ win = safe_cast<Window^>(XamlReader::Load(st, nullptr));
	Application^ app = gcnew MyApplication(win);
	app->Run(win);
}
