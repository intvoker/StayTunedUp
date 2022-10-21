// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STU_EquipFinishedAnimNotify.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipFinishedNotifySignature, USkeletalMeshComponent*, MeshComp);

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_EquipFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;

	FEquipFinishedNotifySignature OnEquipFinishedNotify;
};
