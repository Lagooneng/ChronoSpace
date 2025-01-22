// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/TA/CSTA_TimePauseArea.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/BoxComponent.h"
#include "Physics/CSCollision.h"
#include "ChronoSpace.h"


ACSTA_TimePauseArea::ACSTA_TimePauseArea()
{
	TimePauseTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TimePauseTrigger"));
	RootComponent = TimePauseTrigger;
	TimePauseTrigger->SetBoxExtent(FVector(200.0f, 200.0f, 1000.0f));
	TimePauseTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	TimePauseTrigger->SetCollisionProfileName(CPROFILE_CSTRIGGER);
	TimePauseTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACSTA_TimePauseArea::OnTriggerBeginOverlap);
	TimePauseTrigger->OnComponentEndOverlap.AddDynamic(this, &ACSTA_TimePauseArea::OnTriggerEndOverlap);
}


void ACSTA_TimePauseArea::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void ACSTA_TimePauseArea::ConfirmTargetingAndContinue()
{
	//UE_LOG(LogCS, Log, TEXT("ConfirmTargetingAndContinue"));
	if (SourceActor)
	{
		OnComplete.Broadcast();
	}
}

void ACSTA_TimePauseArea::BeginPlay()
{
    Super::BeginPlay();

    if (TimePauseTrigger)
    {
        FVector BoxLocation = TimePauseTrigger->GetComponentLocation();
        FVector BoxExtent = TimePauseTrigger->GetScaledBoxExtent(); // �������� ����� �ڽ� ũ��
        FQuat   BoxRotation = TimePauseTrigger->GetComponentRotation().Quaternion();

        DrawDebugBox(
            GetWorld(),
            BoxLocation,
            BoxExtent,
            BoxRotation,
            FColor::Green,
            false,  // ���� ǥ��
            DurtionTime, // -1�� �ð� ���� ����
            0,     // ����� �� �켱����
            2.0f   // �� �β�
        );
    }
}


void ACSTA_TimePauseArea::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (auto Act = ActorsThatIsPausedTime.CreateIterator(); Act; ++Act)
    {
        if (!IsValid(Act.Value())) continue;

        ACharacter* RemainedCharacter = Cast<ACharacter>(Act.Value());
        if (RemainedCharacter)
        {
            // �ð� ����
            if (RemainedCharacter->CustomTimeDilation != 1.0f)
            {
                RemainedCharacter->CustomTimeDilation = 1.0f;
                UE_LOG(LogTemp, Log, TEXT("CustomTimeDilation reset to 1.0 for actor: %s"), *RemainedCharacter->GetName());
            }

            // ���� GravityScale ó�� �κ� ����
            // �ð� ������ �����ϰ� �ߺ��� ���� �����߽��ϴ�.
        }

        // ��Ͽ��� ����
        ActorsThatIsPausedTime.FindAndRemoveChecked(Act.Value()->GetFName());
    }

    // �θ� Ŭ������ EndPlay ȣ��
    Super::EndPlay(EndPlayReason);
}

void ACSTA_TimePauseArea::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    ACharacter* DetectedCharacter = Cast<ACharacter>(OtherActor);

    if (DetectedCharacter)
    {
        // �ð� ���� ���߱�
        if (DetectedCharacter->CustomTimeDilation == 0.0f)
        {
            // �̹� ���� ���¶�� �ٽ� ó������ ����
            return;
        }
        DetectedCharacter->CustomTimeDilation = 0.0f;

        // ��츦 ���� ��Ͽ� �߰�
        ActorsThatIsPausedTime.Emplace(OtherActor->GetFName(), OtherActor);
    }
}

void ACSTA_TimePauseArea::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ACharacter* DetectedCharacter = Cast<ACharacter>(OtherActor);
    if (DetectedCharacter)
    {
        // �ð� ����
        if (DetectedCharacter->CustomTimeDilation <= 1.001f && DetectedCharacter->CustomTimeDilation >= 0.999f)
        {
            // �̹� �ð��� ���� ���¶�� �ٽ� ó������ ����
            return;
        }

        DetectedCharacter->CustomTimeDilation = 1.0f;

        // ���� �ð� ��Ͽ��� ����
        if (ActorsThatIsPausedTime.Contains(OtherActor->GetFName()))
        {
            ActorsThatIsPausedTime.FindAndRemoveChecked(OtherActor->GetFName());
        }

        // ����� �α� ���
        UE_LOG(LogTemp, Log, TEXT("Time resumed for actor: %s"), *OtherActor->GetName());
    }
}
