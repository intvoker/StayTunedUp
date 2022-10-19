// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUEquipFinishedAnimNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipFinishedNotifySignature, USkeletalMeshComponent*, MeshComp);

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTUEquipFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;

	FEquipFinishedNotifySignature OnEquipFinishedNotify;
};
