#include "CSessionRowWidget.h"
#include "CMainMenuWidget.h"
#include "Components/Button.h"

void UCSessionRowWidget::Setup(UCMainMenuWidget* InParentWidget, uint32 InSelfIndex)
{
	ParentWidget = InParentWidget;
	SelfIndex = InSelfIndex;

	RowButton->OnClicked.AddDynamic(this, &UCSessionRowWidget::OnClicked);
}

void UCSessionRowWidget::OnClicked()
{
	ParentWidget->SetSelectedIndex(SelfIndex);
}
