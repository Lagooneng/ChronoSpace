// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CSStageManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageChanged);


/**
 * 
 */
UCLASS()
class CHRONOSPACE_API UCSStageManager : public UGameInstance
{
    GENERATED_BODY()

public:
    // �⺻ ������
    UCSStageManager();

    // ���� �������� (L_Main, L_Stage1 ��)
    UPROPERTY(BlueprintReadWrite, Category = "Stage")
    FString CurrentStage;

    // ���������� ��� ������ �����Ƽ ��� 
    // ���������� ��밡��. UPROPERTY() �������. 
    TMap<FString, TArray<FString>> StageAbilities;

    // �������� ���� �� ȣ��Ǵ� ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Stage")
    FOnStageChanged OnStageChanged;

    // �������� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Stage")
    void ChangeStage(FString NewStage);

    // ���� ������������ ��� ������ �����Ƽ ��������
    UFUNCTION(BlueprintCallable, Category = "Stage")
    TArray<FString> GetAvailableAbilities();

    // �ʱ� ������ ����
    UFUNCTION(BlueprintCallable, Category = "Stage")
    void InitializeStageAbilities();
};
