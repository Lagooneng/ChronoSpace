// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Manager/CSStageManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "CSAbilityHUD.generated.h"

UCLASS()
class CHRONOSPACE_API UCSAbilityHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    // �����Ƽ UI�� ǥ���� �����̳�
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* AbilityContainer;

    // �����Ƽ UI ��� (�̹��� + �ؽ�Ʈ)
    UPROPERTY(EditDefaultsOnly, Category = "AbilityUI")
    TSubclassOf<UUserWidget> AbilityWidgetClass;

    // ���� ��� ������ �����Ƽ ���
    UPROPERTY(BlueprintReadWrite, Category = "AbilityUI")
    TArray<FString> AvailableAbilities;

    // ���� ���õ� �����Ƽ �ε���
    UPROPERTY(BlueprintReadWrite, Category = "AbilityUI")
    int32 SelectedAbilityIndex;

    // UI �ʱ�ȭ �Լ� (�������� ���� �� ȣ���)
    UFUNCTION(BlueprintCallable, Category = "AbilityUI")
    void InitializeAbilityUI();

protected:
    virtual void NativeConstruct() override;

private:
    // ���콺 �� �Է� ó��
    UFUNCTION()
    void ChangeAbilitySelection(float AxisValue);

    // �����Ƽ ����
    UFUNCTION()
    void UseSelectedAbility();
};