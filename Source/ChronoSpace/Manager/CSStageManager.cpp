// Fill out your copyright notice in the Description page of Project Settings.


#include "CSStageManager.h"
#include "Kismet/GameplayStatics.h"

UCSStageManager::UCSStageManager()
{
    CurrentStage = "L_Main"; // �⺻�� ����
}

void UCSStageManager::ChangeStage(FString NewStage)
{
    CurrentStage = NewStage;

    UGameplayStatics::OpenLevel(GetWorld(), *NewStage);

    OnStageChanged.Broadcast(); // �������� ���� �� UI ������Ʈ ȣ��
}

TArray<FString> UCSStageManager::GetAvailableAbilities()
{
    if (StageAbilities.Contains(CurrentStage))
    {
        return StageAbilities[CurrentStage];
    }
    return TArray<FString>();
}

// �ʱ� ������ ����
void UCSStageManager::InitializeStageAbilities()
{
    // ���� ������ �߰�
    StageAbilities.Add("L_Stage1", { "ReverseGravity", "TimeStop" });
    StageAbilities.Add("L_Stage2", { "TimeStop" });

    OnStageChanged.Broadcast(); // �ʱ� ���� �� UI ������Ʈ
}