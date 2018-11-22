// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"

class FUTagsEdModeToolkit : public FModeToolkit
{
public:

	FUTagsEdModeToolkit();
	
	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }

	// Reference to the SUtagsTreeViewWidget class Slate UI.
	TSharedPtr<class SUTagsTreeViewWidget> SUtagsTreeViewWidgetRef;

private:
	
	TSharedPtr<SWidget> ToolkitWidget;

};
