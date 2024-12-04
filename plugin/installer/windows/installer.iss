#define MyAppName "Replikator"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "AudioTools"
#define MyAppURL "https://www.audiotools.com"

[Setup]
AppId={{REPLIKATOR-VST-PLUGIN}}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
DefaultDirName={commonpf}\VST3\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputBaseFilename=ReplikatorSetup
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64

[Files]
Source: "..\build\Replikator.vst3\*"; DestDir: "{commonpf}\VST3\Replikator"; Flags: ignoreversion recursesubdirs
Source: "..\build\Replikator.aax\*"; DestDir: "{commonpf}\Common Files\Avid\Audio\Plug-Ins"; Flags: ignoreversion recursesubdirs

[Code]
function GetVST2Dir(Param: String): String;
begin
  Result := ExpandConstant('{commonpf}\VSTPlugins');
end;