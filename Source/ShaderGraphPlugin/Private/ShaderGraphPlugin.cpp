////////////////////////////////////////////////////////////////////////////////
//
// MIT License
// 
// Copyright (c) 2018-2019 Nuraga Wiswakarma
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////
//

#include "ShaderGraphPlugin.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif

#include "ShaderGraphPluginSettings.h"

#define LOCTEXT_NAMESPACE "IShaderGraphPlugin"

class FShaderGraphPlugin : public IShaderGraphPlugin
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

    void RegisterSettings();
    void UnregisterSettings();
    bool HandleSettingsSaved();
};

void FShaderGraphPlugin::StartupModule()
{
#if WITH_EDITOR
    // We don't quite have control of when the "Settings" module is loaded, so we'll wait until PostEngineInit to register settings.
    FCoreDelegates::OnPostEngineInit.AddRaw(this, &FShaderGraphPlugin::RegisterSettings);
#endif // WITH_EDITOR
}

void FShaderGraphPlugin::ShutdownModule()
{
#if WITH_EDITOR
    UnregisterSettings();
#endif
}

#if WITH_EDITOR
void FShaderGraphPlugin::RegisterSettings()
{
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

    // While this should usually be true, it's not guaranteed that the settings module will be loaded in the editor.
    // UBT allows setting bBuildDeveloperTools to false while bBuildEditor can be true.
    // The former option indirectly controls loading of the "Settings" module.
    if (SettingsModule)
    {
        ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "ShaderGraphPlugin",
            LOCTEXT("ShaderGraphPluginSettingsName", "Rendering Utility Library"),
            LOCTEXT("ShaderGraphPluginSettingsDescription", "Configure the Rendering Utility Library plug-in."),
            GetMutableDefault<UShaderGraphPluginSettings>()
        );

        if (SettingsSection.IsValid())
        {
            SettingsSection->OnModified().BindRaw(this, &FShaderGraphPlugin::HandleSettingsSaved);
        }
    }
}

void FShaderGraphPlugin::UnregisterSettings()
{
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

    if (SettingsModule)
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "ShaderGraphPlugin");
    }
}

bool FShaderGraphPlugin::HandleSettingsSaved()
{
    UShaderGraphPluginSettings* Settings = GetMutableDefault<UShaderGraphPluginSettings>();

    if (IsValid(Settings))
    {
        Settings->SaveConfig();
    }

    return true;
}
#endif

IMPLEMENT_MODULE(FShaderGraphPlugin, ShaderGraphPlugin)
DEFINE_LOG_CATEGORY(LogSGP);
DEFINE_LOG_CATEGORY(UntSGP);

#undef LOCTEXT_NAMESPACE
