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
	TextBox ^_resultTextBox, ^_parameterTextBox, ^_getValueTextBox, ^_setValueTextBox;
	ComboBox ^_checkZoneComboBox;

	AppDomain^ _zone = nullptr;

	static String^ GetOutputPath()
	{
		return Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location) + "\\..\\WPFCppLab3";
	}

	Void Cleanup()
	{
		_errorsListBox->Items->Clear();
		_methodsListBox->ItemsSource = nullptr;
	    _variablesListBox->ItemsSource = nullptr;

		if (_zone != nullptr)
	    {
	        AppDomain::Unload(_zone);
	    }

	    if (_dataModel->Methods != nullptr)
	    {
	        _variablesListBox->ItemsSource = nullptr;
	        _methodsListBox->ItemsSource = nullptr;
	        _dataModel->Methods = nullptr;
	        _dataModel->Fields = nullptr;
	        _dataModel->Type = nullptr;
	        _dataModel->Instance = nullptr;
	        _dataModel->Handle = nullptr;
	        _assembly = nullptr;
	    }
	}

	Void UpdateVariableInTextBox()
	{
		Object^ instance = _dataModel->Fields[_variablesListBox->SelectedIndex]->GetValue(_dataModel->Instance);
		_getValueTextBox->Text = instance != nullptr ? instance->ToString() : "";
	}

	Void OnSelectionMethodsListBoxChanged(Object^ sender, SelectionChangedEventArgs^ e)
	{
		
	}
	
	Void OnSelectionVariablesListBoxChanged(Object^ sender, SelectionChangedEventArgs^ e)
	{
		UpdateVariableInTextBox();
	}

	Void OnInvokeButtonClick(Object^ sender, RoutedEventArgs^ e)
	{

	}

	Void OnSetButtonClick(Object^ sender, RoutedEventArgs^ e)
	{
		if (_variablesListBox->SelectedIndex == -1)
	    {
			return;
		}
		
        String^ variableName = _dataModel->Fields[_variablesListBox->SelectedIndex]->Name;
        FieldInfo^ fieldInfo = _dataModel->Type->GetField(variableName);
		Object^ valueToSet = _setValueTextBox->Text;

        if (fieldInfo != nullptr)
        {
            try
            {
                valueToSet = Convert::ChangeType(valueToSet, fieldInfo->FieldType);
            }
            catch (Exception^ exception)
            {
				MessageBox::Show(exception->Message);
				return;
            }

            if (!fieldInfo->FieldType->IsAssignableFrom(valueToSet->GetType()))
            {
            	MessageBox::Show("Cannot assign this value type to the field!");
				return;
			}

            fieldInfo->SetValue(_dataModel->Instance, valueToSet);
            
			UpdateVariableInTextBox();
        }
	}
	
	Void OnAddButtonClick(Object^ sender, RoutedEventArgs^ e)
	{
		Cleanup();
		
	    CodeDomProvider^ provider = CodeDomProvider::CreateProvider("VisualBasic");

		_code = TextRange(_richTextBox->Document->ContentStart, _richTextBox->Document->ContentEnd).Text;

		auto compileUnit = gcnew CodeSnippetCompileUnit(_code);
		auto parameters = gcnew CompilerParameters();
		parameters->GenerateInMemory = true;
		String^ outputFilename = "Result";

		// The file must exist in two locations in order to work properly
		// Workaround solution
	    parameters->OutputAssembly = Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location) + "\\" + outputFilename + ".dll";
	    provider->CompileAssemblyFromDom(parameters, compileUnit);

		// Real assembly solution
	    parameters->OutputAssembly =  GetOutputPath() + "\\" + outputFilename + ".dll";
	    CompilerResults^ compilationResult = provider->CompileAssemblyFromDom(parameters, compileUnit);

	    if (compilationResult->Errors->Count > 0)
	    {
	        for each (CompilerError ^ err in compilationResult->Errors)
	        {
	            _errorsListBox->Items->Add(err->ErrorText);
	        }

			return;
	    }
	    
        auto evidence = gcnew Evidence();
        evidence->AddHostEvidence(gcnew Zone(_dataModel->SelectedSecurityZone));

        auto setup = gcnew AppDomainSetup();
        setup->ApplicationBase = Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location);

        auto appDomain = AppDomain::CreateDomain("Zone", nullptr, setup, SecurityManager::GetStandardSandbox(evidence));
		
        _assembly = compilationResult->CompiledAssembly;
        Type^ t = _assembly->GetType("A");	// Class "A" - the same from the Class1.vb
		
        try
        {
            _dataModel->Handle = Activator::CreateInstanceFrom(appDomain, t->Assembly->ManifestModule->ScopeName, t->FullName);
            _dataModel->Instance = _dataModel->Handle->Unwrap();
            _dataModel->Type = _dataModel->Instance->GetType();
        }
        catch (Exception^ exception)
        {
            _errorsListBox->Items->Add(exception->Message);
        }

		_dataModel->Fields = _dataModel->Type->GetFields();
		_dataModel->Methods = _dataModel->Type->GetMethods();

        _variablesListBox->ItemsSource = _dataModel->Fields;
        _methodsListBox->ItemsSource = _dataModel->Methods;
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
		_getValueTextBox =		 safe_cast<TextBox^>(win->FindName("setTextBox"));
		_setValueTextBox =		 safe_cast<TextBox^>(win->FindName("setTextBox2"));
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
