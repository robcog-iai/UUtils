// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#include "UTagsEd.h"
#include "UTagsEdMode.h"

#define LOCTEXT_NAMESPACE "FUTagsEdModule"

void FUTagsEdModule::StartupModule()
{
	//FModuleManager::Get().LoadModule(TEXT("UTags"));
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FUTagsEdMode>(FUTagsEdMode::EM_UTagsEdModeId, LOCTEXT("UTagsEdModeName", "UTagsEdMode"), FSlateIcon(), true);
}

void FUTagsEdModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FUTagsEdMode::EM_UTagsEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUTagsEdModule, UTagsEd)