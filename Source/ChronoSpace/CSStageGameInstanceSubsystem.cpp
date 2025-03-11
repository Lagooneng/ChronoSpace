#include "CSStageGameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"

UCSStageGameInstanceSubsystem::UCSStageGameInstanceSubsystem()
{
    CurrentStage = "L_Main";  // �⺻ �������� ����
}

void UCSStageGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    //  �������� �����Ƽ ������ �ʱ�ȭ
    InitializeStageAbilities();

    UE_LOG(LogTemp, Warning, TEXT("CSStageGameInstanceSubsystem Initialized!"));
}

void UCSStageGameInstanceSubsystem::Deinitialize()
{
    Super::Deinitialize();
    UE_LOG(LogTemp, Warning, TEXT("CSStageGameInstanceSubsystem Deinitialized!"));
}

void UCSStageGameInstanceSubsystem::ChangeStage(FString NewStage)
{
    UE_LOG(LogTemp, Warning, TEXT("ChangeStage called with: %s"), *NewStage);

    CurrentStage = NewStage;
    OnStageChanged.Broadcast(); //  UI ������Ʈ �� ��Ÿ ��� ����

    // ���� ���� ����
    UGameplayStatics::OpenLevel(GetWorld(), *NewStage);
}

TArray<FString> UCSStageGameInstanceSubsystem::GetAvailableAbilities()
{
    if (StageAbilities.Contains(CurrentStage))
    {
        return StageAbilities[CurrentStage].Abilities;
    }
    return TArray<FString>();
}

void UCSStageGameInstanceSubsystem::InitializeStageAbilities()
{
    //  ���� ������ �߰�
    FStageAbilityList Stage1Abilities;
    Stage1Abilities.Abilities = { "ReverseGravity", "TimeStop" };

    FStageAbilityList Stage2Abilities;
    Stage2Abilities.Abilities = { "TimeStop" };

    StageAbilities.Add("L_Stage1", Stage1Abilities);
    StageAbilities.Add("L_Stage2", Stage2Abilities);
}
