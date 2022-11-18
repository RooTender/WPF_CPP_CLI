#include <windows.h>
#include "DataModel.h"
using namespace System::Runtime::Remoting;
using namespace System::Security::Policy;
using namespace System::Security;
using namespace System;
using namespace System::Windows;
using namespace System::IO;
using namespace System::Windows::Markup;
using namespace System::Windows::Controls;
using namespace System::CodeDom;
using namespace System::CodeDom::Compiler;
using namespace System::Reflection;
using namespace System::Windows::Documents;
using namespace std;


public ref class MyApplication : public Application
{
public:

private: DataModel^ h_dm;
private: TextRange ^textRang;
private: String ^ pathToVBCode, ^code, ^tekst, ^st;
private: Button ^addBtn, ^invokeBtn, ^setBtn;
private: RichTextBox ^codeRTB;
private: ListBox ^errorsListBox, ^methodsListBox, ^variablesListBox;
private: Assembly^ modul;
private: Type^ t;
private: Object^ obj;
private: ObjectHandle^ handle;
private: array<FieldInfo^>^ fields;
private: MethodInfo^ mI;
private: FieldInfo^ fI;
private: TextBox ^resultTextBox, ^parameterTextBox, ^setTextBox, ^setTextBox2;
private: ComboBox ^checkZoneComboBox;

	public: MyApplication(Window ^win)
	{
		h_dm = gcnew DataModel();
		win->DataContext = h_dm;

		pathToVBCode = gcnew String("..\\VBCode\\Class1.vb");
		code = File::ReadAllText(pathToVBCode);
		addBtn = (Button^)win->FindName("addButton");
		addBtn->Click += gcnew RoutedEventHandler(this, &MyApplication::OnAddBtnClick);
		invokeBtn = (Button^)win->FindName("invokeButton");
		invokeBtn->Click += gcnew RoutedEventHandler(this, &MyApplication::OninvokeBtnClick);
		setBtn = (Button^)win->FindName("setButton");
		setBtn->Click += gcnew RoutedEventHandler(this, &MyApplication::OnsetBtnClick);
		methodsListBox = (ListBox^)win->FindName("methodsListBox");
		methodsListBox->SelectionChanged += gcnew System::Windows::Controls::SelectionChangedEventHandler(this, &MyApplication::OnSelectionMethodsListBoxChanged);
		variablesListBox = (ListBox^)win->FindName("variablesListBox");
		variablesListBox->SelectionChanged += gcnew System::Windows::Controls::SelectionChangedEventHandler(this, &MyApplication::OnSelectionVariablesListBoxChanged);
		errorsListBox = (ListBox^)win->FindName("errorsListBox");
		methodsListBox = (ListBox^)win->FindName("methodsListBox");
		variablesListBox = (ListBox^)win->FindName("variablesListBox");
		resultTextBox = (TextBox^)win->FindName("resultTextBox");
		parameterTextBox = (TextBox^)win->FindName("parameterTextBox");
		setTextBox = (TextBox^)win->FindName("setTextBox");
		setTextBox2 = (TextBox^)win->FindName("setTextBox2");
		checkZoneComboBox = (ComboBox^)win->FindName("checkZoneComboBox");
		codeRTB = (RichTextBox^)win->FindName("codeRichTextBox");
		codeRTB->AppendText(code);
		codeRTB->Document->LineHeight = 0.1;
	}

	private: System::Void OnSelectionMethodsListBoxChanged(Object^ sender, SelectionChangedEventArgs^ e)
	{

	}

	private: System::Void OnSelectionVariablesListBoxChanged(Object^ sender, SelectionChangedEventArgs^ e)
	{

	}
	private: System::Void OninvokeBtnClick(Object^ sender, RoutedEventArgs^ e)
	{

	}


	private: System::Void OnsetBtnClick(Object^ sender, RoutedEventArgs^ e)
	{

	}

	private: System::Void OnAddBtnClick(Object^ sender, RoutedEventArgs^ e)
	{

	}

};

[STAThread]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmd, int nCmd)
{
	Stream^ st = File::OpenRead("MainWindow.xaml");
	Window^ win = (Window^)XamlReader::Load(st, nullptr);
	Application^ app = gcnew MyApplication(win);
	app->Run(win);
}


