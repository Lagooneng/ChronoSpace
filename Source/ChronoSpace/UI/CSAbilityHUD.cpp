// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CSAbilityHUD.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UCSAbilityHUD::NativeConstruct()
{
    Super::NativeConstruct();

    //  �������� �Ŵ��� ��������
    UCSStageGameInstanceSubsystem* StageSubsystem = GetGameInstance()->GetSubsystem<UCSStageGameInstanceSubsystem>();
    if (StageSubsystem)
    {
        //  ���������� ����� �� UI�� ������Ʈ�ϵ��� �̺�Ʈ ���ε�
        if (!StageSubsystem->OnStageChanged.IsBound())
        {
            StageSubsystem->OnStageChanged.AddDynamic(this, &UCSAbilityHUD::InitializeAbilityUI);
        }
    }

    //  �ʱ� UI �ε�
    InitializeAbilityUI();
}

void UCSAbilityHUD::InitializeAbilityUI()
{
    // �������� ����ý��� ��������
    UCSStageGameInstanceSubsystem* StageSubsystem = GetGameInstance()->GetSubsystem<UCSStageGameInstanceSubsystem>();
    if (!StageSubsystem) return;

    //  ���� ��� ������ �����Ƽ ��������
    AvailableAbilities = StageSubsystem->GetAvailableAbilities();
    SelectedAbilityIndex = 0;

    //  ���� UI ����
    AbilityContainer->ClearChildren();

    for (int32 i = 0; i < AvailableAbilities.Num(); i++)
    {
        //  �����Ƽ UI ���� ����
        UUserWidget* NewWidget = CreateWidget<UUserWidget>(this, AbilityWidgetClass);
        if (NewWidget)
        {
            UImage* Icon = Cast<UImage>(NewWidget->GetWidgetFromName(TEXT("AbilityIcon")));
            UTextBlock* Text = Cast<UTextBlock>(NewWidget->GetWidgetFromName(TEXT("AbilityText")));

            if (Icon)
            {
                //  �������� ������ �� �ֵ��� (�����Ƽ �� �������� �����ؾ� ��)
                // Icon->SetBrushFromTexture(SomeAbilityIcon);
            }
            if (Text)
            {
                Text->SetText(FText::FromString(AvailableAbilities[i]));
            }

            AbilityContainer->AddChild(NewWidget);
        }
    }
}

//  ���콺 �ٷ� �����Ƽ ���� ����
void UCSAbilityHUD::ChangeAbilitySelection(float AxisValue)
{
    if (AvailableAbilities.Num() == 0) return;

    if (AxisValue > 0)
    {
        SelectedAbilityIndex = (SelectedAbilityIndex + 1) % AvailableAbilities.Num();
    }
    else if (AxisValue < 0)
    {
        SelectedAbilityIndex = (SelectedAbilityIndex - 1 + AvailableAbilities.Num()) % AvailableAbilities.Num();
    }
}

//  ���콺 Ŭ������ �����Ƽ ����
void UCSAbilityHUD::UseSelectedAbility()
{
    if (AvailableAbilities.Num() > 0)
    {
        FString SelectedAbility = AvailableAbilities[SelectedAbilityIndex];
        UE_LOG(LogTemp, Warning, TEXT("���� �����Ƽ: %s"), *SelectedAbility);

        //  �����Ƽ ���� ���� �߰� ���� (��: AbilitySystem ����)
    }
}
